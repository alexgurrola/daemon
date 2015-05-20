CC=gcc
CFLAGS=-g -O2
OBJECTS=main.o

all : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o bin/lifeline

%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f bin/lifeline *.o
