CC=gcc
XX=g++
CFLAGS=-I.
DEPS = card.h check.h foundation.h stockWaste.h tableau.h
DEPT = advance.h
OBJ = check.o card.o checkf.o foundation.o stockWaste.o tableau.o
OBJS = advance.o foundation.o stockWaste.o tableau.o card.o

VPATH = checkfile : advancefile

build: check advance

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.c $(DEPT)
	$(CC) -c -o $@ $< $(CFLAGS)

check: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

advance: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm check advance *.o
