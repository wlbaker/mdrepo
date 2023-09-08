
#ifndef U3_STREAM_H_
#define U3_STREAM_H_

#include "u3.h"
#include "../../model/u3.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

struct U3_context {
   PISTA_DEVICE_PRIVATE;

	HANDLE hDevice;
	
	U3__U3Settings s;   // config values

	// config computed values
	int scanInterval;
	int numCh;
	int usb_spp;
	int hw_scanInterval;
	int hw_scanSkip;  // for very slow data rates...less than like 40samples/sec...must skip some pkts
	int chMap[16];  // actually initialized in streamConfig

	// state between data reads
	int discard;
	int m;
	int k;
	int mult;
	int pkt_sz;
	uint8 *recBuff;
	
	// computed
	int bufsz;  // number of records in ibuf and dbuf

	int totPackets;
	int backlog;

	U3CalibrationInfo caliInfo;

	U3__U3Fsensor *u3f;
	U3__U3Esensor *u3e;
	int32_t *ch_ibuf[16];

};

// typedef struct U3_C_DATA_MODEL U3CDataModel;
struct U3CalibrationInfo;

int U3_CDM_apply_settings( struct U3_context *cdm);

int U3_openUSBConnection( struct U3_context *cdm, int localID);
void U3_closeUSBConnection( struct U3_context *cdm);   //Closes a HANDLE to a U3 device.

int U3_getCalibrationInfo(struct U3_context *cdm);
int U3_configIO(struct U3_context *cdm, int fio, int eio);
int U3_streamConfig(struct U3_context *cdm);
int U3_streamStart(struct U3_context *cdm);
int U3_streamData(struct U3_context *cdm);
int U3_streamStop(struct U3_context *cdm);

#ifdef __cplusplus
}
#endif

#endif
