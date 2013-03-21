##
# Makefile for bind
##

# Project info
Project           = bind
UserType          = Administration
ToolType          = Services
Extra_Environment = DESTBIN=$(USRBINDIR)		\
		    DESTSBIN=$(USRSBINDIR)		\
		    DESTEXEC=$(LIBEXECDIR)		\
		    DESTHELP=$(SHAREDIR)/misc		\
		    DESTLIB=/usr/local/bind/lib		\
		    DESTINC=/usr/local/bind/include	\
		    LD='$(CC) $(LDFLAGS) -nostdlib'	\
		    LD_LIBFLAGS='-Wl,-x -r'		\
		    AR='$(SRCROOT)/ar.sh cru'

# It's a Common Source project
include $(MAKEFILEPATH)/CoreOS/ReleaseControl/Common.make

##
# Targets
##

Install_Flags = DESTDIR="$(DSTROOT)"

install:: build
	$(_v) $(MAKE) -C $(BuildDirectory) $(Environment) $(Install_Flags) install
	$(_v) $(STRIP) $(DSTROOT)$(USRBINDIR)/* $(DSTROOT)$(USRSBINDIR)/* $(DSTROOT)$(LIBEXECDIR)/*
	$(_v) mkdir -p "$(DSTROOT)/usr/share/man/man1"
	$(_v) mkdir -p "$(DSTROOT)/usr/share/man/man3"
	$(_v) mkdir -p "$(DSTROOT)/usr/share/man/man5"
	$(_v) mkdir -p "$(DSTROOT)/usr/share/man/man8"
	$(_v) $(MAKE) -C $(Sources)/$(Project)/doc/man $(Environment)		\
		MANROFF=cat MANDIR=cat FORMAT_BASE=named.conf LIB_NETWORK_BASE="" CMD_BASE="dig host dnsquery" DESTMAN="$(DSTROOT)/usr/share/man" DST="$(BuildDirectory)" SRC="$(Sources)/$(Project)/doc/man" install
	mkdir -p "$(DSTROOT)/usr/share/named/examples"
	install -c -m 444 examples/Instructions "$(DSTROOT)/usr/share/named/examples"
	install -c -m 444 examples/db.10.0.0.1 "$(DSTROOT)/usr/share/named/examples"
	install -c -m 444 examples/db.example.com "$(DSTROOT)/usr/share/named/examples"
	install -c -m 444 examples/named.conf "$(DSTROOT)/usr/share/named/examples"


build:: setup
	$(_v) $(MAKE) -C $(BuildDirectory) $(Environment)
	mkdir -p $(DSTROOT)/System/Library/StartupItems/BIND/Resources/English.lproj/
	install -c -m 755 BIND.startup $(DSTROOT)/System/Library/StartupItems/BIND/BIND
	install -c -m 644 StartupParameters.plist $(DSTROOT)/System/Library/StartupItems/BIND/
	install -c -m 644 Localizable.strings $(DSTROOT)/System/Library/StartupItems/BIND/Resources/English.lproj/
	mkdir -p $(DSTROOT)/private/etc
	install -c -m 644 named.conf $(DSTROOT)/private/etc
	mkdir -p $(DSTROOT)/private/var/named
	install -c -m 644 named.ca $(DSTROOT)/private/var/named
	install -c -m 644 named.local $(DSTROOT)/private/var/named
	install -c -m 644 localhost.zone $(DSTROOT)/private/var/named

setup:: $(BuildDirectory)/Makefile

$(BuildDirectory)/Makefile:
	$(_v) mkdir -p $(BuildDirectory)
	$(_v) $(MAKE) -C $(Sources)/$(Project)/src $(Environment)		\
		DST="$(BuildDirectory)" SRC="$(Sources)/$(Project)/src" links
	$(_v) $(MAKE) -C $(BuildDirectory) $(Environment) depend
