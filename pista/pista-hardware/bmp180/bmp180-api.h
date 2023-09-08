
#ifndef PISTA_BMP180_PROTOCOL_H_
#define PISTA_BMP180_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"

#include "bmp180.h"
#include "bmp180.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct BMP180_context {

	time_t tick_time;
	int  tick_seq;

    struct bmp180_context ctx;
    struct pista_data_packet mi;

	Bmp180__Measurement m;
};


extern struct pista_dev_driver bmp180_driver_info;

struct pista_dev_driver *BMP180_init( struct pista_context *pista_ctx );
int BMP180_allocate( struct pista_dev_inst *di );
int BMP180_set_option(const struct pista_dev_inst *h, const char *key, const void *value );
int BMP180_connect(struct pista_dev_inst *h);
int BMP180_disconnect(struct pista_dev_inst *h);
int BMP180_destroy(struct pista_dev_inst *h);
int BMP180_tick( const struct pista_dev_inst *h );


#ifdef __cplusplus
}
#endif

#endif
