
#ifndef SIMU_STREAM_H_
#define SIMU_STREAM_H_

#include "pista.h"
#include "pista-internal.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "simu.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct SIMU_context {

#ifdef _WIN32
    HANDLE htid;
#else
    pthread_t simu_thread;
	// pthread_mutex_t mp;
	// pthread_mutexattr_t mattr;
#endif
    bool run_thread;

    struct pista_data_packet si;
    struct pista_data_packet vi;
    struct pista_data_packet wi;

	Simu__SimuSettings s;   // config values
	Simu__SimuVitals v;   // runtime values
	Simu__SimuWaveform w;   // runtime waveform

	int packets;
	double dtick;
	double scale;

    int enable_tick_vitals;

};

extern struct pista_dev_driver simu_driver_info;

int SIMU_allocate( struct pista_dev_inst *di );
struct pista_dev_driver  *SIMU_init( struct pista_context *pista_ctx );
struct pista_data_packet *SIMU_poll( const struct pista_dev_inst *inst, int sid );
int SIMU_connect(struct pista_dev_inst *h );
int SIMU_disconnect(struct pista_dev_inst *h );
void *SIMU_config_get(const struct pista_dev_inst *h, const char *key );
int SIMU_config_set(const struct pista_dev_inst *h, const char *key, const void *value );
int SIMU_dump( const struct pista_dev_inst *h, pista_dump_flags flags );
int SIMU_destroy(struct pista_dev_inst *h );


#ifdef __cplusplus
}
#endif

#endif
