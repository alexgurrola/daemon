CC=gcc
CFLAGS=-g -O2
OBJECTS=main.o

all : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main

%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f main *.o
