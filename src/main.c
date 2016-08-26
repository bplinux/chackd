// ----------------------------
// "challackd" specific header files

#include "global.h"
#include "init_daemon.h"
#include "start_daemon.h"
#include "stop_daemon.h"

int main( int argc, char *argv[] )
{
	// ---------------------------------
	// Initialize monitoring via syslogd

	openlog( "challackd", LOG_PID, LOG_DAEMON);
	_udebug( "main procedure started" );

	if ( geteuid() != 0 ) {
		printf("challackd has to be executed as superuser!\n");
		exit( EXIT_FAILURE );
	}

	// ---------------------------------------------------------------
	// getting the challack daemon parameters for base and noise value
	// TODO: unhandled errors?

	if( argc < 3 ) {
		syslog( LOG_INFO, "too few parameter, set base=200, noise=40" );
		base_value = 200;
		noise_value = 40;
	} else {
		base_value = atoi( argv[1] );
		noise_value = atoi( argv[2] );
	}
	
	if( base_value < noise_value || base_value < 0 || noise_value < 0) {
		syslog( LOG_INFO, "wrong parameter, set base=200, noise=40" );
		base_value = 200;
		noise_value = 40;
	}

	
	// ------------------------------------------------	
	// Handle daemon initialization and possible errors

	switch( init_daemon() ) {
	case INIT_DAEMON_SUCCESS:
		_udebug( "daemon initialization finished" );
		start_daemon();
		break;
	case INIT_DAEMON_FAILURE:
	default:
		_udebug( "daemon initialization failed" );
		stop_daemon( SIGUSR1 ); // SIGUSR1 not necessary at this point
		break;
	}

	// ------------------------------------
	// Something weird; should never happen
	
	syslog( LOG_INFO, "main procedure exception" );
	exit( EXIT_FAILURE );

}
