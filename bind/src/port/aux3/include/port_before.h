#define WANT_IRS_NIS
#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define SIG_FN void
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 
#endif
#define BIG_ENDIAN	4321
#define BYTE_ORDER	BIG_ENDIAN
#define ISC_SOCKLEN_T int

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#include <sys/types.h>

#include <limits.h>	/* _POSIX_PATH_MAX */
#include <sys/times.h>
#include <sys/time.h>
struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* nanoseconds */
};

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
#ifdef PRINTFCHECKS
#define ISC_PRINTF_LIKE(x,y)
#else
#define ISC_PRINTF_LIKE(x,y) __printflike(x,y)
#endif
