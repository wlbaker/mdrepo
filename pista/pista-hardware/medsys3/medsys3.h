
#ifndef PISTA_MEDSYS3_PROTOCOL_H_
#define PISTA_MEDSYS3_PROTOCOL_H_

#include <stdint.h>
#include <time.h>    // time_t

#include "pista.h"
#include "pista-internal.h"
#include "medsys3.pb-c.h"

#define SOH 0x01
#define CR '\r'
#define SP 0x20

#define MS3_ACK 0x00
#define MS3_NAK 0x01


// Session Field
#define MS3_CONNECT    0b00
#define MS3_GENERAL    0b01
#define MS3_DISCONNECT 0b10
#define MS3_REJECT     0b11

// Session Type: Bits 2,1,0
#define MS3_SESS_CM     0b000
#define MS3_SESS_ASO    0b001
#define MS3_SESS_FTP    0b010
#define MS3_SESS_RFU1   0b011
#define MS3_SESS_RFU2   0b100
#define MS3_SESS_RFU3   0b101
#define MS3_SESS_RFU4   0b110
#define MS3_SESS_RFU5   0b111

#define EI_OK 0x0
#define EI_TOKEN_RESOLUTION 0x1
#define EI_TOKEN_SIZE 0x2
#define EI_EXPECTING_PHRASE_SPECIFIER 0x21
#define EI_EXPECTING_PARAMETER_INDEX  0x22
#define EI_EXPECTING_AFTER_PARAMETER  0x23
#define EI_EXPECT_SUBINDEX            0x24
#define EI_EXPECT_ASSIGN_MARK         0x25
#define EI_EXPECT_DONE_MARK           0x26
#define EI_EXPECT_VALUE               0x27
#define EI_DONE_SUBINDEX              0x28
#define EI_INVALID_PARAM              0x29
#define EI_INVALID_SUBINDEX_TOKEN     0x2A
#define EI_RANGE_ERROR                0x2B
#define EI_INVALID_PHRASE             0x2C
#define EI_SET_EXECUTION              0x2E
#define EI_QUERY_EXECUTION            0x30

#define P_RATE  0
#define P_VR    1   // volume remaining
#define P_TR    2   // time remaining
#define P_VI    3   // primary volumed infused
#define P_VI_CLEARED    4   // DDMMMYY HH:MM:SS
#define P_RVT_CONFIG    5
#define P_CHANNEL_LABEL 8
#define P_INSTR_TVI     9
#define P_TVI_SINCE_TIME    0x0A
#define P_PRI_TVI           0x0B
#define P_SEC_TVI           0x0C
#define P_STATUS            0x0D
#define P_INFUSION_STATUS   0x0F
#define P_SELECTED_PUMP     0x10
#define P_SYSTEM_STATE      0x11

#define P_DRUG_NAME        0x29
#define P_DEVICE_TYPE      0x3A
#define P_CUR_RATE         0xC0
#define P_SIGNIFICANT_EVENT  0xD1


#define MS3_DRUG_LENGTH 8


#ifdef __cplusplus
extern "C" {
#endif

typedef struct medsys3_context {
	char sbuf[256];  // send buf
	char cbuf[256];  // receive buf
	int  cpos;
	int  seq;
	time_t tick_time;

    struct pista_data_packet ai; // alarm/event item
    struct pista_data_packet si; // status item
    struct pista_data_packet mi; // measurement item

 	Medsys3__Sigevent a;
 	Medsys3__Status s;
 	Medsys3__Measurement m;
} MEDSYS3_context;

// forward declarations
struct pista_dev_driver;
extern struct pista_dev_driver medsys3_driver_info;

// device header

// function prototypes
const char  *ms3_build_connect( char *send_buf, int buf_len );
struct pista_data_packet *ms3_process_pkt( MEDSYS3_context *me, char *buf, int len );

// semi-private, device specific C api
const char *ms3_build_message( char *send_buf, int buf_len, char *message );
int ms3_verify_pkt( char *buf, int len );

// semi-private, exposed for unit testing
unsigned int ms3_asic_crc( const char *str, unsigned char len );
void ms3_dump_pkt( const char *msg, const char *buf, int len);


struct pista_dev_driver *MEDSYS3_init( struct pista_context *pista_ctx);
int MEDSYS3_allocate(  struct pista_dev_inst *di );
int MEDSYS3_handle( const struct pista_dev_inst *h, const char *cc, int len );
int MEDSYS3_destroy(struct pista_dev_inst *h);
int MEDSYS3_probe( commfunc_t out, void *commfunc_priv );
int MEDSYS3_verify(const char data[], size_t len);
int MEDSYS3_tick( const struct pista_dev_inst *di );
int MEDSYS3_cleanup(struct pista_dev_driver *drv );

#ifdef __cplusplus
}
#endif

#endif
