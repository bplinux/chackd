# challack-daemon
challack-daemon randomize tcp_challenge_ack_limit to prevent side channel attacks

# Abstract
A shortly presented side-channel attack has given strong attention of the community [1] . For lots of servers or smartphone devices this attack is dangerous for ipv4 connections. There is no doubt that the kernel is fixing this issue in the next versions. However, some admins might not update the kernel due to specific reasons or just lazyness. 

A work-around as published in [2] might help, but for server workload efficency such high values shall be avoided [1]. Some possible methods are given in [1] which show of preventing those attacks by making an attacker mad of these approaches. One concept is to randomize the system limit. The challack daemon does this job very well and keep it simple. An former concept of mine was looking for a loadable kernel module but i discarded this, because there is a powerful interface between user- and kernelspace called proc vfs. With proc files we are able to do the job with a simple daemon.

This is my first open-source project with a nice benifit for admins who want to secure agains challenge_ack_limit attacks and are not able to update their kernel. Just compile it and run it on your server.

I need help from the community to make this project "community standard".

# Description

The daemon is coded in c. It maybe compiled with the Makefile (all;debug;clean). make all is compiling all source-files without any debug informations. Maybe you want to know what challack daemon does, do it with make debug. make clean removes only the executable file

# Files

Makefile      - Makefile

global.h      - Handle compiler options and define global variables

main.c        - main function and your entry in challack-daemon

init_daemon.h - interface header for init_daemon.c

init_daemon.c - initialization of the daemon, just to make challackd a daemon process

start_daemon.h- interface header for start_daemon.c

start_daemon.c- main functionality with random-generator and proc-file Handling

stop_daemon.h - interface header for stop_daemon.c

stop_daemon.c - containing the signal handler for SIGUSR1 which is used to stopp the daemon

# TODOs

Please look for TODOs inside the src files for some things i would like to work on. Feel free to branch in any way you want.
I would like to learn a lot from this project. 

Makefile	-
My wish for the Makefile is to make it a kind of standard with installation, kernel-release queries and so on.

start_daemon	-
Any part of code which might cause the daemon to crash must be fixed

stop_daemon	-
Any part of code which is not a kind of standard must be fixed

init_daemon	-
Any part of code which might caus the daemon to crash must be fixed

main	-
My intention is that main parameters are given as simple integer, currently it works well. However maybe there is a much better way of handling?

# Author

Bastian Pukallus, please mail to bastianpukallus@gmail.com

# Sources

[1] http://www.cs.ucr.edu/~zhiyunq/pub/sec16_TCP_pure_offpath.pdf

[2] https://www.mail-archive.com/debian-user@lists.debian.org/msg705042.html
