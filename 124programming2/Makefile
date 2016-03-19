CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = matrix.cpp scannerTest.cpp

all: randmst

randmst : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o randmst

clean:
	-rm randmst