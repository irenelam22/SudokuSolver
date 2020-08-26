# Makefile for CS50 Sudoku Final Project
#
# Team KIDD - Kelly Westkaemper, Irene Lam, David Kantor, David Perez Gonzalez
# CS 50, Summer 2020

.PHONY: all valgrind clean

############## default: make all libs and programs ##########
all: 
	make -C libcs50
	make -C common
	make -C solve
	make -C create
	make -C sudoku

############## test: make all tests ##########
test:
	make -C solve test
	

############## valgrind all programs ##########
valgrind: all
	make -C solve valgrind
	make -C create valgrind

############## clean  ##########
clean:
	rm -f *~
	make -C libcs50 clean
	make -C common clean
	make -C solve clean
	make -C create clean
	make -C sudoku clean
