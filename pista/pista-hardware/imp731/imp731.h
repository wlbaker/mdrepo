
#ifndef PISTA_IMP731_PROTOCOL_H_
#define PISTA_IMP731_PROTOCOL_H_

#include <stdint.h>
#include "pista.h"
#include "pista-internal.h"

#include "imp731.pb-c.h"

#define HOST_MSG_ENABLE 0xf5
#define UNKNOWN_F6	0xf6
#define EMV_PACKET 0xf0
#define EMV_INFO 0xfb
#define EMV_PLETH 0xf2
#define GUI_STATUS 0xfa
#define UNK_F8 0xf8
#define UNK_B8 0xb8
#define UNKNOWN_5F	0x5f
#define STREAM_PACKET  0x60
#define BREATH_PACKET  0x61
#define STATUS_PACKET  0x62
#define UNKNOWN_63	0x63
#define READ_DATE_TIME 0x66

#define STX 0x02
#define ETX 0x03
#define SP 0x20

#define IMP_ACK 0xFF
#define IMP_NAK 0x01

#define READ_CAL_HEADER 0x24
#define READ_RUN_HOURS      0x27
#define READ_SPM_VER        0x28
#define READ_RUN_STATISTICS 0x1c
#define READ_CUR_DATE      0x39
#define READ_CUR_TIME      0x42



#ifdef __cplusplus
extern "C" {
#endif

struct IMP731_context {

	char sbuf[256];  // send buf
	char cbuf[256];  // receive buf
	int  cpos;
	// int  seq;
	time_t tick_time;

	int  w_offset;
	int  status_cnt;
    int  packet_cnt; // used to consolidate 4 pkts in one

    struct pista_data_packet ii;
    struct pista_data_packet si;
    struct pista_data_packet bi;
    struct pista_data_packet wi;

 	Imp731__Ident i;
 	Imp731__Status s; // settings
 	Imp731__Breath b;
 	Imp731__Sensors w;
};


// device header
// typedef struct IMP731_C_DATA_MODEL IMP731CDataModel;

#define CRC_SEND_SEED 0x73
#define CRC_RECV_SEED 0xff

// function prototypes
const char *IMP731_get_id( char *send_buf, int crc_seed );
const char *IMP731_get_emv_info( char *send_buf, int crc_seed );
void IMP731_process_pkt( const struct pista_dev_inst *h, const char *recv_buf, int len );
// unsigned char calcCRC( int initial, const char *buffer, int numBytes);

extern struct pista_dev_driver imp731_driver_info;

#ifdef __cplusplus
}
#endif

#endif
