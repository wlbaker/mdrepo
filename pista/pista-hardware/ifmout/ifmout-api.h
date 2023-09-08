
#ifndef PISTA_IFMOUT_PROTOCOL_H_
#define PISTA_IFMOUT_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"

#include "ifmout.h"
#include "model/ifmout.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct IFMOUT_context {

	time_t tick_time;
	int  tick_seq;

    struct ifmout_context ctx;
    struct pista_data_packet mi;

	Bmp180__Measurement m;
};


extern struct pista_dev_driver ifmout_driver_info;

#ifdef __cplusplus
}
#endif

#endif
