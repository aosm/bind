/*
 * Copyright (c) 2000-2001 by Internet Software Consortium.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SOFTWARE CONSORTIUM DISCLAIMS
 * ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL INTERNET SOFTWARE
 * CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
 * PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
 * ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 */

#include "port_before.h"

#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>

#include "port_after.h"

static HINSTANCE winsockDLLHandle;

/*
 * sockets are file descriptors in UNIX.  This is not so in NT
 * We must keep track of what is a socket and what is an FD to
 * make everything flow right.
 */

/*
 * A list of the sockets currently open
 */
sockdata sockset[REAL_FD_SETSIZE];
int sockdescrip[REAL_FD_SETSIZE];
int sockcount = 0;


/*
 * Initialize for FD tracking, ioctl()
 */
void socketInit()
{
	int i;
	for(i=0; i < REAL_FD_SETSIZE; i++)
	{
		sockset[i].sock = INVALID_SOCKET;
		sockset[i].flags = 0;
		sockdescrip[i] = 0;
	}
	sockcount = 0;
	/* Do the same for files */
	fdFileInit();
}

/*
 * Find a socket in the list. 
 * Return -1 if not found.
 */
int sockindex(SOCKET s)
{
	int i = 0;
	while(sockset[i].sock != s && i < REAL_FD_SETSIZE)
		i++;

	if(i < REAL_FD_SETSIZE)
	{
	    return(i);
	}
	else {
		return(-1);
	}
}

/*
 * Add a socket to the list.  Request can get the index
 */
int sockin(SOCKET s)
{
	int i = 0;
	while(sockset[i].sock != INVALID_SOCKET && i < REAL_FD_SETSIZE)
		i++;

	if(i < REAL_FD_SETSIZE)
	{
		sockset[i].sock = s;
		sockset[i].flags = 0;
		sockdescrip[i] = 0;
		sockcount++;
	}
	return i;
}

/*
 * Remove a socket from the list
 */
void sockout(SOCKET s)
{
	int i = sockindex(s);

	if(i < REAL_FD_SETSIZE && i >= 0) {
		sockset[i].sock = INVALID_SOCKET;
		sockset[i].flags = 0;
		sockdescrip[i] = 0;
		sockcount--;
	}
}

/*
 * The only flags that could be set are O_APPEND, O_NONBLOCK, O_SYNC, O_ASYNC.
 * For now we only will support O_NONBLOCK as it's the only one BIND uses.
 */
int setsockflags(SOCKET s, int flag)
{
	int i;
	int fl;
	/* Extract the NON_BLOCKING flag */
	fl = flag & PORT_NONBLOCK;
	ioctlsocket(s, FIONBIO, &fl);
	
/* We're not supporting any other flags right now as they are not in the code.
 * We'll just store the requested flags.
 */

	i = sockindex(s);

	if(i < REAL_FD_SETSIZE && i >= 0) {
 		sockset[i].flags = flag;
		return(0);
	}
	else 
	{
		i = sockin(s);
		if(i < REAL_FD_SETSIZE)
		{
			sockset[i].flags = flag;
			return(0);
		}
	}
	return(-1);		//Never happens unless full
}

int getsockflags(SOCKET s)
{
	int i = sockindex(s);

	if(i < REAL_FD_SETSIZE && i >= 0) {
	 	return(sockset[i].flags);
	}
	else
	{
		i = sockin(s);
	}
	return(0);		// No flags anyway
}

/*
 * Note: The only FD flags that Unix supports is the FD_CLOEXEC flag
 * It is 0 - don't close-on-exec or 1 = do close-on-exec.
 * In either case this is meaningless to Windows NT.  We'll set the
 * value in our internal structure, but really do nothing with it.
 */
int setsockdescrip(SOCKET s, int flag)
{
	int i = sockindex(s);

	if(i < REAL_FD_SETSIZE && i >= 0) {
 		sockdescrip[i] = flag;
		return(0);
	}
	else 
	{
		i = sockin(s);
		if(i < REAL_FD_SETSIZE)
		{
			sockdescrip[i] = flag;
			return(0);
		}
	}
	return(-1);		//Never happens unless full
}

int getsockdescrip(SOCKET s)
{
	int i = sockindex(s);

	if(i < REAL_FD_SETSIZE && i >= 0) {
	 	return(sockdescrip[i]);
	}
	else
	{
		i = sockin(s);
	}
	return(0);		// No flags anyway
}

/*
 * Check to see whether fd is a socket or an actual FD
 */
int S_ISSOCK(int fd)
{
	int i = 0;

	/* If we don't have any sockets listed we can skip the check */
	if(sockcount <=0)
		return(FALSE);
	/*
	 * See first if we have it in the file list. If so we can skip
	 * the rest, as the eof test would say it's a file. It is not,
	 * however, necessarily true that if we don't find it, then it's
	 * a socket as not all file descriptors may have been added to
	 * the file list.
	 */
	if(fdindex(fd) >= 0)
		return(FALSE);

	/* See if it's in the socket list */
	if(sockindex(fd) >= 0)
		return(TRUE);
	/* 
	 * See if it could be a file descriptor
	 */
	if(fd > 0)
	{
		/* Try EOF */
		if(_eof(fd) == -1) {
			if(errno == EBADF) {
				/* EOF says not a valid fd, so we must be a socket */
				errno = 0;	/* Fix the error code */
				return(TRUE);
			}
			else {
				/* This is some other error but apparently not a file */
				return(TRUE);
			}
		}
		else {
			/* must be a file */
			return(FALSE);
		}
	}
	/*
	 * If we got here the file descriptor is invalid
	 * Set errno and see if something notices
	 */
	errno = EBADF;
	return(FALSE);
}

/*
 * Holds flags, sets block/nonblock for sockets
 * not much else
 */

int fcntlsocket(int fd, int cmd, u_long arg)
{
	int rc = -1;
	

	switch(cmd)
	{
	/* Set status flags */
	case F_SETFL:
		rc = setsockflags(fd, arg);
		break;
	/* Get status flags */
	case F_GETFL:
		rc = getsockflags(fd);
		break;
	/* Set FD flags */
	case F_SETFD:
		rc = setsockdescrip(fd, arg);
		break;
	/* Get FD flags */
	case F_GETFD:
		rc = getsockdescrip(fd);
 		break;
	default:
		break;
	}
	return rc;
}


/*
 * Holds flags, sets block/nonblock for sockets
 * not much else
 */

/*
 * Shutdown socket services
 */
void SocketShutdown()
{
	p_WSACleanup();
	FreeLibrary(winsockDLLHandle);
}

/*
 * Initialize socket services
 */
BOOL InitSockets()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int i, err;

	winsockDLLHandle = LoadLibrary("ws2_32.dll");
	p_WSACleanup = GetProcAddress(winsockDLLHandle, "WSACleanup");
	p_WSAStartup = GetProcAddress(winsockDLLHandle, "WSAStartup");

	/* Need Winsock 2.0 or better */
	wVersionRequested = MAKEWORD(2, 0);
 
	err = p_WSAStartup(wVersionRequested, &wsaData);
	if ( err != 0 )
	{
		/* Tell the user that we could not find a usable Winsock DLL */
		return(FALSE);
	}
 
	/* 
	 * Confirm that the WinSock DLL supports 2.0
	 * Note that if the DLL supports versions greater
 	 * than 2.2 in addition to 2.2, it will still return
	 * 2.2 in wVersion since that is the version we
	 * requested.                                 
	 */
 	if ( LOBYTE( wsaData.wVersion ) != 2 || HIBYTE( wsaData.wVersion ) != 0 )
	{
		/* Tell the user that we could not find a usable Winsock DLL */
		p_WSACleanup();
		return(FALSE); 
	}
 
	socketInit();  //Initialize storage structure above.

	/* Pointers to socket functions imported by us */
	p_ioctlsocket = GetProcAddress(winsockDLLHandle, "ioctlsocket");
	p_closesocket = GetProcAddress(winsockDLLHandle, "closesocket");
	p_setsockopt = GetProcAddress(winsockDLLHandle, "setsockopt");
	p_getsockopt = GetProcAddress(winsockDLLHandle, "getsockopt");

	p_recv = GetProcAddress(winsockDLLHandle, "recv");
	p_recvfrom = GetProcAddress(winsockDLLHandle, "recvfrom");
	p_send = GetProcAddress(winsockDLLHandle, "send");
	p_sendto = GetProcAddress(winsockDLLHandle, "sendto");

	p_shutdown = GetProcAddress(winsockDLLHandle, "shutdown");
	p_socket = GetProcAddress(winsockDLLHandle, "socket");
	p_select = GetProcAddress(winsockDLLHandle, "select");
	p_connect = GetProcAddress(winsockDLLHandle, "connect");
	p_bind = GetProcAddress(winsockDLLHandle, "bind");
	p_accept = GetProcAddress(winsockDLLHandle, "accept");
	p_listen = GetProcAddress(winsockDLLHandle, "listen");

	p_ntohl = GetProcAddress(winsockDLLHandle, "ntohl");
	p_htonl = GetProcAddress(winsockDLLHandle, "htonl");
	p_htons = GetProcAddress(winsockDLLHandle, "htons");
	p_ntohs = GetProcAddress(winsockDLLHandle, "ntohs");

	p_getpeername = GetProcAddress(winsockDLLHandle, "getpeername");
	p_getsockname = GetProcAddress(winsockDLLHandle, "getsockname");

	p_inet_addr = GetProcAddress(winsockDLLHandle, "inet_addr");
	p_inet_ntoa = GetProcAddress(winsockDLLHandle, "inet_ntoa");

	p_gethostbyaddr = GetProcAddress(winsockDLLHandle, "gethostbyaddr");
	p_gethostbyname = GetProcAddress(winsockDLLHandle, "inet_addr"); 
	p_gethostname = GetProcAddress(winsockDLLHandle, "gethostname");
	p_getprotobyname = GetProcAddress(winsockDLLHandle, "getprotobyname");
	p_getprotobynumber = GetProcAddress(winsockDLLHandle, "getprotobynumber");
	p_getservbyname = GetProcAddress(winsockDLLHandle, "getservbyname");
	p_getservbyport = GetProcAddress(winsockDLLHandle, "getservbyport");
	 
 	p___WSAFDIsSet = GetProcAddress(winsockDLLHandle, "__WSAFDIsSet"); 
	p_WSAIoctl = GetProcAddress(winsockDLLHandle, "WSAIoctl");
	p_WSAGetLastError = GetProcAddress(winsockDLLHandle, "WSAGetLastError");

	return(TRUE);
}

/*
 * Function wrappers - call through to Winsock via (p_xxx)()
 * Could use #defines, but that's not type safe, 
 * and some functions need to do other things, too.
 */

int WSAAPI WSAGetLastError()
{return(p_WSAGetLastError)();}

int WSAAPI bind(SOCKET s,const struct sockaddr FAR * name,int namelen)
{return(p_bind)(s,name,namelen);}

int WSAAPI ioctlsocket(SOCKET s,long cmd,u_long FAR* argp)
{return(p_ioctlsocket)(s,cmd,argp);}
 
int WSAAPI closesocket(SOCKET s)
{
	int retval;

    retval = (p_closesocket)(s);
    if(retval == 0)
		sockout(s);
	return (retval);
}

int WSAAPI setsockopt(SOCKET s,int level,int optname,const char FAR * optval,int optlen)
{return(p_setsockopt)(s,level,optname,optval,optlen);}

int WSAAPI getsockopt(SOCKET s,int level,int optname,char FAR * optval,int FAR * optlen)
{return(p_getsockopt)(s,level,optname,optval,optlen);}

int WSAAPI recv(SOCKET s,char FAR * buf,int len,int flags)
{return(p_recv)(s,buf,len,flags);}

int WSAAPI recvfrom(SOCKET s,char FAR * buf,int len,int flags,struct sockaddr FAR * from,int FAR * fromlen)
{
	int errval = 0;
	int rc = (p_recvfrom)(s,buf,len,flags,from,fromlen);
	if(rc < 0) {
		errval = WSAGetLastError();

		switch (errval) {
		case WSAEWOULDBLOCK:
			errno = EWOULDBLOCK;
			break;
		case WSAEINTR:
			errno = EINTR;
			break;
		case WSAEHOSTUNREACH:
			errno = EHOSTUNREACH;
			break;
		case WSAEHOSTDOWN:
			errno = EHOSTDOWN;
			break;
		case WSAENETUNREACH:
			errno = ENETUNREACH;
			break;
		case WSAENETDOWN:
		case WSAENETRESET:
		case WSAETIMEDOUT:
			errno = ENETDOWN;
			break;
		case WSAECONNREFUSED:
			errno = ECONNREFUSED;
			break;
		case WSAECONNRESET:
			errno = ECONNRESET;
			break;
		default:
			errno = errval;
		}
	}
	return(rc);
}

int WSAAPI send(SOCKET s,const char FAR * buf,int len,int flags)
{return(p_send)(s,buf,len,flags);}

int WSAAPI sendto(SOCKET s,const char FAR * buf,int len,int flags,const struct sockaddr FAR * to,int tolen)
{return(p_sendto)(s,buf,len,flags,to,tolen);}

int WSAAPI shutdown(SOCKET s,int how)
{return(p_shutdown)(s, how);}

SOCKET WSAAPI socket(int af,int type,int protocol)
{
	if(af == AF_UNIX)
	{
		errno = ECONNREFUSED;
		return(SOCKET_ERROR);
	}

      /* Don't allow more sockets than an fd_set can hold */
      if(sockcount >= REAL_FD_SETSIZE)
      {
              errno = EMFILE;
              return(SOCKET_ERROR);
      }
      else

	{
              SOCKET s = (p_socket)(af,type,protocol);
              if(s != SOCKET_ERROR)
              {
                      sockin(s);
                      return s;
              }
	}
	errno = GetLastError();
	return(SOCKET_ERROR);
}

int WSAAPI select(int nfds,fd_set FAR * readfds,fd_set FAR * writefds,fd_set FAR *exceptfds,const struct timeval FAR * timeout)
{return(p_select)(nfds,readfds,writefds,exceptfds,timeout);}

int WSAAPI connect(SOCKET s,const struct sockaddr FAR * name,int namelen)
{return(p_connect)(s,name,namelen);}

SOCKET WSAAPI accept(SOCKET s,struct sockaddr FAR * addr,int FAR * addrlen)
{
	s = (p_accept)(s,addr,addrlen);
	if(s != SOCKET_ERROR)
		sockin(s);	/* Track the value */
	return s;
}

int WSAAPI listen(SOCKET s,int backlog)
{return(p_listen)(s,backlog);}

u_long WSAAPI ntohl(u_long netlong)
{return(p_ntohl)(netlong);}

u_long WSAAPI htonl(u_long hostlong)
{return(p_htonl)(hostlong);}

u_short WSAAPI htons(u_short hostshort)
{return(p_htons)(hostshort);}

u_short WSAAPI ntohs(u_short netshort)
{return(p_ntohs)(netshort);}

int WSAAPI getpeername(SOCKET s,struct sockaddr FAR * name,int FAR * namelen)
{return(p_getpeername)(s,name,namelen);}

int WSAAPI getsockname(SOCKET s,struct sockaddr FAR * name,int FAR * namelen)
{return(p_getsockname)(s,name,namelen);}

unsigned long WSAAPI inet_addr(const char FAR * cp)
{return(p_inet_addr)(cp);}

char FAR * WSAAPI inet_ntoa(struct in_addr in)
{return(char FAR *)(p_inet_ntoa)(in);}

int WSAAPI gethostname(char FAR * name,int namelen)
{return(p_gethostname)(name, namelen);}

int WSAAPI __WSAFDIsSet(SOCKET s, fd_set FAR *fds)
{return(p___WSAFDIsSet)(s,fds);}
