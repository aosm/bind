#if !defined(__GNUC__)		
# define const
#endif

#define SIOCGIFCONF_ADDR

#define SIG_FN void
#define ISC_SOCKLEN_T int

/* #define EVENTLIB_DEBUG 1 /**/

#define USE_POSIX
#define POSIX_SIGNALS

#include <sys/types.h>
#include <limits.h>	/* _POSIX_PATH_MAX */

#define PATH_MAX _POSIX_PATH_MAX
#define MAXPATHLEN _POSIX_PATH_MAX

#include <stdio.h>	/* To avoid ptr/_ptr/__ptr name clash. */

#include <stdarg.h>

#define NEED_PSELECT
struct timespec {
        time_t  tv_sec;         /* seconds */
        long    tv_nsec;        /* nanoseconds */
};
 

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#define NO_SOCKADDR_UN
#endif

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
