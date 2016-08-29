#ifndef __GLOBAL_H_
#define __GLOBAL_H_

// ------------------
// standard libraries

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/stat.h>

// -------------------
// debug logging macro

#ifdef DEBUG
	#define _udebug(s) syslog( LOG_DEBUG, s )
#else
	#define _udebug(s)
#endif

#define CHACKD_LIMIT_FILE "/proc/sys/net/ipv4/tcp_challenge_ack_limit"
#define CHACKD_PID_FILE "/var/run/chackd.pid"

FILE *f_proc; /* used for tcp_challenge_ack_limit proc-file has to be global for
start_daemon and stop_daemon functions */

int default_limit;	// system default limit
int base_value;		// daemon parameter argv[1]
int noise_value;	// daemon parameter argv[2]

#endif
