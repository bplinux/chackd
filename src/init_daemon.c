#include "../include/global.h"
#include "../include/init_daemon.h"
#include "../include/stop_daemon.h"

int init_daemon()
{
	// ----------------
	// locale variables	

	int i;
	pid_t pid;
	FILE *f_pid;
	char *defptr = NULL; // getline() ptr for default; must be free()d!
	size_t deflen = 0; // needed for getline()

	struct sigaction ignore;
	struct sigaction stop;

	// TODO: add more terminal generated signals

	int ignore_signals[] = { SIGINT };

	// -------------------------------------
	// Setting up the signal handle routines

	ignore.sa_handler = SIG_IGN;
	stop.sa_handler = stop_daemon;

	// ----------------------------------------------
	// Setting up the signals which has to be ignored

	for( i = 0; i < sizeof( ignore_signals ) / sizeof( int ); i++) {
		if( sigaction( ignore_signals[i], &ignore, NULL ) == -1 ) {
			_udebug( "failed to sigaction() ignore signals" );
			return( INIT_DAEMON_FAILURE );
		}
	}
	
	_udebug( "initialized ignore signals with sigaction()" );

	// -----------------------------------
	// forking the main process for daemon

	switch( pid = fork() ) {
	case 0:
		_udebug( "parent forked to child process" );	
		break;
	case -1:
		syslog( LOG_INFO, "fork() to child not successful" );
		return( INIT_DAEMON_FAILURE );
		break;
	default:
		_udebug( "terminating parent process" );	
		exit( EXIT_SUCCESS );
		break;
	};

	// -----------------------------------------------------
	// making child process a full session leader and set-up
	// TODO: unhandled errors?

	setsid();
	chroot("/");
	umask(0);

	// -------------------------------
	// closing unused file-descriptors
	// TODO: unhandled errors?

	close( STDIN_FILENO );
	close( STDOUT_FILENO );
	close( STDERR_FILENO );

	// --------------------------------------------
	// forking the child process to generate daemon
	
	switch( pid = fork() ) {
	case 0:
		_udebug( "child forked to daemon process" );
		break;
	case -1:
		syslog( LOG_INFO, "fork() to daemon not successful" );
		return( INIT_DAEMON_FAILURE );
		break;
	default:
		_udebug( "terminating child process" );
		exit( EXIT_SUCCESS );
	};

	// --------------------------------------------------------
	// I am challack daemon process; writing my PID to PID_FILE
	// TODO: unhandled errors?

	f_pid = fopen( CHALLACKD_PID_FILE, "w" );
	fprintf( f_pid, "%d\n", getpid() );
	fclose( f_pid );

	// ----------------------------------------------------
	// load default limit value from tcp_challenge_ack_limit
	// TODO: unhandled errors?

	f_proc = fopen( CHALLACKD_LIMIT_FILE, "r");
	getline( &defptr, &deflen, f_proc );
	fclose( f_proc );
	default_limit = atoi( defptr );
	free( defptr );

	_udebug( "default value saved" );

	// ----------------------------------
	// Setting up the stop signal handler

	if( sigaction( SIGUSR1, &stop, NULL ) == -1 ) {
		_udebug( "failed to sigaction() SIGUSR1 to stop" );
		return( INIT_DAEMON_FAILURE );
	}	

	// ----------------------------------------------
	// challack daemon successful initialized; return

	return( INIT_DAEMON_SUCCESS );
}
