PROG = test
OBJS = test.o libcs50/counters.o
C = common
LIBS = $(C)/common.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$(C)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@ 

.PHONY: clean valgrind

libcs50/counters.o: libcs50/counters.h

# test: $(PROG) 
# 	./$(PROG) 

valgrind: $(PROG) 
	valgrind ./$(PROG) 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)