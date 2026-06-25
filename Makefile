CC=gcc 
CFLAGS=-Wall -Wextra 

sfs: main.c
	$(CC) -o sfs $(CFLAGS) main.c 
