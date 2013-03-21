#include "port_before.h"
#undef fchown
#include <unistd.h>
#include <fcntl.h>
#include <mpe.h>
#include <limits.h>
#include "port_after.h"

int __bind_mpe_fchown(int fd, uid_t owner, gid_t group) {

struct pascal_string {
  int length;
  char buffer[PATH_MAX+1];
};

struct pascal_string filename;

extern void FFILEINFO(int, int, void *, int);

/* Initialize the filename buffer to the maximum length */

filename.length = PATH_MAX;

/* Obtain the filename of the open file descriptor */

FFILEINFO(_MPE_FILENO(fd),80,&filename,0);
if (ccode() != CCE) {
  /* There was an error, so just return a null filename */
  filename.buffer[0] = '\0';
}

/* Change the file ownership and return */

return chown(filename.buffer, owner, group);
}
