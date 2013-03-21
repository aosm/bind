#define SVR4
#define WANT_IRS_NIS
#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define SIG_FN void
#define ISC_SOCKLEN_T int

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#include <limits.h>	/* _POSIX_PATH_MAX */
#include <sys/endian.h> /* endianness */

#define IRIX_EMUL_IOCTL_SIOCGIFCONF

#ifdef IRIX_EMUL_IOCTL_SIOCGIFCONF
#include <sys/types.h>
#include <net/if.h>	
		/* struct ifconf, struct if_msghdr, struct ifa_msghdr,
		 * struct ifreq
		 */

int emul_ioctl(	struct ifconf * ifc );

#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#endif	/* #ifdef IRIX_EMUL_IOCTL_SIOCGIFCONF */
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
