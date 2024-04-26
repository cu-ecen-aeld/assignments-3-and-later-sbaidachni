INCLUDE_DIRS = 
LIB_DIRS = 
CC=$(CROSS_COMPILE)gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) -Wall
LIBS= 

HFILES= 
CFILES=aesdsocket.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	aesdsocket

clean:
	-rm -f *.o *.d *.map *.elf
	-rm -f aesdsocket

build: aesdsocket.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<