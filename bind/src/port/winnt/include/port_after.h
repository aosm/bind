#ifndef _PORT_AFTER_H
#define _PORT_AFTER_H

#include <pathnames.h>

/* This is a reserved keyword for COM.  BIND wants to use it. */
#undef interface

/*
 * Define fnctl() for NT
 */
#include <nt_fcntl.h>
/*
 * Signal handling
 */
#include <nt_signal.h>
/*
 * _chdir()
 */
#include <direct.h>
/*
 * strerror() et. al.
 */
#include <string.h>

/*
 * This is only used in conjunction with AF_UNIX, but we define it
 * so the compiler shuts up
 */
struct sockaddr_un {
	short int sun_family;
	char sun_path[108];
};

/*
 * Winsock defines this struct as in_addr6.  res_mkupdate.c wants in6_addr.  Odd.
 */
struct in6_addr {
		u_char	s6_addr[16];	/* IPv6 address */
};

/* From Solaris 2.5 sys/netinet/in.h */
#define IN_EXPERIMENTAL(i) (((long)(i) & 0xe0000000) == 0xe0000000)

/* NT event log does not support facility level */
#define LOG_KERN	0
#define LOG_USER	0
#define LOG_MAIL	0
#define LOG_DAEMON	0
#define LOG_AUTH	0
#define LOG_SYSLOG	0
#define LOG_LPR		0
#define LOG_LOCAL0	0
#define LOG_LOCAL1	0
#define LOG_LOCAL2	0
#define LOG_LOCAL3	0
#define LOG_LOCAL4	0
#define LOG_LOCAL5	0
#define LOG_LOCAL6	0
#define LOG_LOCAL7	0

#define LOG_EMERG       0       /* system is unusable */
#define LOG_ALERT       1       /* action must be taken immediately */
#define LOG_CRIT        2       /* critical conditions */
#define LOG_ERR         3       /* error conditions */
#define LOG_WARNING     4       /* warning conditions */
#define LOG_NOTICE      5       /* normal but signification condition */
#define LOG_INFO        6       /* informational */
#define LOG_DEBUG       7       /* debug-level messages */

# define STDIN_FILENO	0
# define STDOUT_FILENO	1
# define STDERR_FILENO	2

#define EADDRINUSE		WSAEADDRINUSE
#define EMSGSIZE		WSAEMSGSIZE
#define EWOULDBLOCK		WSAEWOULDBLOCK
#define EAFNOSUPPORT		WSAEAFNOSUPPORT
#define ECONNREFUSED		WSAECONNREFUSED
#define ETIMEDOUT		WSAETIMEDOUT
#define ECONNRESET		WSAECONNRESET
#define EINPROGRESS		WSAEINPROGRESS
#define ECONNABORTED		WSAECONNABORTED
#define EHOSTUNREACH		WSAEHOSTUNREACH
#define EHOSTDOWN		WSAEHOSTDOWN
#define ENETUNREACH		WSAENETUNREACH
#define ENETDOWN		WSAENETDOWN
#define ENOTSOCK		WSAENOTSOCK
#define ENOTCONN		WSAENOTCONN
#define ETOOMANYREFS		WSAETOOMANYREFS
#define EPROTOTYPE		WSAEPROTOTYPE
#define EDESTADDRREQ		WSAEDESTADDRREQ
#define EPROTONOSUPPORT         WSAEPROTONOSUPPORT

/* setitimer does not exist in NT */
#define NEED_SETITIMER

/* NT has no nice - just make dummy */
#define nice(x)

#define WAIT_T int

#define NEED_STRSEP
extern char *strsep(char **stringp, const char *delim);

#define NEED_READV
#define readv __readv
extern int __readv(int, const struct iovec*, int);

#define NEED_WRITEV
#define writev __writev
extern int __writev(int, const struct iovec*, int);

#define NEED_GETTIMEOFDAY
extern int gettimeofday(struct timeval *tvp, struct _TIMEZONE *tzp);

#define NEED_UTIMES
#define utimes __utimes
int __utimes(char *, struct timeval *);

#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 256
#endif

#define __SS_MAXSIZE 128
#define __SS_ALLIGSIZE (sizeof (long))

struct sockaddr_storage {
#ifdef  HAVE_SA_LEN
        u_int8_t        ss_len;       /* address length */
        u_int8_t        ss_family;    /* address family */
        char            __ss_pad1[__SS_ALLIGSIZE - 2 * sizeof(u_int8_t)];
        long            __ss_align;
        char            __ss_pad2[__SS_MAXSIZE - 2 * __SS_ALLIGSIZE];
#else
        u_int16_t       ss_family;    /* address family */
        char            __ss_pad1[__SS_ALLIGSIZE - sizeof(u_int16_t)];
        long            __ss_align;
        char            __ss_pad2[__SS_MAXSIZE - 2 * __SS_ALLIGSIZE];
#endif
};

#ifndef IN6ADDR_ANY_INIT
#define	IN6ADDR_ANY_INIT	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
#endif
#ifndef IN6ADDR_LOOPBACK_INIT
#define	IN6ADDR_LOOPBACK_INIT	{{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}
#endif

#define in6_addr in_addr6	/* Required for pre RFC2133 implementations. */
#define in6addr_any isc_in6addr_any

#ifndef LIB
/* Import these if we are not the DLL */
__declspec(dllimport) const struct in6_addr isc_in6addr_any;
__declspec(dllimport) const struct in6_addr isc_in6addr_loopback;
#else
__declspec(dllexport) const struct in6_addr isc_in6addr_any;
__declspec(dllexport) const struct in6_addr isc_in6addr_loopback;
#endif

#ifndef IN6_ARE_ADDR_EQUAL
#define IN6_ARE_ADDR_EQUAL(a,b) \
   (memcmp(&(a)->s6_addr[0], &(b)->s6_addr[0], sizeof(struct in6_addr)) == 0)
#endif

#ifndef IN6_IS_ADDR_UNSPECIFIED
#define IN6_IS_ADDR_UNSPECIFIED(a)      \
	IN6_ARE_ADDR_EQUAL(a, &in6addr_any)
#endif

#ifndef IN6_IS_ADDR_LOOPBACK
#define IN6_IS_ADDR_LOOPBACK(a)		\
	IN6_ARE_ADDR_EQUAL(a, &isc_in6addr_loopback)
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

#ifndef IN6_IS_ADDR_SITELOCAL
#define IN6_IS_ADDR_SITELOCAL(a)        \
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0xc0))
#endif

#ifndef IN6_IS_ADDR_LINKLOCAL
#define IN6_IS_ADDR_LINKLOCAL(a)	\
	(((a)->s6_addr[0] == 0xfe) && (((a)->s6_addr[1] & 0xc0) == 0x80))
#endif

#ifndef IN6_IS_ADDR_MULTICAST
#define IN6_IS_ADDR_MULTICAST(a)        ((a)->s6_addr[0] == 0xff)
#endif

#ifndef __IPV6_ADDR_MC_SCOPE
#define __IPV6_ADDR_MC_SCOPE(a)         ((a)->s6_addr[1] & 0x0f)
#endif

#ifndef __IPV6_ADDR_SCOPE_SITELOCAL
#define __IPV6_ADDR_SCOPE_SITELOCAL 0x05
#endif

#ifndef __IPV6_ADDR_SCOPE_ORGLOCAL
#define __IPV6_ADDR_SCOPE_ORGLOCAL  0x08
#endif

#ifndef IN6_IS_ADDR_MC_SITELOCAL
#define IN6_IS_ADDR_MC_SITELOCAL(a)     \
	(IN6_IS_ADDR_MULTICAST(a) &&    \
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_SITELOCAL))
#endif

#ifndef IN6_IS_ADDR_MC_ORGLOCAL
#define IN6_IS_ADDR_MC_ORGLOCAL(a)      \
	(IN6_IS_ADDR_MULTICAST(a) &&    \
	 (__IPV6_ADDR_MC_SCOPE(a) == __IPV6_ADDR_SCOPE_ORGLOCAL))
#endif

#ifndef INET6_ADDRSTRLEN
#define INET6_ADDRSTRLEN 46
#endif

#ifndef MIN
# define MIN(x, y)	((x > y) ?y :x)
#endif
#ifndef MAX
# define MAX(x, y)	((x > y) ?x :y)
#endif

/* open() under unix allows setting of read/write permissions
 * at the owner, group and other levels.  These don't exist in NT
 * We'll just map them all to the NT equivalent 
 */

#define S_IREAD	_S_IREAD	/* read permission, owner */
#define S_IWRITE _S_IWRITE	/* write permission, owner */
#define S_IRUSR _S_IREAD	/* Owner read permission */
#define S_IWUSR _S_IWRITE	/* Owner write permission */
#define S_IRGRP _S_IREAD	/* Group read permission */
#define S_IWGRP _S_IWRITE	/* Group write permission */
#define S_IROTH _S_IREAD	/* Other read permission */
#define S_IWOTH _S_IWRITE	/* Other write permission */

#ifndef S_ISCHR
# ifndef S_IFMT
#  define S_IFMT 0170000
# endif
# ifndef S_IFCHR
#  define S_IFCHR 0020000
# endif
# define S_ISCHR(m)   ((m & S_IFMT) == S_IFCHR) 
#endif

#ifndef S_ISDIR
# ifndef S_IFMT
#  define S_IFMT 0170000
# endif
# ifndef S_IFDIR
#  define S_IFDIR 0040000
# endif
# define S_ISDIR(m)	((m & S_IFMT) == S_IFDIR)
#endif

#ifndef S_ISREG
# ifndef S_IFMT
#  define S_IFMT 0170000
# endif
# ifndef S_IFREG
#  define S_IFREG 0100000
# endif
# define S_ISREG(m)	((m & S_IFMT) == S_IFREG)
#endif

#ifndef S_ISFIFO
# ifndef S_IFMT
#  define S_IFMT 0170000
# endif
# ifndef S_IFIFO
#  define S_IFIFO 0010000
# endif
# define S_ISFIFO(m)	((m & S_IFMT) == S_IFIFO)
#endif

#define sleep(t) Sleep(t*1000)

/* Define these to allow dig to build properly */
#define WCOREDUMP(status)	0
#define vfork() -1
#define wait(status) -1

/* This gets used by the command parser in nslookup */

#define YY_SKIP_YYWRAP
#define yywrap() 1

#ifndef ISC_FACILITY
#define ISC_FACILITY LOG_DAEMON
#endif

/* String separator for Windows is the backslash */

#define PATH_SEP '\\'
#define UNUSED(x) (x) = (x)
#define DE_CONST(konst, var) \
	do { \
		union { const void *k; void *v; } _u; \
		_u.k = konst; \
		var = _u.v; \
	} while (0) 
#endif /* _PORT_AFTER_H */
