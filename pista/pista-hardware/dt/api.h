
#ifndef U3_STREAM_H_
#define U3_STREAM_H_

#include "pista.h"
#include "pista-internal.h"
#include "../../model/dt.pb-c.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NUM_BUFFERS 4
#define STRLEN 80        /* string size for general text manipulation   */

struct DT__caps {
   double max_hzz;
   int dma;
   int gainsup;
};

struct DT_context {

   HDEV  hdrvr;        /* device handle            */
   HDASS hdass;        /* sub system handle        */
   ECODE status;       /* board error status       */
   char name[STRLEN];  /* string for board name    */
   char entry[STRLEN]; /* string for board name    */

   UINT numberADs = 0;

	DT__caps caps;   // config values
	DT__DTSettings s;   // config values

	DT__DTsensor *d;

	int n_channels;
	int *channel_map;  // array of channels
};

#ifdef __cplusplus
}
#endif

#endif
