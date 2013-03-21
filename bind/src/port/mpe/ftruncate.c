/*
 * ftruncate - set file size, BSD Style
 *
 * shortens or enlarges the file as neeeded
 * uses some undocumented locking call. It is known to work on SCO unix,
 * other vendors should try.
 * The #error directive prevents unsupported OSes
 */

#include "port_before.h"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <mpe.h>
#include "longpointer.h"

extern void FCONTROL(short, short, longpointer);
extern void PRINTFILEINFO(int);

int __bind_mpe_ftruncate(int fd, long wantsize);

int __bind_mpe_ftruncate(int fd, long wantsize) {

int ccode_return,dummy=0;

if (lseek(fd, wantsize, SEEK_SET) < 0) {
        return (-1);
}

FCONTROL(_mpe_fileno(fd),6,__bind_mpe_longaddr(&dummy)); /* Write new EOF */
if ((ccode_return=ccode()) != CCE) {
        fprintf(stderr,"MPE ftruncate failed, ccode=%d, wantsize=%ld\n",ccode_return,wantsize);
        PRINTFILEINFO(_mpe_fileno(fd));
	errno = ESYSERR;
	return (-1);
}

return (0);
}
