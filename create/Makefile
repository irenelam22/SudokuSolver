# Makefile for 'create' module
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS50, Summer 2020

PROG = create 
OBJS = create.o # solvingmodule.o
LIBS = ../common/common.a ../libcs50/libcs50.a 

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../common -I../libcs50  
CC = gcc 
MAKE = make

.PHONY: test clean all

all: $(PROG)

$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

# solvingmodule.o: solvingmodule.h $(LIBS)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)