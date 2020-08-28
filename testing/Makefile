# Makefile for 'testing' module
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS50, Summer 2020

MAKE = make

.PHONY: test clean all

test: 
	bash ./testing.sh 2

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -rf fuzz.out
	rm -f *~ *.o
	rm -f $(PROG)