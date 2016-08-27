#include "include/global.h"
#include "include/init_daemon.h"
#include "include/stop_daemon.h"

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

	// These are terminal generated signals(?)

	int ignore_signals[] = { SIGHUP, SIGINT, SIGTERM };

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

	if( setsid() == ((pid_t) -1) ) {
		syslog( LOG_INFO, "failed to make child a session leader" );
		return( INIT_DAEMON_FAILURE );
	}
	if( chroot("/") == -1 ) {
		syslog( LOG_INFO, "failed to change working directory" );
		return( INIT_DAEMON_FAILURE );
	}
	
	umask(0);

	// -------------------------------
	// closing unused file-descriptors
	// TODO: it might exists a better looking form of this error handling

	if ( \
		close( STDIN_FILENO ) + \
		close( STDOUT_FILENO ) + \
		close( STDERR_FILENO ) < 0 ) {
		syslog( LOG_INFO, "failed to close stdio descriptors" );
		return( INIT_DAEMON_FAILURE );
	}

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

	if( ( f_pid = fopen( CHALLACKD_PID_FILE, "w" ) ) == NULL ) {
		syslog( LOG_INFO, "failed to open pid-file" );
		return( INIT_DAEMON_FAILURE );
	}
	if( fprintf( f_pid, "%d\n", getpid() ) < 0 ) {
		syslog( LOG_INFO, "failed to write pid to pid-file" );
		return( INIT_DAEMON_FAILURE );
	}
	if( fclose( f_pid ) != 0 ) {
		syslog( LOG_INFO, "failed to close pid-file-stream" );
		return( INIT_DAEMON_FAILURE );
	}

	// ----------------------------------------------------
	// load default limit value from tcp_challenge_ack_limit

	if( (f_proc = fopen( CHALLACKD_LIMIT_FILE, "r" ) ) == NULL ) {
		syslog( LOG_INFO, "failed to open proc-file" );
		return( INIT_DAEMON_FAILURE );
	}
	if( ( getline( &defptr, &deflen, f_proc ) ) == -1 ) {
		syslog( LOG_INFO, "can't read proc-file" );
		return( INIT_DAEMON_FAILURE );
	}
	if( fclose( f_proc ) != 0 ) {
		syslog( LOG_INFO, "failed to close proc-file-stream" );
		return( INIT_DAEMON_FAILURE );
	}
	
	default_limit = (int) strtol( defptr, NULL, 10 );
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
