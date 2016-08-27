# TODO asking for Kernel KERNELRELEASE
# TODO description

CC=gcc
CFLAGS=-Wall -g

all:
	$(CC) $(CFLAGS) ./src/*.c -o /usr/bin/challackd
clean:
	rm -f /usr/bin/challackd

debug:
	$(CC) $(CFLAGS) -DDEBUG ./src/*.c -o /usr/bin/challackd
