#define __EXTENSIONS__
#define SVR4
#define SIG_FN void
#define ISC_SOCKLEN_T int
#define _POSIX_TIMERS

#include <limits.h>	/* _POSIX_PATH_MAX */
#include <sys/byteorder.h>
#include <sys/sockio.h>
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
