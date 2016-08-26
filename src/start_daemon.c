#include "global.h"
#include "start_daemon.h"

static int generate_next( int local_base_value, int local_noise_value )
{
	int noise_random;

	_udebug( "generating random limit value" );

	noise_random = rand() % local_noise_value;

	// -------------------------------------------------------
	// either subtract or adding the noise_value to base_value

	switch( rand()&1 ) {
	case 0:
		return( local_base_value - noise_random );
		break;
	case 1:
	default:
		return( local_base_value + noise_random );
		break;
	}	

	// -------------------------------------------------
	// Failure in switch case, returning with base_value

	_udebug( "failure in generate_next(), returning with base_value" );
	return( local_base_value );

}

void start_daemon()
{
	syslog( LOG_INFO, "starting tcp_challenge_ack_limit randomization" );

	int next;

	while( 1 ) {
		sleep( 2 ); // two seconds of daemon thread sleep

		next = generate_next( base_value, noise_value );

		if( ( f_proc = fopen( CHALLACKD_LIMIT_FILE, "w" ) ) == NULL ) {
			_udebug( "failed to open proc file, skipping..." );
			continue;
		}
		
		fprintf( f_proc, "%d\n", next );
		fclose( f_proc );
	}

}
