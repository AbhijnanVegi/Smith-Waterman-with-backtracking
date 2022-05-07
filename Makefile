CC=gcc
CFLAGS=-Wall -g -Og -std=c99 -march=native -mtune=native 
INCLUDES=includes
OBJECTS=helper.o swb.o utils.o
V=BASELINE

all: main

main: src/main.c helper.o swb.o utils.o
	$(CC) $(CFLAGS) -o main src/main.c $(OBJECTS) -I$(INCLUDES) 

swb.o : src/swb.c includes/swb.h utils.o helper.o
	$(CC) $(CFLAGS) -c -o swb.o src/swb.c -I$(INCLUDES) -D$(V)

helper.o: src/helper.c includes/helper.h
	$(CC) -c -I$(INCLUDES) src/helper.c -o helper.o

utils.o: src/utils.c includes/utils.h
	$(CC) $(CFLAGS) -c -I$(INCLUDES) src/utils.c -o utils.o

clean: 
	rm -f main *.o