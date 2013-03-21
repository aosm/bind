#ifndef _PRAND_CMD_H_
#define _PRAND_CMD_H_

static const char *cmds[] = {
	"/bin/ps -ef 2>&1",
	NULL
};

static const char *dirs[] = {
	"/tmp",
	".",
	"/",
	"/usr/adm",
	"/var/adm",
	"/dev",
	"/usr/mail",
	NULL
};

static const char *files[] = {
	NULL
};

#endif /* _PRAND_CMD_H_ */
