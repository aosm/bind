#define __EXTENSIONS__
#define SVR4
#define SIG_FN void
#define ISC_SOCKLEN_T int
#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED 1
#define _POSIX_TIMERS

#include <limits.h>	/* _POSIX_PATH_MAX */
        typedef unsigned char u_char;
        typedef unsigned short u_short;
        typedef unsigned int u_int;
        typedef unsigned long u_long;



#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
