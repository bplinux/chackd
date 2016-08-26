# TODO asking for Kernel KERNELRELEASE
# TODO description

CC=gcc
CFLAGS=-Wall -g

all:
	$(CC) $(CFLAGS) *.c -o challackd
clean:
	rm -f ./challackd
