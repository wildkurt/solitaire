CC=gcc
XX=g++
CFLAGS=-I. -Wall
DEPS = card.h check.h foundation.h stockWaste.h tableau.h
DEPT = advance.h check.h moves.h printGames.h printGamesToFile.h
DEPU = winnable.h Card.h Foundation.h GameConfiguration.h Moves.h Rules.h Stock.h Tableau.h
OBJ = check.o card.o checkf.o foundation.o stockWaste.o tableau.o
OBJS = advance.o card.o checkf.o foundation.o stockWaste.o tableau.o moves.o printGame.o printGameToFile.o
OBJT = winnable.o Card.o Foundation.o GameConfiguration.o Moves.o Rules.o Stock.o Tableau.o winnablef.o

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
	rm check advance winnable *.o
