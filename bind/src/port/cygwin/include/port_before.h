#ifndef PORT_BEFORE_H
#define PORT_BEFORE_H

#undef WANT_IRS_NIS
#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define SIG_FN void
#define ISC_SOCKLEN_T int

#define _PATH_HEQUIV      "/usr/local/etc/hosts.equiv"
#define _PATH_HOSTS     "/usr/local/etc/hosts"
#define _PATH_NETWORKS  "/usr/local/etc/networks"
#define _PATH_PROTOCOLS "/usr/local/etc/protocols"
#define _PATH_SERVICES  "/usr/local/etc/services"
#define _PATH_RESCONF     "/usr/local/etc/resolv.conf"
#define _PATH_IRS_CONF "/usr/local/etc/irs.conf"
#define _PATH_NETGROUP "/usr/local/etc/netgroup"
#define _PATH_HESIOD_CONF "/usr/local/etc/hesiod.conf"

#define EVENTLIB_TIME_CHECKS

#include <time.h>
#ifndef __time_t_defined
struct timespec {
	time_t	tv_sec;		/* seconds */
	long	tv_nsec;	/* nanoseconds */
};
#endif

#include <limits.h>

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#define _LITTLE_ENDIAN

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
#endif /*PORT_BEFORE_H*/
