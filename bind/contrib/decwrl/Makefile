CC= cc
SHELL= /bin/sh
CDEBUG= -O
INCL =  ../../include
RES=	../../res/libresolv.a
LIBS=	
LDFLAGS=
CFLAGS=	$(CDEBUG) -I$(INCL)

all: gethost mkdb mkservers

gethost: gethost.o ${RES} Makefile
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ gethost.o ${RES} ${LIBS}

mkdb: mkdb.pl
	rm -f $@; cp $*.pl $@; chmod +x $@

mkservers: mkservers.pl
	rm -f $@; cp $*.pl $@; chmod +x $@

clean: FRC
	rm -f *.o *.BAK *.CKP *~
	rm -f gethost

FRC:
