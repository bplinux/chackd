#include "include/global.h"
#include "include/stop_daemon.h"

void stop_daemon( int rcvd_signal )
{

	_udebug( "stop signal received" );
	syslog( LOG_INFO, "stopping tcp_challenge_ack_limit randomization" );

	// ------------------------------------------------------------------
	// writing the default value into the proc file and close file stream

	if( ( f_proc = fopen( CHACKD_LIMIT_FILE, "w") ) == NULL ) {
		syslog( LOG_INFO, "failed to open proc-file" );
		exit( EXIT_FAILURE );
	}
	if( fprintf( f_proc, "%d\n", default_limit ) < 0 ) {
		syslog( LOG_INFO, "failed to write value to proc-file" );
		exit( EXIT_FAILURE );
	}
	fclose( f_proc );

	// -------------------------------------------------------
	// TODO: reopen file and check if value is really restored
	
	_udebug( "default value restored" );

	// -------------------------
	// remove chackd pid file

	if( remove( CHACKD_PID_FILE ) == -1 ) {
		syslog( LOG_INFO, "can't remove pid file" );
		exit( EXIT_FAILURE );
	}

	_udebug( "pid file removed" );

	exit( EXIT_SUCCESS );

}
