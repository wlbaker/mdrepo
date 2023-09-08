
#include <stdio.h>
#include "simu-api.h"
#include <unistd.h>  // sleep

int evt_tester( void *priv, struct pista_data_packet *pkt )
{
    struct pista_dev_inst *inst = (struct pista_dev_inst *)priv;

    	printf("callback: %c %d DESC at %lx\n", pkt->stream_id, pkt->payload_sz, pkt->desc );
    	pista_dump_desc(pkt->desc, pkt->field_cnt, pkt->payload);

    return PISTA_OK;
}

void main ()
{
    long loop = 0;

    struct pista_context *ctx = NULL;
    struct pista_dev_driver drv;
    struct pista_dev_inst di;

    printf (" ---------------------------------------------------------\n");

    SIMU_init( ctx, &drv );
    SIMU_allocate( &drv, &di );

    di.event_handler = evt_tester;

    SIMU_connect( &di );


    /* During the BACKGROUND operation, tick*/
    while ( loop < 10 ) {

    	printf ("* tick\n");
        loop++;
        sleep(1);
        // SIMU_meas_tick( &di );
   }

   printf ("Data collection terminated.\n");
   SIMU_disconnect( &di );
   SIMU_destroy( &di );
   
   printf ("Stopped and released\n");
}

