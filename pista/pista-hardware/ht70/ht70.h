
#ifndef PISTA_HT70_PROTOCOL_H_
#define PISTA_HT70_PROTOCOL_H_

// #define POSIX_C_SOURCE 200809L
#ifndef __USE_XOPEN_EXTENDED
#define __USE_XOPEN_EXTENDED
#endif

#include <stdint.h>
#include <time.h>    // time_t
#include <string.h>

#include "pista.h"
#include "pista-internal.h"
#include "ht70.pb-c.h"

#include <expat.h>

#ifdef __cplusplus
extern "C" {
#endif

struct HT70_context {

	int  seq;
	time_t tick_time;
    XML_Parser p;

    struct pista_data_packet ai; // alarm/event item
    struct pista_data_packet si; // status item
    struct pista_data_packet mi; // measurement item
    struct pista_data_packet wi; // waveform item

 	Ht70__Alarms a;
 	Ht70__Status s;
 	Ht70__Breath m;
 	Ht70__Sensors w;

    bool fire_alarm;
    bool fire_measurement;
    bool fire_status;
    bool fire_waveform;
    bool reset;

    int depth;
    char *stack[16];
    char wave_name[32];
    char element_name[32];

    char charbuf[128];
    int charbuf_pos;

};

// forward declarations
struct pista_dev_driver;
extern struct pista_dev_driver ht70_driver_info;

// device header

// function prototypes
const char  *ht70_build_connect( char *send_buf, int buf_len );
int ht70_process_pkt( void *userData, const char *buf, int len );

// semi-private, device specific C api
int ht70_verify_pkt( char *buf, int len );

// semi-private, exposed for unit testing
unsigned int ht70_asic_crc( const char *str, unsigned char len );
void ht70_dump_pkt( const char *msg, const char *buf, int len);

void ht70_install_parser(struct HT70_context *context);
int ht70_b64decode(int *output, const void* data, const size_t len);


struct pista_dev_driver *HT70_init( struct pista_context *pista_ctx );
int HT70_allocate( struct pista_dev_inst *di );
int HT70_handle( const struct pista_dev_inst *h, const char *cc, int len );
int HT70_destroy(struct pista_dev_inst *h);
int HT70_probe( commfunc_t out, void *commfunc_priv );
int HT70_verify(const char data[], size_t len);
int HT70_tick( const struct pista_dev_inst *di );
int HT70_cleanup(struct pista_dev_driver *drv );

#ifdef __cplusplus
}
#endif

#endif
