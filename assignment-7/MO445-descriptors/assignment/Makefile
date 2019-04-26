CFLAGS = -Wall -O3
MO445LIB  = -L../lib
MO445FLAGS  = -I../include
CC=gcc
FLAGS= -O3 -Wall

all: libMO445 assignment

libMO445:
	$(MAKE) -C ../
assignment: libMO445
	$(CC) $(FLAGS) $(MO445FLAGS) assignment.c  $(MO445LIB) -o assignment -lMO445 -lm
clean:
	rm -f *~ test.o test assignment.o assignment ../lib/*.a ../obj/*.o
