/*
 *  res_parse.c
 *
 *  Parse the result of a DNS query
 *	into an accessible structure
 *
 *  v1.0
 *
 *  Dave Shield		January 1994
 *
 *  v1.1	Cast all malloc calls
 *		Cleaner handling of header
 *			February 1994
 *
 *  v1.2	Fixed incorrect calls to free_response
 *		Use memcpy rather than bcopy
 *			November 1995
 *
 *  v1.3	Allocate response dynamically
 *		Handle network/host ordering
 *			July 1997
 */

#include "rr.h"
#include "rr-internal.h"
#include <string.h>
#include <stdlib.h>
#include <resolv.h>


	/*
	 *  expand_cdname:
	 *	Extract and uncompress a domain name
	 *
	 *  returns a pointer to the domain name (or NULL on failure).
	 */
static char *
expand_cdname(char **cpp, char *msg)
{
	char	name[MAXDNAME];
	int	i;
	char	*ptr;
	
	if ((i = dn_expand(msg, msg+512, *cpp, name, MAXDNAME)) < 0)
		return(NULL);
	if (name[0] == '\0' ) {
		name[0] = '.';
		name[1] = '\0';
	}
	*cpp += i;	/* Step over the name */

	if ((ptr=(char *)malloc(strlen(name)+1)) == NULL ) {
			/* Failed - undo everything */
		*cpp -= i;
		return(NULL);
	}
	strcpy(ptr, name);
	return(ptr);
}


	/*
	 *  expand_charstring:
	 *	Extract a character string
	 *
	 *  returns a pointer to the string (or NULL on failure).
	 */
static char *
expand_charstring(char **cpp, char *msg)
{
	int	i;
	char	*ptr;

	i = **cpp;	/* Extract length of string */
	(*cpp)++;	/*  and move on */

	if ((ptr=(char *)malloc(i+1)) == NULL ) {
			/* Failed - undo everything */
		(*cpp)--;
		return(NULL);
	}
	strncpy(ptr, *cpp, i);
	ptr[i] = '\0';
	*cpp += i;

	return(ptr);
}


	/*
	 *  parse_question:
	 *	Extract and parse a question record
	 *
	 *  returns a pointer to the question (or NULL on failure).
	 */
static s_question *
parse_question(char **cpp, char *msg)
{
	s_question	*ptr;

	if ((ptr = (s_question *)malloc(sizeof(s_question))) == NULL )
		return(NULL);
	if ((ptr->qname = expand_cdname(cpp,msg)) == NULL ) {
		free( ptr );
		return(NULL);
	}
	ptr->qtype = _getshort(*cpp);
	*cpp += sizeof(u_short);
	ptr->qclass = _getshort(*cpp);
	*cpp += sizeof(u_short);

	return(ptr);
}

	

	/*
	 *  parse_rr:
	 *	Extract and parse a resource record
	 *
	 *  returns a pointer to the RR (or NULL on failure).
	 */
static s_rr *
parse_rr(char **cpp, char *msg)
{
	s_rr		*ptr;
	int		dlen;
	union u_rdata	*rd;


		/*
		 *  Set up the RR-independent information
		 */
	if ((ptr = (s_rr *)malloc(sizeof(s_rr))) == NULL )
		return(NULL);
	if ((ptr->name = expand_cdname(cpp,msg)) == NULL ) {
		free(ptr);
		return(NULL);
	}
	ptr->type = _getshort(*cpp);
	*cpp += sizeof(u_short);
	ptr->class = _getshort(*cpp);
	*cpp += sizeof(u_short);
	ptr->ttl = _getlong(*cpp);
	*cpp += sizeof(u_int);

	dlen = _getshort(*cpp);
	ptr->dlen = dlen;
	*cpp += sizeof(u_short);

	rd = &ptr->rdata;


		/*
		 *  Handle RR-specifics
		 *
		 *    (No indication of failures here is
		 *	passed back to the calling procedure)
		 */
	switch(ptr->type) {
	case T_A:				/* Address */
		switch (ptr->class) {
		case C_IN:
			memcpy((void *)&rd->address, (void *)*cpp, sizeof(struct in_addr));
			*cpp += dlen;
			break;

		default:
			/* Can't really handle this - just skip it */
			*cpp += dlen;
		}
		break;

	case T_NS:				/* Name Server */
	case T_MD:				/* Mail Destination (OBS) */
	case T_MF:				/* Mail Forwarder   (OBS) */
	case T_CNAME:				/* Canonical Name */
		rd->string = expand_cdname(cpp, msg);
		break;

	case T_SOA:				/* Start of Authority */
		rd->soa.mname = expand_cdname(cpp, msg);
		rd->soa.rname = expand_cdname(cpp, msg);
		rd->soa.serial = _getlong(*cpp);
		*cpp += sizeof(u_int);
		rd->soa.refresh = _getlong(*cpp);
		*cpp += sizeof(u_int);
		rd->soa.retry = _getlong(*cpp);
		*cpp += sizeof(u_int);
		rd->soa.expire = _getlong(*cpp);
		*cpp += sizeof(u_int);
		rd->soa.minimum = _getlong(*cpp);
		*cpp += sizeof(u_int);
		break;
		
	case T_MB:				/* Mail Box  */
	case T_MG:				/* Mail Group */
	case T_MR:				/* Mail Rename */
		rd->string = expand_cdname(cpp, msg);
		break;

	case T_NULL:				/* Null RR */
		if ((rd->null.anything = (char *)malloc(dlen)) != NULL )
			memcpy((void *)rd->null.anything, (void *)*cpp, dlen);
		rd->null.length = dlen;
		*cpp += dlen;
		break;

	case T_WKS:				/* Well Known Services */
		memcpy((void *)&rd->wks.address, (void *)*cpp, sizeof(struct in_addr));
		*cpp += sizeof(struct in_addr);
		rd->wks.protocol = **cpp;
		(*cpp)++;
		rd->wks.maplength = dlen-(sizeof(struct in_addr) +1);
		if ((rd->wks.bitmap = (char *)malloc(rd->wks.maplength)) != NULL )
			memcpy((void *)rd->wks.bitmap, (void *)*cpp, rd->wks.maplength);
		*cpp += rd->wks.maplength;
		break;

	case T_PTR:				/* Domain Name Pointer */
		rd->string = expand_cdname(cpp, msg);
		break;

	case T_HINFO:				/* Host Info */
		if (( rd->hinfo.cpu = expand_charstring(cpp, msg)) == NULL ) {
			cpp += dlen;
			break;
		}
		if (( rd->hinfo.os = expand_charstring(cpp, msg)) == NULL ) {
			cpp -= (strlen(rd->hinfo.cpu) +1);
			cpp += dlen;
			break;
		}
		break;

	case T_MINFO:				/* Mailbox Info */
		rd->minfo.rmailbx = expand_cdname(cpp, msg);
		rd->minfo.emailbx = expand_cdname(cpp, msg);
		break;

	case T_MX:				/* Mail Exchanger */
		rd->mx.preference = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->mx.exchange = expand_cdname(cpp, msg);
		break;

	case T_SRV:				/* Service location */
		rd->srv.priority = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->srv.weight = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->srv.port = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->srv.target = expand_cdname(cpp, msg); 
		break;

	case T_TXT:				/* Text string */
		rd->txt.len = **cpp;
		rd->txt.next = NULL;
		if ((rd->txt.text = expand_charstring(cpp, msg)) == NULL ) {
			cpp += dlen;
			break;
		}

			/*
			 *  Multiple strings
			 *	add onto a linked list
			 */
		if ( rd->txt.len+1 < dlen ) {
			struct s_TXT	*txtp;
			char		**cpp2;
			int		n;

			n = rd->txt.len+1;
			txtp = &(rd->txt);
			cpp2 = cpp;
			while ( n < dlen ) {
				if ((txtp->next = (struct s_TXT *)malloc(sizeof(struct s_TXT))) == NULL ) {
					cpp += (dlen - rd->txt.len);
					break;
				}
				txtp = txtp->next;
				txtp->len = **cpp2;
				n += txtp->len+1;
				txtp->next = NULL;
				if ((txtp->text = expand_charstring(cpp2, msg)) == NULL ) {
					cpp += (dlen - rd->txt.len);
					break;
				}
			}
		}
		break;
		

			/*
			 *  RFC 1183  Additional types
			 */
	case T_AFSDB:				/* AFS Server */
		rd->afsdb.subtype = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->afsdb.hostname = expand_cdname(cpp, msg);
		break;


	case T_RP:				/* Responsible Person */
		rd->rp.mbox_dname = expand_cdname(cpp, msg);
		rd->rp.txt_dname = expand_cdname(cpp, msg);
		break;

	case T_X25:				/* X25 Address */
		rd->string = expand_charstring(cpp, msg);
		break;

	case T_ISDN:				/* ISDN Address */
		if ( **cpp == dlen ) {
			rd->isdn.address = expand_charstring(cpp, msg);
			rd->isdn.sa = NULL;
		}
		else {
			rd->isdn.address = expand_charstring(cpp, msg);
			rd->isdn.sa = expand_charstring(cpp, msg);
		}
		break;

	case T_RT:				/* Route Through */
		rd->rt.preference = _getshort(*cpp);
		*cpp += sizeof(u_short);
		rd->rt.int_host = expand_cdname(cpp, msg);
		break;

			/*
			 *  Additional Non-standard types
			 */
	case T_UINFO:				/* User (finger) info */
		if ((rd->string = (char *)malloc(dlen+1)) != NULL ) {
			memcpy((void *)rd->string, (void *)*cpp, dlen);
			rd->string[dlen] = '\0';
		}
		*cpp += dlen;
		break;

	case T_UID:				/* User ID */
	case T_GID:				/* Group ID */
		rd->number = _getlong(*cpp);
		*cpp += sizeof(u_int);
		break;

	case T_UNSPEC:				/* Unspecified info */
	default:				/* Unrecognised */
		if ((rd->string = (char *)malloc(dlen+1)) != NULL )
			memcpy((void *)rd->string, (void *)*cpp, dlen);
		*cpp += dlen;
		break;

	}
		
		
	return(ptr);
}




	/*
	 *  res_parse:
	 *	Parse a DNS response buffer
	 *
	 *  returns a pointer to the expanded tree (or NULL on failure).
	 */
res_response *
res_parse(char *msg)
{
	char *cp;
	HEADER *hp;
	res_response *resp;
	int i;

	u_short qdcount, ancount, nscount, arcount;


	/*
	 * Set up the response structure,
	 *  and copy across the header fields.
	 */
	if ((resp = (res_response *)malloc(sizeof(res_response))) == NULL )
		return(NULL);
	memcpy((void *)&(resp->header), (void *)msg, sizeof(HEADER));
	hp = &(resp->header);
	cp = msg + sizeof(HEADER);


	/*
	 * Temporarily clear the number of records to expect
	 *    (allows the tree to be freed in case of problems)
	 * Also handle network/host ordering
	 */
	qdcount = ntohs(resp->header.qdcount); resp->header.qdcount = 0;
	ancount = ntohs(resp->header.ancount); resp->header.ancount = 0;
	nscount = ntohs(resp->header.nscount); resp->header.nscount = 0;
	arcount = ntohs(resp->header.arcount); resp->header.arcount = 0;
	resp->question = NULL;
	resp->answer = NULL;
	resp->authority = NULL;
	resp->additional = NULL;

	/*
	 * Handle question records.
	 */
	if ( qdcount ) {
		if ((resp->question = (s_question **)malloc(qdcount*sizeof(s_question*))) == NULL )
			return(NULL);
		for ( i=0 ; i<qdcount ; i++ )		/* Clear, in case of free */
			resp->question[i] = NULL;
		resp->header.qdcount = qdcount;
		for ( i=0 ; i<qdcount ; i++ )
			if ((resp->question[i] = parse_question(&cp, msg)) == NULL ) {
				free_response(resp);
				free(resp);
				return(NULL);
			}
	}


	/*
	 * Handle authoritative answer records
	 */
	if ( ancount ) {
		if ((resp->answer = (s_rr **)malloc(ancount*sizeof(s_rr*))) == NULL ) {
			resp->header.ancount = 0;
			free_response(resp);
			free(resp);
			return(NULL);
		}
		for ( i=0 ; i<ancount ; i++ )
			resp->answer[i] = NULL;
		resp->header.ancount = ancount;
		for ( i=0 ; i<ancount ; i++ )
			if ((resp->answer[i] = parse_rr(&cp, msg)) == NULL ) {
				free_response(resp);
				free(resp);
				return(NULL);
			}
	}


	/*
	 * Handle name server records
	 */
	if ( nscount ) {
		if ((resp->authority = (s_rr **)malloc(nscount*sizeof(s_rr*))) == NULL ) {
			resp->header.nscount = 0;
			free_response(resp);
			free(resp);
			return(NULL);
		}
		for ( i=0 ; i<nscount ; i++ )
			resp->authority[i] = NULL;
		resp->header.nscount = nscount;
		for ( i=0 ; i<nscount ; i++ )
			if ((resp->authority[i] = parse_rr(&cp, msg)) == NULL ) {
				free_response(resp);
				free(resp);
				return(NULL);
			}
	}


	/*
	 * Handle additional records
	 */
	if ( arcount ) {
		if ((resp->additional = (s_rr **)malloc(arcount*sizeof(s_rr*))) == NULL ) {
			resp->header.arcount = 0;
			free_response(resp);
			free(resp);
			return(NULL);
		}
		for ( i=0 ; i<arcount ; i++ )
			resp->additional[i] = NULL;
		resp->header.arcount = arcount;
		for ( i=0 ; i<arcount ; i++ )
			if ((resp->additional[i] = parse_rr(&cp, msg)) == NULL ) {
				free_response(resp);
				free(resp);
				return(NULL);
			}
	}

	return(resp);
}
