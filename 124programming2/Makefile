CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OBJS = matrix.cpp strassen.cpp

all: strassen

strassen : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o strassen

clean:
	-rm strassen
