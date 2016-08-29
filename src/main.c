// ---------------------------------
// "chackd" specific header files

#include "include/global.h"
#include "include/init_daemon.h"
#include "include/start_daemon.h"
#include "include/stop_daemon.h"

int main( int argc, char *argv[] )
{
	// ---------------------------------
	// Initialize monitoring via syslogd

	openlog( "chackd", LOG_PID, LOG_DAEMON );
	_udebug( "main procedure started" );

	// --------------------------------
	// Check if superuser is using this

	if ( geteuid() != 0 ) {
		printf( "chackd has to be executed as superuser!\n" );
		exit( EXIT_FAILURE );
	}

	// ---------------------------------------------------------------
	// getting the chack daemon parameters for base and noise value
	// TODO: unhandled errors?

	if( argc < 3 ) {
		syslog( LOG_INFO, "too few parameter, set base=100, noise=20" );
		base_value = 100;
		noise_value = 20;
	} else {
		// I do not think that error handling is necessary here
		base_value = (int) strtol( argv[1], NULL, 0 );
		noise_value = (int) strtol( argv[2], NULL, 0 );
	}
	
	if( base_value < noise_value || base_value < 0 || noise_value < 0 ) {
		syslog( LOG_INFO, "wrong parameter, set base=100, noise=20" );
		base_value = 100;
		noise_value = 20;
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
