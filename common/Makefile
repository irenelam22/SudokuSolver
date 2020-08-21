OBJS = puzzle.o unit.o # common.o 
LIB = common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS)
CC = gcc

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# common.o: common.h
unit.o: unit.h ../libcs50/counters.h
puzzle.o: puzzle.h unit.h

.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o