/*
 * ripped off from ../ntpres/ntpres.c by Greg Troxel 4/2/92
 * routine callable from ntpd, rather than separate program
 * also, key info passed in via a global, so no key file needed.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netdb.h>
#include <signal.h>

/**/
#include <netinet/in.h>
#include <arpa/inet.h>
/**/
#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>		/* MAXHOSTNAMELEN (often) */
#endif

#include "ntpd.h"
#include "ntp_io.h"
#include "ntp_request.h"
#include "ntp_stdlib.h"
#include "ntp_syslog.h"

#define	STREQ(a, b)	(*(a) == *(b) && strcmp((a), (b)) == 0)

/*
 * Each item we are to resolve and configure gets one of these
 * structures defined for it.
 */
struct dns_entry {
	struct dns_entry *de_next;
	struct info_dns_assoc de_info; /* DNS info for peer */
};
#define	de_associd	de_info.associd
#define	de_peeraddr	de_info.peeraddr
#define	de_hostname	de_info.hostname

/*
 * dns_entries is a pointer to the list of configuration entries
 * we have left to do.
 */
static struct dns_entry *dns_entries = NULL;

/*
 * We take an interrupt every thirty seconds, at which time we decrement
 * config_timer and resolve_timer.  The former is set to 2, so we retry
 * unsucessful reconfigurations every minute.  The latter is set to
 * an exponentially increasing value which starts at 2 and increases to
 * 32.  When this expires we retry failed name resolutions.
 *
 * We sleep SLEEPTIME seconds before doing anything, to give the server
 * time to arrange itself.
 */
#define	MINRESOLVE	2
#define	MAXRESOLVE	32
#define	CONFIG_TIME	2
#define	ALARM_TIME	30

#define	SLEEPTIME	2

static	volatile int config_timer = 0;
static	volatile int resolve_timer = 0;

static	int resolve_value;	/* next value of resolve timer */

/*
 * Big hack attack
 */
#define	LOCALHOST	0x7f000001	/* 127.0.0.1, in hex, of course */
#define	SKEWTIME	0x08000000	/* 0.03125 seconds as a l_fp fraction */

/*
 * Select time out.  Set to 2 seconds.  The server is on the local machine,
 * after all.
 */
#define	TIMEOUT_SEC	2
#define	TIMEOUT_USEC	0


/*
 * File descriptor for ntp request code.
 */
static	int sockfd = -1;

/*
 * Pipe descriptors
 */
int p_fd[2] = { -1, -1 };

/* stuff to be filled in by caller */

extern keyid_t req_keyid;	/* request keyid */

/* end stuff to be filled in */

void		ntp_res		P((void));
static	RETSIGTYPE bong		P((int));
static	void	checkparent	P((void));
static	void	removeentry	P((struct dns_entry *));
static	void	addentry	P((char *, u_int32, u_short));
static	int	findhostaddr	P((struct dns_entry *));
static	void	openntp		P((void));
static	int	host_assoc	P((struct info_dns_assoc *));
static	void	doconfigure	P((int));

struct ntp_res_t_pkt {		/* Tagged packet: */
	void *tag;		/* For the caller */
	u_int32 paddr;		/* IP to look up, or 0 */
	char name[NTP_MAXHOSTNAME]; /* Name to look up (if 1st byte is not 0) */
};

struct ntp_res_c_pkt {		/* Control packet: */
	char name[NTP_MAXHOSTNAME];
	u_int32 paddr;
	int mode;
	int version;
	int minpoll;
	int maxpoll;
	int flags;
	int ttl;
	keyid_t keyid;
	u_char keystr[MAXFILENAME];
};
/*
 * ntp_res_send
 *
 */

void
ntp_res_send(
	void *tag,		/* Return this with the answer */
	char *name,		/* Name to resolve (or NIL) */
	u_int32 paddr,		/* Address to resolve (or 0) */
	u_short associd		/* Association ID (if available) */
	)
{
	pid_t pid;

	/*
	 * fork.
	 * - parent returns
	 * - child stuffs data and calls ntp_res(NTP_RES_V2)
	 */

	msyslog(LOG_INFO, "ntp_res_send: req_keyid %d\n", req_keyid);
	for (pid = -1; pid == -1;) {
#ifdef RES_TEST
		pid = 0;
#else
		pid = fork();
#endif
		if (pid == -1) {
			msyslog(LOG_ERR, "ntp_res_send: fork() failed: %m");
			sleep(2);
		}
	}
	switch (pid) {
	    case -1:	/* Error */
		msyslog(LOG_DEBUG, "ntp_res_send: error...");
		/* Can't happen */
		break;

	    case 0:	/* Child */
		closelog();
		kill_asyncio();
		(void) signal_no_reset(SIGCHLD, SIG_DFL);
#ifndef LOG_DAEMON
		openlog("ntp_res", LOG_PID);
# else /* LOG_DAEMON */
#  ifndef LOG_NTP
#   define	LOG_NTP LOG_DAEMON
#  endif
		openlog("ntp_res_send", LOG_PID | LOG_NDELAY, LOG_NTP);
#endif

		msyslog(LOG_DEBUG, "ntp_res_send: in child...");
		addentry(name, paddr, associd);
		msyslog(LOG_DEBUG, "ntp_res_send: back from addentry()");
		ntp_res();
		msyslog(LOG_DEBUG, "ntp_res_send: in child...DONE");
		break;

	    default:	/* Parent */
		msyslog(LOG_DEBUG, "ntp_res_send: in parent...");
		/* Nothing to do.  (In Real Life, this never happens.) */
		return;
	}
}

/*
 * ntp_res needs;
 *
 *	req_key(???), req_keyid valid
 *	syslog still open
 */

void
ntp_res(void)
{
#ifdef HAVE_SIGSUSPEND
	sigset_t set;

	sigemptyset(&set);
#endif /* HAVE_SIGSUSPEND */

#ifdef DEBUG
	if (debug) {
		msyslog(LOG_INFO, "NTP_RESOLVER running");
	}
#endif

	/* check out auth stuff */
	if (sys_authenticate) {
		if (!authistrusted(req_keyid)) {
			msyslog(LOG_ERR, "invalid request keyid %08x",
			    req_keyid );
			exit(1);
		}
	}

	/*
	 * Make a first cut at resolving the bunch
	 */
	doconfigure(1);
	if (dns_entries == NULL) {
		if (debug) {
			msyslog(LOG_INFO, "NTP_RESOLVER done!");
		}
#if defined SYS_WINNT
		ExitThread(0);	/* Don't want to kill whole NT process */
#else
		exit(0);	/* done that quick */
#endif
	}
	
	/*
	 * Here we've got some problem children.  Set up the timer
	 * and wait for it.
	 */
	resolve_value = resolve_timer = MINRESOLVE;
	config_timer = CONFIG_TIME;
#ifndef SYS_WINNT
	(void) signal_no_reset(SIGALRM, bong);
	alarm(ALARM_TIME);
#endif /* SYS_WINNT */

	for (;;) {
		if (dns_entries == NULL)
		    exit(0);

		checkparent();

		if (resolve_timer == 0) {
			if (resolve_value < MAXRESOLVE)
			    resolve_value <<= 1;
			resolve_timer = resolve_value;
#ifdef DEBUG
			msyslog(LOG_INFO, "resolve_timer: 0->%d", resolve_timer);
#endif
			config_timer = CONFIG_TIME;
			doconfigure(1);
			continue;
		} else if (config_timer == 0) {
			config_timer = CONFIG_TIME;
#ifdef DEBUG
			msyslog(LOG_INFO, "config_timer: 0->%d", config_timer);
#endif
			doconfigure(0);
			continue;
		}
#ifndef SYS_WINNT
		/*
		 * There is a race in here.  Is okay, though, since
		 * all it does is delay things by 30 seconds.
		 */
# ifdef HAVE_SIGSUSPEND
		sigsuspend(&set);
# else
		sigpause(0);
# endif /* HAVE_SIGSUSPEND */
#else
		if (config_timer > 0)
		    config_timer--;
		if (resolve_timer > 0)
		    resolve_timer--;
		sleep(ALARM_TIME);
#endif /* SYS_WINNT */
	}
}


#ifndef SYS_WINNT
/*
 * bong - service and reschedule an alarm() interrupt
 */
static RETSIGTYPE
bong(
	int sig
	)
{
	if (config_timer > 0)
	    config_timer--;
	if (resolve_timer > 0)
	    resolve_timer--;
	alarm(ALARM_TIME);
}
#endif /* SYS_WINNT */

/*
 * checkparent - see if our parent process is still running
 *
 * No need to worry in the Windows NT environment whether the
 * main thread is still running, because if it goes
 * down it takes the whole process down with it (in
 * which case we won't be running this thread either)
 * Turn function into NOP;
 */

static void
checkparent(void)
{
#if !defined (SYS_WINNT) && !defined (SYS_VXWORKS)

	/*
	 * If our parent (the server) has died we will have been
	 * inherited by init.  If so, exit.
	 */
	if (getppid() == 1) {
		msyslog(LOG_INFO, "parent died before we finished, exiting");
		exit(0);
	}
#endif /* SYS_WINNT && SYS_VXWORKS*/
}


/*
 * removeentry - we are done with an entry, remove it from the list
 */
static void
removeentry(
	struct dns_entry *entry
	)
{
	register struct dns_entry *de;

	de = dns_entries;
	if (de == entry) {
		dns_entries = de->de_next;
		return;
	}

	while (de != NULL) {
		if (de->de_next == entry) {
			de->de_next = entry->de_next;
			return;
		}
		de = de->de_next;
	}
}


/*
 * addentry - add an entry to the configuration list
 */
static void
addentry(
	char *name,
	u_int32 paddr,
	u_short associd
	)
{
	register struct dns_entry *de;

#ifdef DEBUG
	if (debug > 1) {
		struct in_addr si;

		si.s_addr = paddr;
		msyslog(LOG_INFO, 
			"ntp_res_send: <%s> %s associd %d\n",
			(name) ? name : "", inet_ntoa(si), associd);
	}
#endif

	de = (struct dns_entry *)emalloc(sizeof(struct dns_entry));
	if (name) {
		strncpy(de->de_hostname, name, sizeof de->de_hostname);
	} else {
		de->de_hostname[0] = 0;
	}
	de->de_peeraddr = paddr;
	de->de_associd = associd;
	de->de_next = NULL;

	if (dns_entries == NULL) {
		dns_entries = de;
	} else {
		register struct dns_entry *dep;

		for (dep = dns_entries; dep->de_next != NULL;
		     dep = dep->de_next)
		    /* nothing */;
		dep->de_next = de;
	}
}


/*
 * findhostaddr - resolve a host name into an address (Or vice-versa)
 *
 * Given one of {de_peeraddr,de_hostname}, find the other one.
 * It returns 1 for "success" and 0 for an uncorrectable failure.
 * Note that "success" includes try again errors.  You can tell that you
 *  got a "try again" since {de_peeraddr,de_hostname} will still be zero.
 */
static int
findhostaddr(
	struct dns_entry *entry
	)
{
	struct hostent *hp;

	checkparent();		/* make sure our guy is still running */

	if (entry->de_hostname[0] && entry->de_peeraddr) {
		struct in_addr si;

		si.s_addr = entry->de_peeraddr;
		/* HMS: Squawk? */
		msyslog(LOG_ERR, "findhostaddr: both de_hostname and de_peeraddr are defined: <%s>/%s", &entry->de_hostname[0], inet_ntoa(si));
		return 1;
	}

	if (!entry->de_hostname[0] && !entry->de_peeraddr) {
		msyslog(LOG_ERR, "findhostaddr: both de_hostname and de_peeraddr are undefined!");
		return 0;
	}

	if (entry->de_hostname[0]) {
#ifdef DEBUG
		if (debug > 2)
			msyslog(LOG_DEBUG, "findhostaddr: Resolving <%s>",
				&entry->de_hostname[0]);
#endif DEBUG
		hp = gethostbyname(&entry->de_hostname[0]);
	} else {
#ifdef DEBUG
		if (debug > 2) {
			struct in_addr si;

			si.s_addr = entry->de_peeraddr;
			msyslog(LOG_DEBUG, "findhostaddr: Resolving %s",
				inet_ntoa(si));
		}
#endif
		hp = gethostbyaddr((const char *)&entry->de_peeraddr,
				   sizeof entry->de_peeraddr,
				   AF_INET);
	}

	if (hp == NULL) {
		/*
		 * If the resolver is in use, see if the failure is
		 * temporary.  If so, return success.
		 */
		if (h_errno == TRY_AGAIN)
		    return (1);
		return (0);
	}

	if (entry->de_hostname[0]) {
#ifdef DEBUG
		if (debug > 2)
			msyslog(LOG_DEBUG, "findhostaddr: name resolved.");
#endif
		/*
		 * Use the first address.  We don't have any way to tell
		 * preferences and older gethostbyname() implementations
		 * only return one.
		 */
		memmove((char *)&(entry->de_peeraddr),
			(char *)hp->h_addr,
			sizeof(struct in_addr));
	} else {
#ifdef DEBUG
		if (debug > 2)
			msyslog(LOG_DEBUG, "findhostaddr: address resolved.");
#endif
		strncpy(&entry->de_hostname[0], hp->h_name, sizeof entry->de_hostname);
	}
		   
	return (1);
}


/*
 * openntp - open a socket to the ntp server
 */
static void
openntp(void)
{
	struct sockaddr_in saddr;

	if (sockfd >= 0)
	    return;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd == -1) {
		msyslog(LOG_ERR, "socket() failed: %m");
		exit(1);
	}

	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(NTP_PORT);		/* trash */
	saddr.sin_addr.s_addr = htonl(LOCALHOST);	/* garbage */

	/*
	 * Make the socket non-blocking.  We'll wait with select()
	 */
#ifndef SYS_WINNT
# if defined(O_NONBLOCK)
	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		msyslog(LOG_ERR, "fcntl(O_NONBLOCK) failed: %m");
		exit(1);
	}
# else
#  if defined(FNDELAY)
	if (fcntl(sockfd, F_SETFL, FNDELAY) == -1) {
		msyslog(LOG_ERR, "fcntl(FNDELAY) failed: %m");
		exit(1);
	}
#  else
#   include "Bletch: NEED NON BLOCKING IO"
#  endif /* FNDDELAY */
# endif /* O_NONBLOCK */
#else  /* SYS_WINNT */
	{
		int on = 1;

		if (ioctlsocket(sockfd,FIONBIO,(u_long *) &on) == SOCKET_ERROR) {
			msyslog(LOG_ERR, "ioctlsocket(FIONBIO) fails: %m");
			exit(1); /* Windows NT - set socket in non-blocking mode */
		}
	}
#endif /* SYS_WINNT */


	if (connect(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
		msyslog(LOG_ERR, "openntp: connect() failed: %m");
		exit(1);
	}
}


/*
 * host_assoc: Send the resolved hostname for the associd
 */
static int
host_assoc(
	struct info_dns_assoc *conf
	)
{
	fd_set fdset;
	struct timeval tvout;
	struct req_pkt reqpkt;
	l_fp ts;
	int n;
#ifdef SYS_WINNT
	HANDLE hReadWriteEvent = NULL;
	BOOL ret;
	DWORD NumberOfBytesWritten, NumberOfBytesRead, dwWait;
	OVERLAPPED overlap;
#endif /* SYS_WINNT */

	checkparent();		/* make sure our guy is still running */

	if (sockfd < 0)
	    openntp();
	
#ifdef SYS_WINNT
	hReadWriteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif /* SYS_WINNT */

	/*
	 * Try to clear out any previously received traffic so it
	 * doesn't fool us.  Note the socket is nonblocking.
	 */
	tvout.tv_sec =  0;
	tvout.tv_usec = 0;
	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	while (select(sockfd + 1, &fdset, (fd_set *)0, (fd_set *)0, &tvout) >
	       0) {
		recv(sockfd, (char *)&reqpkt, REQ_LEN_MAC, 0);
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
	}

	/*
	 * Make up a request packet with the configuration info
	 */
	memset((char *)&reqpkt, 0, sizeof(reqpkt));

	reqpkt.rm_vn_mode = RM_VN_MODE(0, 0, 0);
	reqpkt.auth_seq = AUTH_SEQ(1, 0);	/* authenticated, no seq */
	reqpkt.implementation = IMPL_XNTPD;	/* local implementation */
	reqpkt.request = REQ_HOSTNAME_ASSOCID;	/* Hostname for associd */
	reqpkt.err_nitems = ERR_NITEMS(0, 1);	/* one item */
	reqpkt.mbz_itemsize = MBZ_ITEMSIZE(sizeof(struct info_dns_assoc));
	memmove(reqpkt.data, (char *)conf, sizeof(struct info_dns_assoc));
	reqpkt.keyid = htonl(req_keyid);

	get_systime(&ts);
	L_ADDUF(&ts, SKEWTIME);
	HTONL_FP(&ts, &reqpkt.tstamp);
	n = 0;
	if (sys_authenticate)
		n = authencrypt(req_keyid, (u_int32 *)&reqpkt, REQ_LEN_NOMAC);

	/*
	 * Done.  Send it.
	 */
#ifndef SYS_WINNT
	n = send(sockfd, (char *)&reqpkt, (unsigned)(REQ_LEN_NOMAC + n), 0);
	if (n < 0) {
		msyslog(LOG_ERR, "send to NTP server failed: %m");
		return 0;	/* maybe should exit */
	}
#else
	/* In the NT world, documentation seems to indicate that there
	 * exist _write and _read routines that can be used to do blocking
	 * I/O on sockets. Problem is these routines require a socket
	 * handle obtained through the _open_osf_handle C run-time API
	 * of which there is no explanation in the documentation. We need
	 * nonblocking write's and read's anyway for our purpose here.
	 * We're therefore forced to deviate a little bit from the Unix
	 * model here and use the ReadFile and WriteFile Win32 I/O API's
	 * on the socket
	 */
	overlap.Offset = overlap.OffsetHigh = (DWORD)0;
	overlap.hEvent = hReadWriteEvent;
	ret = WriteFile((HANDLE)sockfd, (char *)&reqpkt, REQ_LEN_NOMAC + n,
			(LPDWORD)&NumberOfBytesWritten, (LPOVERLAPPED)&overlap);
	if ((ret == FALSE) && (GetLastError() != ERROR_IO_PENDING)) {
		msyslog(LOG_ERR, "send to NTP server failed: %m");
		return 0;
	}
	dwWait = WaitForSingleObject(hReadWriteEvent, (DWORD) TIMEOUT_SEC * 1000);
	if ((dwWait == WAIT_FAILED) || (dwWait == WAIT_TIMEOUT)) {
		if (dwWait == WAIT_FAILED)
		    msyslog(LOG_ERR, "WaitForSingleObject failed: %m");
		return 0;
	}
#endif /* SYS_WINNT */
    

	/*
	 * Wait for a response.  A weakness of the mode 7 protocol used
	 * is that there is no way to associate a response with a
	 * particular request, i.e. the response to this configuration
	 * request is indistinguishable from that to any other.  I should
	 * fix this some day.  In any event, the time out is fairly
	 * pessimistic to make sure that if an answer is coming back
	 * at all, we get it.
	 */
	for (;;) {
		FD_ZERO(&fdset);
		FD_SET(sockfd, &fdset);
		tvout.tv_sec = TIMEOUT_SEC;
		tvout.tv_usec = TIMEOUT_USEC;

		n = select(sockfd + 1, &fdset, (fd_set *)0,
			   (fd_set *)0, &tvout);

		if (n < 0)
		{
			msyslog(LOG_ERR, "select() fails: %m");
			return 0;
		}
		else if (n == 0)
		{
			if(debug)
			    msyslog(LOG_DEBUG, "select() returned 0.");
			return 0;
		}

#ifndef SYS_WINNT
		n = recv(sockfd, (char *)&reqpkt, REQ_LEN_MAC, 0);
		if (n <= 0) {
			if (n < 0) {
				msyslog(LOG_ERR, "recv() fails: %m");
				return 0;
			}
			continue;
		}
#else /* Overlapped I/O used on non-blocking sockets on Windows NT */
		ret = ReadFile((HANDLE)sockfd, (char *)&reqpkt, (DWORD)REQ_LEN_MAC,
			       (LPDWORD)&NumberOfBytesRead, (LPOVERLAPPED)&overlap);
		if ((ret == FALSE) && (GetLastError() != ERROR_IO_PENDING)) {
			msyslog(LOG_ERR, "ReadFile() fails: %m");
			return 0;
		}
		dwWait = WaitForSingleObject(hReadWriteEvent, (DWORD) TIMEOUT_SEC * 1000);
		if ((dwWait == WAIT_FAILED) || (dwWait == WAIT_TIMEOUT)) {
			if (dwWait == WAIT_FAILED) {
				msyslog(LOG_ERR, "WaitForSingleObject fails: %m");
				return 0;
			}
			continue;
		}
		n = NumberOfBytesRead;
#endif /* SYS_WINNT */

		/*
		 * Got one.  Check through to make sure it is what
		 * we expect.
		 */
		if (n < RESP_HEADER_SIZE) {
			msyslog(LOG_ERR, "received runt response (%d octets)",
				n);
			continue;
		}

		if (!ISRESPONSE(reqpkt.rm_vn_mode)) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO, "received non-response packet");
#endif
			continue;
		}

		if (ISMORE(reqpkt.rm_vn_mode)) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO, "received fragmented packet");
#endif
			continue;
		}

		if ( ( (INFO_VERSION(reqpkt.rm_vn_mode) < 2)
		       || (INFO_VERSION(reqpkt.rm_vn_mode) > NTP_VERSION))
		     || INFO_MODE(reqpkt.rm_vn_mode) != MODE_PRIVATE) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "version (%d/%d) or mode (%d/%d) incorrect",
				    INFO_VERSION(reqpkt.rm_vn_mode),
				    NTP_VERSION,
				    INFO_MODE(reqpkt.rm_vn_mode),
				    MODE_PRIVATE);
#endif
			continue;
		}

		if (INFO_SEQ(reqpkt.auth_seq) != 0) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "nonzero sequence number (%d)",
				    INFO_SEQ(reqpkt.auth_seq));
#endif
			continue;
		}

		if (reqpkt.implementation != IMPL_XNTPD ||
		    reqpkt.request != REQ_HOSTNAME_ASSOCID) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "implementation (%d/%d) or request (%d/%d) incorrect",
				    reqpkt.implementation, IMPL_XNTPD,
				    reqpkt.request, REQ_HOSTNAME_ASSOCID);
#endif
			continue;
		}

		if (INFO_NITEMS(reqpkt.err_nitems) != 0 ||
		    INFO_MBZ(reqpkt.mbz_itemsize) != 0 ||
		    INFO_ITEMSIZE(reqpkt.mbz_itemsize) != 0) {
#ifdef DEBUG
			if (debug > 1)
			    msyslog(LOG_INFO,
				    "nitems (%d) mbz (%d) or itemsize (%d) nonzero",
				    INFO_NITEMS(reqpkt.err_nitems),
				    INFO_MBZ(reqpkt.mbz_itemsize),
				    INFO_ITEMSIZE(reqpkt.mbz_itemsize));
#endif
			continue;
		}

		n = INFO_ERR(reqpkt.err_nitems);
		switch (n) {
		    case INFO_OKAY:
			/* success */
			return 1;
		
		    case INFO_ERR_IMPL:
			msyslog(LOG_ERR,
				"server reports implementation mismatch!!");
			return 0;
		
		    case INFO_ERR_REQ:
			msyslog(LOG_ERR,
				"server claims configuration request is unknown");
			return 0;
		
		    case INFO_ERR_FMT:
			msyslog(LOG_ERR,
				"server indicates a format error occurred(!!)");
			return 0;

		    case INFO_ERR_NODATA:
			msyslog(LOG_ERR,
				"server indicates no data available (shouldn't happen)");
			return 0;
		
		    case INFO_ERR_AUTH:
			msyslog(LOG_ERR,
				"server returns a permission denied error");
			return 0;

		    default:
			msyslog(LOG_ERR,
				"server returns unknown error code %d", n);
			return 0;
		}
	}
}


/*
 * doconfigure - attempt to resolve names and configure the server
 */
static void
doconfigure(
	int dores
	)
{
	register struct dns_entry *de;
	register struct dns_entry *deremove;

	de = dns_entries;
	while (de != NULL) {
#ifdef DEBUG
		if (debug > 1) {
			struct in_addr si;

			si.s_addr = de->de_peeraddr;
			msyslog(LOG_INFO,
			    "doconfigure: name: <%s> peeraddr: %s",
			    de->de_hostname, inet_ntoa(si));
		}
#endif
		if (dores && (de->de_hostname[0] == 0 || de->de_peeraddr == 0)) {
			if (!findhostaddr(de)) {
				struct in_addr si;

				si.s_addr = de->de_peeraddr;
				msyslog(LOG_ERR,
					"couldn't resolve <%s>/%s, giving up on it",
					de->de_hostname, inet_ntoa(si));
				deremove = de;
				de = deremove->de_next;
				removeentry(deremove);
				continue;
			}
		}

		if (de->de_hostname[0] && de->de_peeraddr != 0) {
			/* Send the answer */
			if (host_assoc(&de->de_info)) {
				struct in_addr si;

				si.s_addr = de->de_peeraddr;
				msyslog(LOG_INFO,
					"resolved <%s>/%s, done with it",
					de->de_hostname, inet_ntoa(si));

				deremove = de;
				de = deremove->de_next;
				removeentry(deremove);
				continue;
			}
#ifdef DEBUG
			if (debug > 1) {
				msyslog(LOG_INFO,
				    "doconfigure: host_assoc() FAILED, maybe next time.");
			}
#endif
		}
		de = de->de_next;
	}
}
