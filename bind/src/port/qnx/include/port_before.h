
#define LITTLE_ENDIAN	1234
#define BYTE_ORDER	LITTLE_ENDIAN

#include <sys/select.h>
#include <signal.h>
#include <ioctl.h>
#include <unix.h>
#include <sys/cdefs.h>
#define SIG_FN	__sig_func
#define ISC_SOCKLEN_T int
#define POSIX_SIGNALS
#define USE_POSIX
#define MIN	min
#define MAX	max
#define PORT_NONBLOCK	O_NONBLOCK
#define HAVE_SA_LEN

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
