#ifndef _PRAND_CMD_H_
#define _PRAND_CMD_H_

static const char *cmds[] = {
	"/bin/ps -alwx 2>&1",
	"/usr/etc/arp -an 2>&1",
	"/usr/ucb/netstat -an 2>&1",
	"/usr/bin/df  2>&1",
	"/usr/ucb/uptime  2>&1",
	"/usr/ucb/netstat -s 2>&1",
	"/usr/bin/iostat  2>&1",
	"/usr/ucb/vmstat  2>&1",
	"/usr/ucb/w  2>&1",
	NULL
};

static const char *dirs[] = {
	"/tmp",
	"/var/tmp",
	".",
	"/",
	"/var/spool",
	"/var/adm",
	"/dev",
	"/var/spool/mail",
	NULL
};

static const char *files[] = {
	"/var/spool/mqueue/syslog",
	"/var/adm/wtmp",
	"/var/adm/lastlog",
	NULL
};

#endif /* _PRAND_CMD_H_ */
