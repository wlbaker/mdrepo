
#ifndef PISTA_MCCUL_PROTOCOL_H_
#define PISTA_MCCUL_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"

#include "cbw.h"


#ifdef __cplusplus
extern "C" {
#endif

struct IWAV {
	int *idat;
};
typedef struct IWAV IWav;

struct DWAV {
	double *ddat;
};
typedef struct DWAV DWav;

#define LOG_PREFIX "mcc-ul"

struct MCCUL_context {
    PISTA_DEVICE_PRIVATE;

	char sbuf[256];  // send buf
	char cbuf[256];  // receive buf
	int  cpos;
	int  seq;
	time_t tick_time;
};

struct MCCUL_C_DATA_MODEL {

	// computed
	int bufsz;  // number of records in ibuf and dbuf

	// model data
	int totPackets;
	int backlog;
	IWav ibuf[16];
	DWav dbuf[16];

};


// device header
typedef struct MCCUL_C_DATA_MODEL MCCULDataModel;

// function prototypes
void MCCUL_process_pkt( const char *recv_buf, int len );

extern struct pista_dev_driver mccul_driver_info;

#ifdef __cplusplus
}
#endif

#endif
