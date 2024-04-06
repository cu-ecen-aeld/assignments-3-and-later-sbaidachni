INCLUDE_DIRS = 
LIB_DIRS = 
CC=$(CROSS_COMPILE)gcc

CDEFS=
CFLAGS= -O0 -g $(INCLUDE_DIRS) $(CDEFS) -Wall
LIBS= 

HFILES= 
CFILES= writer.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	writer

clean:
	-rm -f *.o *.d *.map *.elf
	-rm -f writer

build: writer.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $@.o

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<