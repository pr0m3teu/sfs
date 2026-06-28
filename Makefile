CC=gcc 
CFLAGS=-Wall -Wextra 

sfs: main.c sfs.o
	$(CC) -o sfs $(CFLAGS) main.c sfs.o

sfs.o: sfs.c sfs.h
	$(CC) -c $(CFLAGS) sfs.c
