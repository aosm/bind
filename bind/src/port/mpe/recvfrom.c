#include "port_before.h"
#undef recvfrom
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <errno.h>
#include <stdio.h>

int
__bind_mpe_recvfrom(int s, void *buf, size_t len, int flags,
		    struct sockaddr *from, int *fromlen) {
	int n;

	/* MPE can only receive a maximum of 30000 bytes */
	if (len > 30000) len = 30000;

	/* Verify the from length is sized properly */
	if (fromlen != NULL && 
	   *fromlen != sizeof(struct sockaddr_in) && 
	   *fromlen != sizeof(struct sockaddr_un)) {
		int sa_len;
		struct sockaddr_in sa;

		sa_len = sizeof(sa);
		if (getsockname(s, &sa, &sa_len) < 0 && errno == EAFNOSUPPORT) {
			*fromlen = sizeof(struct sockaddr_un);
		} else {
			*fromlen = sizeof(struct sockaddr_in);
		}
	}

	n = recvfrom(s, buf, len, flags, from, fromlen);
	if (n == -1 && errno == EOPNOTSUPP) {
		n = recv(s, buf, len, flags);
		if (n == -1)
			return (-1);
		if (from != NULL && getpeername(s, from, fromlen) < 0)
			return (-1);
	}
	return (n);
}
