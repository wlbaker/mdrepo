
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "pista.h"
#include "pista-internal.h"
#include "medsys3.h"

/*
 * MEDSYSTEMS 3 PACKET STRUCTURE
 *
 * 4.2: host is the master and instrument is the slave.  instruments waits for command, 
 * executes command, then returns an ack, which may be piggybacked with a certain return value.
 *
 * host must wait for reply or timeout before sending consecutive commands
 *
 * 4.3.2: frame format:
 *      SOH[1]+dcf[1]+acf[1]+scf[1]+DATA[0-119]+edf[4]+CR[1]
 * 4.3.3: Start of Header (SOH) = ASCII 0x01
 * 4.3.4: Datalink control field (dcf)
 * 4.3.5: Address control field (acf)
 * 4.3.6: Session control field (scf)
 * 4.3.7: Data field
 * 4.3.8: Error detection field (edf)
 * 4.3.9: Carriage return field (CR)
 *
 * 4.4: Frame markers - SOH byte and CR byte
 * 
 * 4.5: Error detection field - 4 bytes (?)
 *
 * 4.6: Datalink control field - 1 byte
 * 4.6.1: Datalink control field layout (?)
 * 4.6.2: Host sequence bit 4: not used || reserved
 * 4.6.3: instrument seq - bit 3 and 2: seq no 0 to 3...can be ignored except for resend requests
 * 4.6.4: Ack:  bits 1 and 0
 * 4.6.4.1: Symantics of ACK field (?)
 * 4.6.4.2: NAK (?)
 *
 * 4.7: Address control field - 1 byte
 * 4.7.1: highest 3 bits are fixed mask: 010, next 5 bits are destination address
 * 4.7.2: Identification:
 * 		- host must designate a soft-id to the instrument for duration of session, part of connect command sec 4.8
 *
 * 4.8: Session Control Field - 1 byte
 * 4.8.1: Session Control Field Layout (??)
 * 4.8.2: Session State - But 4 and bit 3 (??):  CONNECT, GENERAL, DISCONNECT, REJECT
 * 4.8.2.2: 
 * 4.8.2.3: Connect command
 * 4.8.2.4: First Connect command: soft id set in address field, value 1 to 30 (see 4.9)
 * 4.8.3: Session Type - Bit 2,1,0... SESS_CM
 *
 */


/*
 * Function to compute the CRC of a sequence of data bits
 *
 * INPUT: crc initial value of crc, 16 bits
 *        pattern: input data (8 buts)
 *
 * RETURN: crc value, 16bits
 *
 * Attrib: Robert Grappel (MIT Lincoln Labs), 
 *         "Generating CRC's with Software, Design Ideas", EDN Oct 31 1984
 *
 */


static unsigned int crc_grappel( unsigned int crc, unsigned char pattern ) 
{
	unsigned char i;
	unsigned int  feedback;
	unsigned int  data;

	for( i = 0; i < 8; i++) {
		data = (pattern >> i) & 0x01;
		if( data ^ (crc & 1 ))
			feedback = 0x8408;  /* CRC - CCITT polynomial */
		else
			feedback = 0;
		crc >>= 1;
		crc ^= feedback;
	}

	return crc;
}



/*
 * Function to compute the CRC value for a specified string
 *
 * INPUT: *str	pinter to the string
 *         len	the length of the string
 *
 * RETURN: crc value
 */

#define CRC_INIT 0xffff

unsigned int ms3_asic_crc( const char *str, unsigned char len )
{
	unsigned int crc_value;
	unsigned char i;

	crc_value = CRC_INIT;

	for(i=0;i<len;i++) {
        // printf(" %c=", (unsigned char)*str);
		crc_value = crc_grappel(crc_value, (unsigned char)*str++);
        // printf("%4.4x", crc_value);
	}
    // printf("\n");

	return crc_value;
}

static const char *byte_to_binary(int x)
{
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

void ms3_dump_pkt( const char *msg, const char *buf, int len) {
	const char *bbuf;

	printf( "%s: ", msg);
	for(int i=0; i < len; i++) {
		char ch = buf[i];
		if( i == 1 ) {
			// char dcf = (FIXED_DCF << 5 ) | ( 0 << 2) | MS3_ACK; 
			bbuf = byte_to_binary(ch);
			printf(" *%3.3s host=%1.1s seq=%2.2s ack=%2.2s* ", bbuf, bbuf+3, bbuf+4, bbuf+6 );
		} else if( i == 2 ) {
			// char acf = (FIXED_ACF << 5) | SOFT_ID; 
			bbuf = byte_to_binary(ch);
			printf(" *%3.3s soft_id=%5.5s* ", bbuf, bbuf+3 );
		} else if( i == 3 ) {
			// char scf = (FIXED_SCF << 5) | (MS3_CONNECT << 3) | MS3_SESS_CM;
			bbuf = byte_to_binary(ch);
			printf(" *%3.3s conn=%2.2s sess_typ=%3.3s* ", bbuf, bbuf+3, bbuf+5 );
		} else {
			if( ch >= 0x20 && ch < 0xfe ) {
   				printf("%c", ch);
			} else {
				printf("[%02x]", (unsigned char)ch);
			}
		}
	}
	printf("\n");
}


static int save_segment( MEDSYS3_context *me, const char *key, const char *val ) {
    int code = -1;
    if( strncmp(key, "EX", 2) == 0 ) {
        // error code
        int ex_code = strtol( key+2, NULL, 16 );
        const char *m = key;
        switch(ex_code) {
            case EI_OK:
                m = "ok";
                break;
            case EI_TOKEN_RESOLUTION:
                m = "EI_TOKEN_RESOLUTION";
                break;
            case EI_TOKEN_SIZE:
                m = "EI_TOKEN_SIZE";
                break;
            case EI_EXPECTING_PHRASE_SPECIFIER:
                m = "EI_EXPECTING_PHRASE_SPECIFIER";
                break;
            case EI_EXPECTING_PARAMETER_INDEX:
                m = "EI_EXPECTING_PARAMETER_INDEX";
                break;
            case EI_EXPECTING_AFTER_PARAMETER:
                m = "EI_EXPECTING_AFTER_PARAMETER";
                break;
            case EI_EXPECT_SUBINDEX:
                m = "EI_EXPECT_SUBINDEX";
                break;
            case EI_EXPECT_ASSIGN_MARK:
                m = "EI_EXPECT_ASSIGN_MARK";
                break;
            case EI_EXPECT_DONE_MARK:
                m = "EI_EXPECT_DONE_MARK";
                break;
            case EI_EXPECT_VALUE:
                m = "EI_EXPECT_VALUE";
                break;
            case EI_DONE_SUBINDEX:
                m = "EI_DONE_SUBINDEX";
                break;
            case EI_INVALID_PARAM:
                m = "EI_INVALID_PARAM";
                break;
            case EI_INVALID_SUBINDEX_TOKEN:
                m = "EI_INVALID_SUBINDEX_TOKEN";
                break;
            case EI_RANGE_ERROR:
                m = "EI_RANGE_ERROR";
                break;
            case EI_INVALID_PHRASE:
                m = "EI_INVALID_PHRASE";
                break;
            case EI_SET_EXECUTION:
                m = "EI_SET_EXECUTION";
                break;
            case EI_QUERY_EXECUTION:
                m = "EI_QUERY_EXECUTION";
                break;
        }

        printf("* ERROR: %s\n", m );
    } else if( strncmp(key, "RX", 2) == 0 ) {

        code = strtol( key+2, NULL, 16 );
        int pump = -1;
        int *dest = NULL;
        char *sdest = NULL;

        if( strlen(key) >= 7) {
            pump = strtol( key+6, NULL, 16 );
        }

        // printf( "PARSED %s %2.2x %2.2x\n", key, code, pump );

 	    Medsys3__Sigevent *a = &me->a;
 	    Medsys3__Status *s = &me->s;
 	    Medsys3__Measurement *m = &me->m;

        switch( code ) {
            case P_PRI_TVI: //           0x0B
                if( pump == 0 ) dest = &m->pa_infused;
                else if( pump == 1 ) dest = &m->pb_infused;
                else if( pump == 2 ) dest = &m->pc_infused;
                break;
            case P_SEC_TVI:
                if( pump == 0 ) dest = &m->pa_sec_infused;
                else if( pump == 1 ) dest = &m->pb_sec_infused;
                else if( pump == 2 ) dest = &m->pc_sec_infused;
                break;
            case P_STATUS:
                if( pump == 0 ) dest = &m->pa_dev_status;
                else if( pump == 1 ) dest = &m->pb_dev_status;
                else if( pump == 2 ) dest = &m->pc_dev_status;
                else if( pump == 3 ) dest = &m->ins_status;
                break;
            case P_INFUSION_STATUS:
                if( pump == 0 ) dest = &m->pa_inf_status;
                else if( pump == 1 ) dest = &m->pb_inf_status;
                else if( pump == 2 ) dest = &m->pc_inf_status;
                break;
            case P_SYSTEM_STATE:
                // if( pump == -1 ) dest = &m->ins_status;
                break;
            case P_DRUG_NAME:  
                if( pump == 0 ) sdest = s->drug_a;
                else if( pump == 1 ) sdest = s->drug_b;
                else if( pump == 2 ) sdest = s->drug_c;
                break;
            case P_DEVICE_TYPE: 
                // if( pump == -1 ) dest = &m->ins_status;
                break;
            case P_CUR_RATE:     
                if( pump == 0 ) dest = &m->pa_rate;
                else if( pump == 1 ) dest = &m->pb_rate;
                else if( pump == 2 ) dest = &m->pc_rate;
                break;
            case P_SIGNIFICANT_EVENT:
                printf("* SIGEVENT INCOMPLETE: %d.%d=%s\n", code, pump, val );
                a->code = code;
                a->pump = pump;
 	            dest = &a->aaf_type;
 	            dest = &a->aaf_index;
                break;
            default:
	            printf( "RESPONSE UNKNOWN: %s==%s\n", key, val);
        }

        if( dest != NULL ) {
            *dest = atoi(val);
	        // printf( "SAVING AS INT: %s==%d\n", val, *dest);
        } else if( sdest != NULL ) {
            strncpy( sdest, val + 1, MS3_DRUG_LENGTH);  // VAL starts with quote mark, and ends with a quote!
            sdest[MS3_DRUG_LENGTH]='\0';                // we reserved a char for padding with a null
        } else {
	        printf( "RESPONSE FORMAT ERR: %s=%s\n", key, val);
        }
    } else {
	    printf( "SEGMENT UNKNOWN: %s=%s\n", key, val);
    }

    return code;
}

static long ahextoint( const char *ptr, int cnt ) {
    char buf[cnt];
    memcpy( buf, ptr, cnt );
    buf[cnt] = '\0';

	return strtol( buf, NULL, 16 );
}

//
// FIXME: CRC check fails for these probe packets.  Why???
//
// 01 6d 40 70 35 34 34 31 0d CRC fail: d049 != 5441
// 01 61 40 71 45 30 36 42 0d CRC fail: 6463 != E06B
//

int ms3_verify_pkt( char *buf, int len ) {

	if( buf[0] != SOH ) {
        return PISTA_ERR_NA;
	}

    if( len < 9 ) {
        return PISTA_ERR_NA;
    }

    // FIXME: this shortcuts the CRC check for probe packets, which is failing
    // for unknown reasons
	if( buf[8] == '\r' ) {
        return PISTA_OK;
	}

	int crc = ms3_asic_crc( buf, len - 5 );
    int pkt_crc = ahextoint( buf + (len-5), 4 );
    if( crc == pkt_crc ) {
        return PISTA_OK;
    }

    for( int i = 0; i < len; i++ ) {
        printf(" %2.2x", buf[i] );
    }
    // CRC failure, not a valid packet
	printf( " CRC fail: %4.4x != %4.4s\n", crc, buf + (len - 5) );
    return PISTA_ERR_NA;
}

struct pista_data_packet *ms3_process_pkt( //
        MEDSYS3_context *me,    //
        char *buf, int len                 //
        ) 
{ 
    struct pista_data_packet *sendable = NULL;

	if( buf[0] != SOH ) {
		ms3_dump_pkt( "NOSOH", buf, len );
        return NULL;
	}

    if( len < 9 ) {
		printf( "INVALID MESSAGE TOO SHORT: len=%d\n", len );
        return NULL;
    }

	// ms3_dump_pkt( "process", buf, len );
	int crc = ms3_asic_crc( buf, len - 5 );
    int pkt_crc = ahextoint( buf + (len-5), 4 );
    if( crc != pkt_crc ) {
        // CRC failure, log and ignore
		printf( "CRC fail: %4.4x != %4.4s\n", crc, buf + (len - 5) );
        return NULL;
    }

    // SOH[1]+dcf[1]+acf[1]+scf[1]+DATA[0-119]+edf[4]+CR[1]
    // [01]h@(RX00_X00=1.00;RX00_X01=1.00;RX00_X02=1.00!3D08[0d]
    
    // int dcf = buf[1];
    // int acf = buf[2];
    // int scf = buf[3];

    char *dat = buf + 4;
    char *end = buf + len - 5;

    char *key = dat;
    char *val = NULL;
	while( dat < end ) {
        if( *dat == '=' ) {
            *dat = '\0';
            val = dat + 1;
        }

        if( *dat == '!' || *dat == ';' ) {
            *dat = '\0';
            int code = save_segment( me, key, val );

            if( code == P_SEC_TVI ) {
                sendable = &me->mi;
                // we only have a meaningful rate if we are actively infusing
                if( me->m.pa_inf_status != 1 ) me->m.pa_rate = 0;
                if( me->m.pb_inf_status != 1 ) me->m.pb_rate = 0;
                if( me->m.pc_inf_status != 1 ) me->m.pc_rate = 0;
            } else if( code == P_DRUG_NAME ) {
                sendable = &me->si;
            } else if( code == P_SIGNIFICANT_EVENT ) {
                sendable = &me->ai;
            }
  
            key = dat+1;
            val = NULL;
        }
        dat++;
	}

	return sendable;
}

#define FIXED_DCF 0b011
#define FIXED_ACF 0b010
#define FIXED_SCF 0b001
#define SOFT_ID   1

const char *ms3_build_connect( char *send_buf, int buf_len ) {
    return ms3_build_message( send_buf, buf_len, NULL );
}

const char *ms3_build_message( char *send_buf, int buf_len, char *message ) {
	char dcf = (FIXED_DCF << 5 ) | ( 0 << 2) | MS3_ACK; // Datalink control field - 1 byte: bit4, unused..bit 3,2 instr seq..bit 10 ACK
	char acf = (FIXED_ACF << 5) | SOFT_ID;  // Address control field - 1 byte, highest 3 bits are fixed mask: 010, next 5 bits are destination address
	char scf = (FIXED_SCF << 5) | (MS3_CONNECT << 3) | MS3_SESS_CM;
	// scf = (FIXED_SCF << 5) | (MS3_REJECT << 3) | MS3_SESS_CM;

   	sprintf(send_buf, "\001%c%c%c",      dcf, acf, scf);
    if( message != NULL ) {
        strcat( send_buf, message );
    }

    int len = strlen(send_buf);
	int crc = ms3_asic_crc( send_buf, len );
   	sprintf(send_buf + len, "%4.4x", crc );
	strcat( send_buf, "\r");
	return send_buf;
}


