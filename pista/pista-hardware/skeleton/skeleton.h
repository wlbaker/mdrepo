
#ifndef PISTA_SKELETON_PROTOCOL_H_
#define PISTA_SKELETON_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"

#include "model/skeleton.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct skeleton_context {

#ifdef _WIN32
    HANDLE htid;
#else
    pthread_t skeleton_thread;
#endif
    bool run_thread;

    struct pista_data_packet vi;
    struct pista_data_packet wi;

 	Skeleton__Vitals v;
 	Skeleton__Sensors w;

    /*
     * state variables for the waveform parser
     */
    int arr_pos;
    int *arr_dest;
    int wave_num;
    int wave_status;

    /*
     * state variables for the trend parser
     */
    char *ztr_keystack[16];
} SKELETON_context;


void SKELETON_process_pkt( const struct pista_dev_inst *h, const char *recv_buf, int len );

extern struct pista_dev_driver skeleton_driver_info;


// privates
extern int atoi_n( const char *buf, size_t len );

int SKELETON_init( struct pista_context *pista_ctx, struct pista_dev_driver *drv );
int SKELETON_allocate( struct pista_dev_driver *drv, struct pista_dev_inst *di );
int SKELETON_connect( struct pista_dev_inst *di );
int SKELETON_tick( const struct pista_dev_inst *di );
int SKELETON_disconnect( struct pista_dev_inst *di );
int SKELETON_destroy(struct pista_dev_inst *di);
int SKELETON_config_set(const struct pista_dev_inst *h, const char *key, const void *settings );

#ifdef __cplusplus
}
#endif

#endif
