#define MPE
#define _POSIX_SOURCE
#define _SOCKET_SOURCE
#define IS_SOCKET_CLIB_ITSELF

/* This top portion comes from the HPUX port and is mostly unaltered. */

#undef WANT_IRS_NIS
#undef WANT_IRS_PW
#define MISSING_GR_PASSWD
#define SIG_FN void
#define ISC_SOCKLEN_T int

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#define BIG_ENDIAN      4321
#define BYTE_ORDER      BIG_ENDIAN

#include <limits.h>	/* _POSIX_PATH_MAX */

/* This bottom portion is MPE specific. */

#include <sys/types.h>

#define bind		__bind_mpe_bind
#define fchown		__bind_mpe_fchown
#define fsync		__bind_mpe_fsync
#define ftruncate	__bind_mpe_ftruncate
#define nice		__bind_mpe_nice
#define fcntl		__bind_mpe_fcntl
#define recvfrom	__bind_mpe_recvfrom
#define setgid		__bind_mpe_setgid
#define setuid		__bind_mpe_setuid
#define initgroups	__bind_mpe_initgroups
#define endgrent	__bind_mpe_endgrent	
#define endpwent	__bind_mpe_endpwent	
#define getpass		__bind_mpe_getpass

#ifndef _MPE_TIMESPEC
#define _MPE_TIMESPEC
struct timespec { 
        time_t  tv_sec;         /* seconds */ 
        long    tv_nsec;        /* nanoseconds */
};
#endif
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
