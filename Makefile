# TODO asking for Kernel KERNELRELEASE
# TODO description

CC=gcc
CFLAGS=-Wall -g -DDEBUG
PATH_BIN=/usr/bin/challackd

all:
	echo "Making of challack daemon ..."
	$(CC) ./src/*.c -o $(PATH_BIN)
	echo "completed."
clean:
	echo "Removing challack daemon from /usr/bin/ ..."
	rm -f /usr/bin/challackd
	echo "completed."
debug:
	echo "Making debug version of challack daemon ..."
	$(CC) $(CFLAGS) ./src/*.c -o $(PATH_BIN)
	echo "completed."
