#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define SIG_FN void
#define SETGRENT_VOID
#define ISC_SOCKLEN_T int

#define __NO_INCLUDE_WARN__

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#include <time.h>
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
