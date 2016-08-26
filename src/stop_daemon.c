#include "../include/global.h"
#include "../include/stop_daemon.h"

void stop_daemon( int rcvd_signal )
{

	_udebug( "stop signal received" );
	syslog( LOG_INFO, "stopping tcp_challenge_ack_limit randomization" );

	// ------------------------------------------------------------------
	// writing the default value into the proc file and close file stream
	// TODO: unhandled errors?

	f_proc = fopen( CHALLACKD_LIMIT_FILE, "w");
	fprintf( f_proc, "%d\n", default_limit );
	fclose( f_proc );

	// -------------------------------------------------------
	// TODO: reopen file and check if value is really restored
	
	_udebug( "default value restored" );

	// -------------------------
	// remove challackd pid file

	if( remove( CHALLACKD_PID_FILE ) == -1 ) {
		syslog( LOG_INFO, "can't remove pid file" );
		exit( EXIT_FAILURE );
	}

	_udebug( "pid file removed" );

	exit( EXIT_SUCCESS );

}
