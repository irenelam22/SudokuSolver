# Makefile for 'interface' module
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS50, Summer 2020

PROG = interface 
OBJS = interface.o 
LIBS = ../common/common.a ../libcs50/libcs50.a ../solve/solve.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb -l ncurses $(TESTING) -I../common -I../libcs50  -I../solve
CC = gcc 
MAKE = make

.PHONY: test clean all

all: $(PROG)

$(PROG): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $^ -o $@

interface.o: interface.h

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)