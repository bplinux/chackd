# TODO asking for Kernel KERNELRELEASE
# TODO description

CC=gcc
CFLAGS=-Wall -g -DDEBUG
PATH_BIN=/usr/bin/chackd

all:
	$(CC) ./src/*.c -o $(PATH_BIN)
clean:
	rm -f /usr/bin/chackd
debug:
	$(CC) $(CFLAGS) ./src/*.c -o $(PATH_BIN)
