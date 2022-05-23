CC=gcc
XX=g++
CFLAGS=-I.
DEPS = check.h
DEPT = advance.h
DEPU = cardHeader.h foundations.h gameConfiguration.h rules.h switches.h Tableaus.h
OBJ = check.o supportFunctions.o
OBJS = advance.o supportFunctions.o supportFunctions2.o
OBJT = winnable.o cardFunctions.o foundations.o gameConfiguration.o Tableaus.o

VPATH = checkfile : advancefile : winnablefile

build: check advance winnable

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.c $(DEPT)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPU)
	$(XX) -c -o $@ $< $(CFLAGS)

check: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

advance: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

winnable: $(OBJT)
	$(XX) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm  winnable check advance *.o
