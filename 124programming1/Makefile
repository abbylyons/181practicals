CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)
OBJS = graph.cpp pqueue.cpp prim.cpp randmst.cpp

all: randmst

randmst : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o randmst

clean:
	-rm randmst