# TODO asking for Kernel KERNELRELEASE
# TODO description

CC=gcc
CFLAGS=-Wall -g

all:
	$(CC) $(CFLAGS) ./src/*.c -o ./binary/challackd
clean:
	rm -f ./binary/challackd
