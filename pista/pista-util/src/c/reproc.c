
#include <stdio.h>
#include <unistd.h>

#include <pista.h>
// #include <pista-internal.h>

static bool verbose = false;

int handle( struct pista_dev_inst *pdi, FILE *fp ) {

    char buf[256];

	for(;;) {

		int n = fread(buf, 1, sizeof(buf), fp);
        if( n == 0 ) break;
		if( n > 0 ) {
            if(verbose) {
                printf("recv: ");
                for( int i = 0; i < n; i++) {
                    if( buf[i] >= 0x20 ) {
                        printf("%c", buf[i]);
                    } else {
                        printf("%%%2.2d", buf[i]);
                    }
                }
                printf("\n");
            }
		    pdi->driver->handle( pdi, buf, n );	
		}
		if( n < 0) {
			perror("read err");
			return -1;
		}
	}

	return 0;
}

int event_dumper( void *cb, struct pista_data_packet *pkt)
{
    pista_dump_packet( pkt );
    printf("\n");
    return PISTA_OK;
}

int main(int argc, char* argv[])
{
	if( argc != 3 ) {
		printf("usage: <prog> <driver-name> <data-file>\n");
	    return 0;
	}

    char *driver_name = argv[1];
    char *file_name = argv[2];


    struct pista_context *ctx;
    pista_init( &ctx );

    pista_load_plugin( ctx, driver_name, NULL );
    struct pista_dev_driver *driver = pista_find_driver( ctx, driver_name );

    if( driver == NULL ) {
	    fprintf(stderr, "Could not find driver: %s!\n", driver_name);
	    return -2;
    }

    struct pista_dev_inst di;
    pista_allocate( driver, &di );
    pista_set_event_handler( &di, event_dumper, NULL );

   		di.status = PISTA_ST_NOT_CONNECTED;

	printf("READING %s for %s\n", file_name, driver_name );
	printf("============================\n");
    // pista_connect( &di );

    FILE *fp = fopen( file_name, "r");
    if( fp == NULL ) {
	    fprintf(stderr, "Could not open data file: %s!\n", file_name);
	    return -3;
    }
    handle( &di, fp );
    fclose(fp);

	// pista_disconnect( &di );
}

