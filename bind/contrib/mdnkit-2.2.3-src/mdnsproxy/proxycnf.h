/*
 * proxycnf.h - mDNS Proxy, Configure Proxy Server
 */

/*
 * Copyright (c) 2000 Japan Network Information Center.  All rights reserved.
 *  
 * By using this file, you agree to the terms and conditions set forth bellow.
 * 
 * 			LICENSE TERMS AND CONDITIONS 
 * 
 * The following License Terms and Conditions apply, unless a different
 * license is obtained from Japan Network Information Center ("JPNIC"),
 * a Japanese association, Kokusai-Kougyou-Kanda Bldg 6F, 2-3-4 Uchi-Kanda,
 * Chiyoda-ku, Tokyo 101-0047, Japan.
 * 
 * 1. Use, Modification and Redistribution (including distribution of any
 *    modified or derived work) in source and/or binary forms is permitted
 *    under this License Terms and Conditions.
 * 
 * 2. Redistribution of source code must retain the copyright notices as they
 *    appear in each source code file, this License Terms and Conditions.
 * 
 * 3. Redistribution in binary form must reproduce the Copyright Notice,
 *    this License Terms and Conditions, in the documentation and/or other
 *    materials provided with the distribution.  For the purposes of binary
 *    distribution the "Copyright Notice" refers to the following language:
 *    "Copyright (c) Japan Network Information Center.  All rights reserved."
 * 
 * 4. Neither the name of JPNIC may be used to endorse or promote products
 *    derived from this Software without specific prior written approval of
 *    JPNIC.
 * 
 * 5. Disclaimer/Limitation of Liability: THIS SOFTWARE IS PROVIDED BY JPNIC
 *    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *    PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL JPNIC BE LIABLE
 *    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *    BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *    OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *    ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * 
 * 6. Indemnification by Licensee
 *    Any person or entities using and/or redistributing this Software under
 *    this License Terms and Conditions shall defend indemnify and hold
 *    harmless JPNIC from and against any and all judgements damages,
 *    expenses, settlement liabilities, cost and other liabilities of any
 *    kind as a result of use and redistribution of this Software or any
 *    claim, suite, action, litigation or proceeding by any third party
 *    arising out of or relates to this License Terms and Conditions.
 * 
 * 7. Governing Law, Jurisdiction and Venue
 *    This License Terms and Conditions shall be governed by and and
 *    construed in accordance with the law of Japan. Any person or entities
 *    using and/or redistributing this Software under this License Terms and
 *    Conditions hereby agrees and consent to the personal and exclusive
 *    jurisdiction and venue of Tokyo District Court of Japan.
 */

/* $Id: proxycnf.h,v 1.1.1.1 2002/11/18 22:25:26 bbraun Exp $ */

#ifndef PROXYCNF_H
#define PROXYCNF_H 1

/*
 * CONFIG_PATH
 *      where configuration file placed
 */

#ifndef CONFIG_PATH
#ifdef  UNIX
#define CONFIG_PATH "/usr/local/etc/"
#endif
#ifdef  WIN32
#define CONFIG_PATH "$(SystemRoot)/"
#endif
#ifdef  OS2
#define CONFIG_PATH "$(ETC)/"
#endif
#endif  /* CONFIG_PATH */

/*
 * CONFIG_FILE
 *      name of configuration file
 */

#ifndef CONFIG_FILE
#ifdef  UNIX
#define CONFIG_FILE     "mdnsproxy.conf"
#endif
#ifdef  WIN32
#define CONFIG_FILE     "mdnsproxy.cnf"
#endif
#ifdef  OS2
#define CONFIG_FILE     "mdnsproxy.cnf"
#endif
#endif  /* CONFIG_FILE */

/*
 * CONFIG_HOME
 *      debugging support, $HOME environment name
 */

#ifndef CONFIG_HOME
#ifdef  UNIX
#define CONFIG_HOME     "$(HOME)/"
#endif
#ifdef  WIN32
#define CONFIG_HOME     "$(HOMEPATH)/"
#endif
#ifdef  OS2
#define CONFIG_HOME     "$(HOME)/"
#endif
#endif  /* CONFIG_HOME */

/*
 * Commands used in configuration file
 */
#define KW_LISTEN		"listen"
#define KW_FORWARD		"forward"
#define KW_CLIENT_ENCODING	"client-encoding"
#define KW_MDN_CONF_FILE	"mdn-conf-file"
#define KW_LOG_FILE		"log-file"
#define KW_LOG_LEVEL		"log-level"
#define KW_MDN_LOG_LEVEL	"mdn-log-level"
#define KW_USER_ID		"user-id"
#define KW_GROUP_ID		"group-id"
#define KW_ROOT_DIRECTORY	"root-directory"
#define KW_ALLOW_ACCESS		"allow-access"
#define KW_LOG_ON_DENIED	"log-on-denied"
#define KW_SYSLOG_FACILITY	"syslog-facility"

/* The following commands are obsoleted. */
#define KW_CLIENT_TRANSLATION	"client-translation"
#define KW_ALTERNATE_ENCODING	"alternate-encoding"
#define KW_NORMALIZE		"normalize"
#define KW_SERVER_TRANSLATION	"server-translation"
#define KW_ENCODING_ALIAS_FILE	"encoding-alias-file"

/*
 * Command line options.
 */
#define CMDOPT_LOGFILE		"-logfile"
#define CMDOPT_DAEMON		"-daemon"
#define CMDOPT_CONFIG		"-config"
#define CMDOPT_VERSION		"-version"

#endif  /* PROXYCNF_H */
