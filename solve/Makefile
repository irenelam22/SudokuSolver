# Makefile for 'solve' module
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS50, Summer 2020

PROG = solve solve_test
OBJS = solve.o solve_test.o
LIBS = ../common/common.a ../libcs50/libcs50.a 

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../libcs50  
CC = gcc 
MAKE = make

.PHONY: test clean all

all: $(PROG)

# $(LIB): $(OBJS)
# 	ar cr $(LIB) $(OBJS)

# solve: solve.o

solve: solve.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

solve_test: solve_test.o $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# test:
# 	$(CC) -c $(CFLAGS) $<

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)