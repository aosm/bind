#include <sched.h>	/* struct timespec */
#include <limits.h>	/* _POSIX_PATH_MAX */
#include <sys/select.h>

#define PATH_MAX _POSIX_PATH_MAX
#define MAXPATHLEN _POSIX_PATH_MAX
#define ISC_SOCKLEN_T int

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#define LITTLE_ENDIAN  1234
#define BYTE_ORDER LITTLE_ENDIAN
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
