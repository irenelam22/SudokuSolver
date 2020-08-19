# Makefile for 'solve' module
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS50, Summer 2020

PROG = solve
OBJS = solve.o
LIBS = ../common/common.a ../libcs50/libcs50.a ../common/puzzle.o

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

# CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../libcs50  
MAKE = make

.PHONY: test clean all

all: $(PROG)

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

solve: solve.o

# test:
# 	bash testing.sh &> testing.out

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)