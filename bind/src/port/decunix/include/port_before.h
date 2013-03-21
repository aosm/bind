#include <sys/bitypes.h>
typedef u_int8_t uint8_t;
typedef u_int16_t uint16_t;
typedef u_int32_t uint32_t;
typedef u_int64_t uint64_t;

/* 4.0 has the old sockaddr_storage w/ __ss_family. */
#define __ss_family ss_family

#define WANT_IRS_NIS
#undef WANT_IRS_PW
#undef WANT_IRS_GR
#define _SOCKADDR_LEN
#define HAS_PTHREADS
#define ISC_SOCKLEN_T int

#if defined(HAS_PTHREADS) && defined(_REENTRANT)
#define DO_PTHREADS
#endif

#define GROUP_R_RETURN int
#define GROUP_R_SET_RETURN int
#define GROUP_R_SET_RESULT GROUP_R_OK
#define GROUP_R_END_RETURN void
#define GROUP_R_END_RESULT(x) /*empty*/
#define GROUP_R_ARGS char *buf, int buflen, FILE **gr_fp
#define GROUP_R_ENT_ARGS FILE **f
#define GROUP_R_OK 0
#define GROUP_R_BAD (-1)
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups

#define HOST_R_RETURN int
#define HOST_R_SET_RETURN int
#define HOST_R_SET_RESULT HOST_R_OK
#define HOST_R_END_RETURN void
#define HOST_R_END_RESULT(x) /*empty*/
#define HOST_R_ARGS struct hostent_data *hdptr
#define HOST_R_ENT_ARGS HOST_R_ARGS
#define HOST_R_COPY hdptr
#define HOST_R_COPY_ARGS HOST_R_ARGS
#define HOST_R_ERRNO NULL
#define HOST_R_OK 0
#define HOST_R_BAD (-1)
#define HOSTENT_DATA

#define NET_R_RETURN int
#define NET_R_SET_RETURN int
#define NET_R_SET_RESULT NET_R_OK
#define NET_R_END_RETURN void
#define NET_R_END_RESULT(x) /*empty*/
#define NET_R_ARGS struct netent_data *ndptr
#define NET_R_ENT_ARGS NET_R_ARGS
#define NET_R_COPY ndptr
#define NET_R_COPY_ARGS NET_R_ARGS
#define NET_R_OK 0
#define NET_R_BAD (-1)
#define NETENT_DATA

#define NGR_R_RETURN int
#define NGR_R_SET_RETURN int
#define NGR_R_SET_RESULT NGR_R_OK
#define NGR_R_END_RETURN void
#define NGR_R_END_RESULT(x) /*empty*/
#define NGR_R_ARGS char *buf, int buflen
#define NGR_R_ENT_ARGS NGR_R_ARGS
#define NGR_R_COPY buf, buflen
#define NGR_R_COPY_ARGS NGR_R_ARGS
#define NGR_R_OK 1
#define NGR_R_BAD 0

#define PROTO_R_RETURN int
#define PROTO_R_SET_RETURN int
#define PROTO_R_SET_RESULT PROTO_R_OK
#define PROTO_R_END_RETURN void
#define PROTO_R_END_RESULT(x) /*empty*/
#define PROTO_R_ARGS struct protoent_data *pdptr
#define PROTO_R_ENT_ARGS PROTO_R_ARGS
#define PROTO_R_COPY pdptr
#define PROTO_R_COPY_ARGS PROTO_R_ARGS
#define PROTO_R_OK 0
#define PROTO_R_BAD (-1)
#define PROTOENT_DATA

#define PASS_R_RETURN int
#define PASS_R_SET_RETURN int
#define PASS_R_SET_RESULT PASS_R_OK
#define PASS_R_END_RETURN void
#define PASS_R_END_RESULT(x) /*empty*/
#define PASS_R_ARGS char *buf, int buflen, FILE **pw_fp
#define PASS_R_ENT_ARGS FILE **f
#define PASS_R_COPY buf, buflen
#define PASS_R_COPY_ARGS char *buf, int buflen
#define PASS_R_OK 0
#define PASS_R_BAD (-1)

#define SERV_R_RETURN int
#define SERV_R_SET_RETURN int
#define SERV_R_SET_RESULT SERV_R_OK
#define SERV_R_END_RETURN void
#define SERV_R_END_RESULT(x) /*empty*/
#define SERV_R_ARGS struct servent_data *ndptr
#define SERV_R_ENT_ARGS SERV_R_ARGS
#define SERV_R_COPY ndptr
#define SERV_R_COPY_ARGS SERV_R_ARGS
#define SERV_R_OK 0
#define SERV_R_BAD (-1)
#define SERVENT_DATA

#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
