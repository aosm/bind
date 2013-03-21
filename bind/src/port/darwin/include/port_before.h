#define WANT_IRS_NIS
#define WANT_IRS_PW
#define HAVE_PW_CLASS
#define SIG_FN void
#define ts_sec tv_sec
#define ts_nsec tv_nsec
#define GETGROUPLIST_ARGS const char *name, gid_t basegid, gid_t *groups, \
		      int *ngroups
#define ISC_SOCKLEN_T int
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else
#define ISC_FORMAT_PRINTF(fmt, args)
#endif
