PROG = puzzle_unittest
OBJS = puzzle.o unit.o puzzle_unittest.o
LIB = common.a
LIBS = puzzle.o unit.o

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# common.o: common.h
unit.o: unit.h ../libcs50/counters.h
puzzle.o: puzzle.h unit.h
puzzle_unittest.o: puzzle.h unit.h

puzzle_unittest: puzzle_unittest.o $(LIBS)
	$(CC) $(CFLAGS) $^ ../libcs50/libcs50.a  -o $@ 

.PHONY: test clean

test: puzzle_unittest

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o