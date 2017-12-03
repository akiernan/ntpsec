/*
 * clocktime - compute the NTP date from a day of year, hour, minute
 *	       and second.
 */
#include "config.h"
#include "ntp_fp.h"
#include "ntp_stdlib.h"
#include "ntp_calendar.h"

/*
 * We check that the time be within CLOSETIME seconds of the receive
 * time stamp.	This is about 4 hours, which hopefully should be wide
 * enough to collect most data, while close enough to keep things from
 * getting confused.
 */
#define	CLOSETIME	(4u*60u*60u)

/*
 * Since we try to match years, the result of a full search will not
 * change when we are already less than a half year from the receive
 * time stamp.	Since the length of a year is variable we use a
 * slightly narrower limit; this might require a full evaluation near
 * the edge, but will make sure we always get the correct result.
 */
#define NEARTIME	(182u * SECSPERDAY)

/*
 * local calendar helpers
 */
static int32_t  ntp_to_year(uint32_t, time_t);
static uint32_t year_to_ntp(int32_t);

/*
 * Take a time spec given as year, day-of-year, hour, minute and second
 * (in GMT/UTC) and convert it to a NTP time stamp in
 * '*ts_ui'.  There are two cases: ether the year is > 99, in which
 * case it is used, or it is < 99 in which case we ignore it and try
 * to deduce a year,
 *
 * The value will be in the range (rec_ui-0.5yrs) to
 * (rec_ui+0.5yrs). A hint for the current start-of-year will be
 * read from '*yearstart'.
 *
 * On return '*ts_ui' will always the best matching solution, and
 * '*yearstart' will receive the associated start-of-year.
 *
 * The function will tell if the result in 'ts_ui' is in CLOSETIME
 * (+/-4hrs) around the receive time by returning a non-zero value.
 *
 * Note: The function puts no constraints on the value ranges for the
 * time specification, but evaluates the effective seconds in
 * 32-bit arithmetic.
 */
int
clocktime(
	int	year	 ,	/* year */
	int	yday	 ,	/* day-of-year */
	int	hour	 ,	/* hour of day */
	int	minute	 ,	/* minute of hour */
	int	second	 ,	/* second of minute */
	time_t	pivot	 ,	/* pivot for time unfolding */
	uint32_t rec_ui	 ,	/* recent timestamp to get year from */
	uint32_t *yearstart,	/* cached start-of-year, secs from NTP epoch */
	uint32_t *ts_ui	 )	/* effective time stamp */
{
	uint32_t ystt[3];	/* year start */
	uint32_t test[3];	/* result time stamp */
	uint32_t diff[3];	/* abs difference to receive */
	int32_t y, idx, min;
	uint32_t tmp;
	
	/*
	 * Compute the offset into the year in seconds.	 Can't
	 * be negative as yday is 1-origin.
	 */
	tmp = ((uint32_t)second +
	       SECSPERMIN * ((uint32_t)minute +
			     MINSPERHR * ((uint32_t)hour +
					  HRSPERDAY * ((uint32_t)yday - 1))));
	/*
	 * Year > 1970 - from a 4-digit year stamp, must be greater
	 * than POSIX epoch. Means we're not dependent on the pivot
	 * value (derived from the packet receipt timestamp, and thus
	 * ultimately from the system clock) to be correct. CLOSETIME
	 * clipping to the receive time will *not* be applied in this
	 * case. These two lines thus make it possible to recover from
	 * a trashed or zeroed system clock.
	 *
	 * Warning: the hack in the NMEA driver that rectifies 4-digit
	 * years from 2-digit ones has an expiration date in 2399.
	 * After that this code will go badly wrong.
	 */
	if (year > 1970) {
	    *yearstart = year_to_ntp(year);
	    *ts_ui = *yearstart + tmp;
	    return true;
	}

        /*
	 * Year was too small to make sense, probably from a 2-digit
	 * year stamp.
	 * Based on the cached year start, do a first attempt. Be
	 * happy and return if this gets us better than NEARTIME to
	 * the receive time stamp. Do this only if the cached year
	 * start is not zero, which will not happen after 1900 for the
	 * next few thousand years.
	 */
	if (*yearstart) {
		/* -- get time stamp of potential solution */
		test[0] = (uint32_t)(*yearstart) + (unsigned int)tmp;
		/* -- calc absolute difference to receive time */
		diff[0] = test[0] - rec_ui;
		if (diff[0] >= 0x80000000u)
			diff[0] = ~diff[0] + 1;
		/* -- can't get closer if diff < NEARTIME */
		if (diff[0] < NEARTIME) {
			*ts_ui = test[0];
			return diff[0] < CLOSETIME;
		}
	}

	/*
	 * Now the dance begins. Based on the receive time stamp and
	 * the seconds offset in 'tmp', we make an educated guess
	 * about the year to start with. This takes us on the spot
	 * with a fuzz of +/-1 year.
	 *
	 * We calculate the effective timestamps for the three years
	 * around the guess and select the entry with the minimum
	 * absolute difference to the receive time stamp.
	 */
	y = ntp_to_year(rec_ui - tmp, pivot);
	for (idx = 0; idx < 3; idx++) {
		/* -- get year start of potential solution */
		ystt[idx] = year_to_ntp(y + idx - 1);
		/* -- get time stamp of potential solution */
		test[idx] = ystt[idx] + tmp;
		/* -- calc absolute difference to receive time */
		diff[idx] = test[idx] - rec_ui;
		if (diff[idx] >= 0x80000000u)
			diff[idx] = ~diff[idx] + 1;
	}
	/* -*- assume current year fits best, then search best fit */
	for (min = 1, idx = 0; idx < 3; idx++)
		if (diff[idx] < diff[min])
			min = idx;
	/* -*- store results and update year start */
	*ts_ui	   = test[min];
	*yearstart = ystt[min];

	/* -*- tell if we could get into CLOSETIME*/
	return diff[min] < CLOSETIME;
}

static int32_t
ntp_to_year(
    uint32_t ntp,
    time_t pivot)
{
	time64_t	     t;
	ntpcal_split s;

	t = ntpcal_ntp_to_ntp(ntp, pivot);
	s = ntpcal_daysplit(t);
	s = ntpcal_split_eradays(s.hi + DAY_NTP_STARTS - 1, NULL);
	return s.hi + 1;
}

static uint32_t
year_to_ntp(
	int32_t year)
{
	uint32_t days;
	days = (uint32_t)ntpcal_days_in_years(year-1) - DAY_NTP_STARTS + 1;
	return days * SECSPERDAY;
}
