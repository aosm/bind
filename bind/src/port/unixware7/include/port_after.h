#ifndef	PORT_AFTER_H

#define	PORT_AFTER_H
#define HAVE_SA_LEN
#define USE_POSIX
#define POSIX_SIGNALS
#define USE_WAITPID
#define HAVE_GETRUSAGE
#define HAVE_FCHMOD
#define SETGRENT_VOID
#define SETPWENT_VOID
#define IP_OPT_BUF_SIZE 40
#define NEED_PSELECT
#define SIOCGIFCONF_ADDR
#define HAVE_CHROOT
#define CAN_CHANGE_ID

#define PORT_NONBLOCK	O_NONBLOCK
#define PORT_WOULDBLK	EWOULDBLOCK
#define WAIT_T		int

#ifndef MIN
# define MIN(x, y)	((x > y) ?y :x)
#endif
#ifndef MAX
# define MAX(x, y)	((x > y) ?x :y)
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in6_f.h>
#include <netinet/in6.h>
#include <sys/param.h>
#include <sys/bitypes.h>
#include <sys/time.h>

extern int gethostname(char *, size_t);

#define NEED_STRSEP
extern char *strsep(char **, const char *);

#define NEED_DAEMON
int daemon(int nochdir, int noclose);

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 255
#endif

#ifndef ISC_FACILITY
#define ISC_FACILITY LOG_DAEMON
#endif

int isc__gettimeofday(struct timeval *, struct timezone *);
#define gettimeofday isc__gettimeofday

#define UNUSED(x) (x) = (x)
#define DE_CONST(konst, var) \
	do { \
		union { const void *k; void *v; } _u; \
		_u.k = konst; \
		var = _u.v; \
	} while (0) 

#ifndef IN6_IS_ADDR_LINKLOCAL
#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#endif

#ifndef IN6_IS_ADDR_LINKLOCAL
#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#endif

#ifndef IN6_IS_ADDR_V4COMPAT
#define IN6_IS_ADDR_V4COMPAT(a)		\
	((a)->s6_addr[0] == 0x00 && (a)->s6_addr[1] == 0x00 && \
	 (a)->s6_addr[2] == 0x00 && (a)->s6_addr[3] == 0x00 && \
	 (a)->s6_addr[4] == 0x00 && (a)->s6_addr[5] == 0x00 && \
	 (a)->s6_addr[6] == 0x00 && (a)->s6_addr[7] == 0x00 && \
	 (a)->s6_addr[8] == 0x00 && (a)->s6_addr[9] == 0x00 && \
	 (a)->s6_addr[10] == 0x00 && (a)->s6_addr[11] == 0x00 && \
	 ((a)->s6_addr[12] != 0x00 || (a)->s6_addr[13] != 0x00 || \
	  (a)->s6_addr[14] != 0x00 || \
	  ((a)->s6_addr[15] != 0x00 && (a)->s6_addr[15] != 1)))
#endif

#ifndef IN6_IS_ADDR_V4MAPPED
#define IN6_IS_ADDR_V4MAPPED(a)		\
	((a)->s6_addr[0] == 0x00 && (a)->s6_addr[1] == 0x00 && \
	 (a)->s6_addr[2] == 0x00 && (a)->s6_addr[3] == 0x00 && \
	 (a)->s6_addr[4] == 0x00 && (a)->s6_addr[5] == 0x00 && \
	 (a)->s6_addr[6] == 0x00 && (a)->s6_addr[7] == 0x00 && \
	 (a)->s6_addr[8] == 0x00 && (a)->s6_addr[9] == 0x00 && \
	 (a)->s6_addr[10] == 0xff && (a)->s6_addr[11] == 0xff)
#endif

#ifndef IN6_IS_ADDR_LOOPBACK
extern const struct in6_addr isc_in6addr_loopback;
#define IN6_IS_ADDR_LOOPBACK(a)		\
	IN6_ARE_ADDR_EQUAL(a, &isc_in6addr_loopback)
#endif
#endif /* ! PORT_AFTER_H */
