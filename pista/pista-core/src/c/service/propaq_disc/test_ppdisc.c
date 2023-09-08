
#include <signal.h>
#include <getopt.h>
#include <stdio.h>

#include <unistd.h>

#include "pista.h"
#include "pp_api.h"

static volatile int force_exit;


int64_t pista_get_current_time_with_ms() {
    return 0;
}

void sighandler(int sig)
{
	force_exit = 1;
}

void handler( const void *priv, const struct pista_discovery_info *pdi )
{
    printf("discovery: %d %s %s\n", pdi->event_type, pdi->name, pdi->url );
}

int main(int argc, char **argv)
{
    struct pista_context *ctx = NULL;
    struct pista_discovery_service ds;

	int ret = 0;

    setbuf( stdout, NULL ); // use this if you want unbuffered stdout for JVM debugging
	signal(SIGINT, sighandler);

    PPDISC_init( ctx, &ds );

    PPDISC_start( &ds );
    PPDISC_set_callback( &ds, handler, NULL );


	while (!force_exit) {
        printf("T");
        fflush(stdout);
        PPDISC_tick( &ds );
        sleep(1);
	}

    PPDISC_stop( &ds );

	return ret;

}




