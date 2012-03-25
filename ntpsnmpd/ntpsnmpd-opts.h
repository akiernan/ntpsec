/*  
 *  EDIT THIS FILE WITH CAUTION  (ntpsnmpd-opts.h)
 *  
 *  It has been AutoGen-ed  March 25, 2012 at 05:06:56 AM by AutoGen 5.14
 *  From the definitions    ntpsnmpd-opts.def
 *  and the template file   options
 *
 * Generated from AutoOpts 36:1:11 templates.
 *
 *  AutoOpts is a copyrighted work.  This header file is not encumbered
 *  by AutoOpts licensing, but is provided under the licensing terms chosen
 *  by the ntpsnmpd author or copyright holder.  AutoOpts is
 *  licensed under the terms of the LGPL.  The redistributable library
 *  (``libopts'') is licensed under the terms of either the LGPL or, at the
 *  users discretion, the BSD license.  See the AutoOpts and/or libopts sources
 *  for details.
 *
 * The ntpsnmpd program is copyrighted and licensed
 * under the following terms:
 *
 *  Copyright (C) 1970-2012 The University of Delaware, all rights reserved.
 *  This is free software. It is licensed for use, modification and
 *  redistribution under the terms of the NTP License, copies of which
 *  can be seen at:
 *    <http://ntp.org/license>
 *    <http://opensource.org/licenses/ntp-license.php>
 *
 *  Permission to use, copy, modify, and distribute this software and its
 *  documentation for any purpose with or without fee is hereby granted,
 *  provided that the above copyright notice appears in all copies and that
 *  both the copyright notice and this permission notice appear in
 *  supporting documentation, and that the name The University of Delaware not be used in
 *  advertising or publicity pertaining to distribution of the software
 *  without specific, written prior permission. The University of Delaware makes no
 *  representations about the suitability this software for any purpose. It
 *  is provided "as is" without express or implied warranty.
 */
/*
 *  This file contains the programmatic interface to the Automated
 *  Options generated for the ntpsnmpd program.
 *  These macros are documented in the AutoGen info file in the
 *  "AutoOpts" chapter.  Please refer to that doc for usage help.
 */
#ifndef AUTOOPTS_NTPSNMPD_OPTS_H_GUARD
#define AUTOOPTS_NTPSNMPD_OPTS_H_GUARD 1
#include "config.h"
#include <autoopts/options.h>

/*
 *  Ensure that the library used for compiling this generated header is at
 *  least as new as the version current when the header template was released
 *  (not counting patch version increments).  Also ensure that the oldest
 *  tolerable version is at least as old as what was current when the header
 *  template was released.
 */
#define AO_TEMPLATE_VERSION 147457
#if (AO_TEMPLATE_VERSION < OPTIONS_MINIMUM_VERSION) \
 || (AO_TEMPLATE_VERSION > OPTIONS_STRUCT_VERSION)
# error option template version mismatches autoopts/options.h header
  Choke Me.
#endif

/*
 *  Enumeration of each option:
 */
typedef enum {
    INDEX_OPT_NOFORK        =  0,
    INDEX_OPT_SYSLOG        =  1,
    INDEX_OPT_AGENTXSOCKET  =  2,
    INDEX_OPT_VERSION       =  3,
    INDEX_OPT_HELP          =  4,
    INDEX_OPT_MORE_HELP     =  5,
    INDEX_OPT_SAVE_OPTS     =  6,
    INDEX_OPT_LOAD_OPTS     =  7
} teOptIndex;

#define OPTION_CT    8
#define NTPSNMPD_VERSION       "4.2.7p269"
#define NTPSNMPD_FULL_VERSION  "ntpsnmpd 4.2.7p269"

/*
 *  Interface defines for all options.  Replace "n" with the UPPER_CASED
 *  option name (as in the teOptIndex enumeration above).
 *  e.g. HAVE_OPT(NOFORK)
 */
#define         DESC(n) (ntpsnmpdOptions.pOptDesc[INDEX_OPT_## n])
#define     HAVE_OPT(n) (! UNUSED_OPT(& DESC(n)))
#define      OPT_ARG(n) (DESC(n).optArg.argString)
#define    STATE_OPT(n) (DESC(n).fOptState & OPTST_SET_MASK)
#define    COUNT_OPT(n) (DESC(n).optOccCt)
#define    ISSEL_OPT(n) (SELECTED_OPT(&DESC(n)))
#define ISUNUSED_OPT(n) (UNUSED_OPT(& DESC(n)))
#define  ENABLED_OPT(n) (! DISABLED_OPT(& DESC(n)))
#define  STACKCT_OPT(n) (((tArgList*)(DESC(n).optCookie))->useCt)
#define STACKLST_OPT(n) (((tArgList*)(DESC(n).optCookie))->apzArgs)
#define    CLEAR_OPT(n) STMTS( \
                DESC(n).fOptState &= OPTST_PERSISTENT_MASK;   \
                if ((DESC(n).fOptState & OPTST_INITENABLED) == 0) \
                    DESC(n).fOptState |= OPTST_DISABLED; \
                DESC(n).optCookie = NULL )

/* * * * * *
 *
 *  Enumeration of ntpsnmpd exit codes
 */
typedef enum {
    NTPSNMPD_EXIT_SUCCESS = 0,
    NTPSNMPD_EXIT_FAILURE = 1
} ntpsnmpd_exit_code_t;
/*
 *  Make sure there are no #define name conflicts with the option names
 */
#ifndef     NO_OPTION_NAME_WARNINGS
# ifdef    NOFORK
#  warning undefining NOFORK due to option name conflict
#  undef   NOFORK
# endif
# ifdef    SYSLOG
#  warning undefining SYSLOG due to option name conflict
#  undef   SYSLOG
# endif
# ifdef    AGENTXSOCKET
#  warning undefining AGENTXSOCKET due to option name conflict
#  undef   AGENTXSOCKET
# endif
#else  /* NO_OPTION_NAME_WARNINGS */
# undef NOFORK
# undef SYSLOG
# undef AGENTXSOCKET
#endif  /*  NO_OPTION_NAME_WARNINGS */

/* * * * * *
 *
 *  Interface defines for specific options.
 */
#define VALUE_OPT_NOFORK         'n'
#define VALUE_OPT_SYSLOG         'p'
#define VALUE_OPT_AGENTXSOCKET   2
#define VALUE_OPT_HELP          '?'
#define VALUE_OPT_MORE_HELP     '!'
#define VALUE_OPT_VERSION       INDEX_OPT_VERSION
#define VALUE_OPT_SAVE_OPTS     '>'
#define VALUE_OPT_LOAD_OPTS     '<'
#define SET_OPT_SAVE_OPTS(a)   STMTS( \
        DESC(SAVE_OPTS).fOptState &= OPTST_PERSISTENT_MASK; \
        DESC(SAVE_OPTS).fOptState |= OPTST_SET; \
        DESC(SAVE_OPTS).optArg.argString = (char const*)(a) )
/*
 *  Interface defines not associated with particular options
 */
#define ERRSKIP_OPTERR  STMTS(ntpsnmpdOptions.fOptSet &= ~OPTPROC_ERRSTOP)
#define ERRSTOP_OPTERR  STMTS(ntpsnmpdOptions.fOptSet |= OPTPROC_ERRSTOP)
#define RESTART_OPT(n)  STMTS( \
                ntpsnmpdOptions.curOptIdx = (n); \
                ntpsnmpdOptions.pzCurOpt  = NULL)
#define START_OPT       RESTART_OPT(1)
#define USAGE(c)        (*ntpsnmpdOptions.pUsageProc)(&ntpsnmpdOptions, c)
/* extracted from opthead.tlib near line 469 */

#ifdef  __cplusplus
extern "C" {
#endif


/* * * * * *
 *
 *  Declare the ntpsnmpd option descriptor.
 */
extern tOptions ntpsnmpdOptions;

#if defined(ENABLE_NLS)
# ifndef _
#   include <stdio.h>
static inline char* aoGetsText(char const* pz) {
    if (pz == NULL) return NULL;
    return (char*)gettext(pz);
}
#   define _(s)  aoGetsText(s)
# endif /* _() */

# define OPT_NO_XLAT_CFG_NAMES  STMTS(ntpsnmpdOptions.fOptSet |= \
                                    OPTPROC_NXLAT_OPT_CFG;)
# define OPT_NO_XLAT_OPT_NAMES  STMTS(ntpsnmpdOptions.fOptSet |= \
                                    OPTPROC_NXLAT_OPT|OPTPROC_NXLAT_OPT_CFG;)

# define OPT_XLAT_CFG_NAMES     STMTS(ntpsnmpdOptions.fOptSet &= \
                                  ~(OPTPROC_NXLAT_OPT|OPTPROC_NXLAT_OPT_CFG);)
# define OPT_XLAT_OPT_NAMES     STMTS(ntpsnmpdOptions.fOptSet &= \
                                  ~OPTPROC_NXLAT_OPT;)

#else   /* ENABLE_NLS */
# define OPT_NO_XLAT_CFG_NAMES
# define OPT_NO_XLAT_OPT_NAMES

# define OPT_XLAT_CFG_NAMES
# define OPT_XLAT_OPT_NAMES

# ifndef _
#   define _(_s)  _s
# endif
#endif  /* ENABLE_NLS */

#ifdef  __cplusplus
}
#endif
#endif /* AUTOOPTS_NTPSNMPD_OPTS_H_GUARD */
/* ntpsnmpd-opts.h ends here */
