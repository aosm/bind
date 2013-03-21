#define __EXTENSIONS__
#define SVR4
#define SIG_FN void
#define ISC_SOCKLEN_T int
#define _POSIX_TIMERS

#define NEED_DAEMON
int daemon(int nochdir, int noclose);

#include <limits.h>	/* _POSIX_PATH_MAX */

#define IFNAMSIZ 16	/* used in <net/route.h> */


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
