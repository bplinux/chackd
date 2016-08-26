# challack-daemon
challack-daemon randomize tcp_challenge_ack_limit to prevent side channel attacks

# Abstract
A shortly presented side-channel attack has given strong attention of the community [1] . For lots of servers or smartphone devices this attack is dangerous for ipv4 connections. There is no doubt that the kernel is fixing this issue in the next versions. However, some admins might not update the kernel due to specific reasons or just lazyness. 

A work-around as published in [2] might help, but for server workload efficency such high values shall be avoided [1]. Some hint is given in [1] which ways of preventing those attacks. One concept is to randomize the system limit. The challack daemon is to do this job very well and keep it much simple. A former concept was looking for a loadable kernel module but it has discarded, because there is a powerful interface called proc vfs. With proc files we are able to  do the job with  a simple daemon.

This is my first open-source project with a nice benifit for admins who want to secure agains challenge_ack_limit attacks and are not able to update their kernel.

I need help from the community to make this project "community standard".

# TODOs

[1] http://www.cs.ucr.edu/~zhiyunq/pub/sec16_TCP_pure_offpath.pdf

[2] https://www.mail-archive.com/debian-user@lists.debian.org/msg705042.html
