#include "port_before.h"
#include <errno.h>
#include <fcntl.h>
#include <mpe.h>
#include <stdio.h>
#include "longpointer.h"

extern void FCONTROL(short, short, longpointer);
extern void PRINTFILEINFO(int);

int __bind_mpe_fsync(int file);
 
int __bind_mpe_fsync(int file) {

int ccode_return,dummy=0;

/* Complete I/O */
FCONTROL(_mpe_fileno(file),2,__bind_mpe_longaddr(&dummy));
if ((ccode_return=ccode()) != CCE) {
  fprintf(stderr,"MPE fsync complete failed, ccode=%d\n",ccode_return);
  PRINTFILEINFO(_mpe_fileno(file));
  errno = ESYSERR;
  return -1;
}

return 0;
}
