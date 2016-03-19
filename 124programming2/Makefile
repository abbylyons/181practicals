CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = matrix.cpp scannerTest.cpp

all: strassen

strassen : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o strassen

clean:
	-rm strassen
