#ifndef _PRAND_CMD_H_
#define _PRAND_CMD_H_

#ifndef HAVE_DEV_RANDOM
# define HAVE_DEV_RANDOM 1
#endif /* HAVE_DEV_RANDOM */

static const char *cmds[] = {
	"ps -alW 2>&1",
	"arp -a 2>&1",
	"netstat -an 2>&1",
	"/bin/df  2>&1",
	"dig com. soa +ti=1 +retry=0 2>&1",
	"uptime  2>&1",
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
	"/var/mail",
	"/home",
	NULL
};

static const char *files[] = {
	"/var/adm/messages",
	"/var/adm/wtmp",
	"/var/adm/lastlog",
	NULL
};

#endif /* _PRAND_CMD_H_ */
