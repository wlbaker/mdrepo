
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stddef.h>   /* offsetof */

#include "pista.h"
#include "pista-internal.h"

#include "imp731.h"

// used by IMPACT
static unsigned char crcTable0c2[256] = { //
	0, 145, 97, 240, 194, 83, 163, 50, 199, 86, 166, 55, 5, 148, 100, 245, //
	205, 92, 172, 61, 15, 158, 110, 255, 10, 155, 107, 250, 200, 89, 169, 56, //
	217, 72, 184, 41, 27, 138, 122, 235, 30, 143, 127, 238, 220, 77, 189, 44, //
	20, 133, 117, 228, 214, 71, 183, 38, 211, 66, 178, 35, 17, 128, 112, 225, //
	241, 96, 144, 1, 51, 162, 82, 195, 54, 167, 87, 198, 244, 101, 149, 4, //

	60, 173, 93, 204, 254, 111, 159, 14, 251, 106, 154, 11, 57, 168, 88, 201, //
	40, 185, 73, 216, 234, 123, 139, 26, 239, 126, 142, 31, 45, 188, 76, 221, //
	229, 116, 132, 21, 39, 182, 70, 215, 34, 179, 67, 210, 224, 113, 129, 16, //
	161, 48, 192, 81, 99, 242, 2, 147, 102, 247, 7, 150, 164, 53, 197, 84, //
	108, 253, 13, 156, 174, 63, 207, 94, 171, 58, 202, 91, 105, 248, 8, 153, //

	120, 233, 25, 136, 186, 43, 219, 74, 191, 46, 222, 79, 125, 236, 28, 141, //
	181, 36, 212, 69, 119, 230, 22, 135, 114, 227, 19, 130, 176, 33, 209, 64, //
	80, 193, 49, 160, 146, 3, 243, 98, 151, 6, 246, 103, 85, 196, 52, 165, //
	157, 12, 252, 109, 95, 206, 62, 175, 90, 203, 59, 170, 152, 9, 249, 104, //
	137, 24, 232, 121, 75, 218, 42, 187, 78, 223, 47, 190, 140, 29, 237, 124, //
	68, 213, 37, 180, 134, 23, 231, 118, 131, 18, 226, 115, 65, 208, 32, 177 //
};


static unsigned char calcCRC( int initial, const char *buffer, int numBytes) 
{
	unsigned char crc = initial;
	int i;
	for( i = 0; i < numBytes; i++ ) {
		unsigned int z = (unsigned char) buffer[i];
 		unsigned int idx = crc ^ z;
		crc = crcTable0c2[ idx ];
	}
	return crc;
}

static long ahextoi( const char *ptr) {
	return strtol( ptr, NULL, 16 );
}

static long ahextoint( const char *ptr, int cnt ) {
    char buf[cnt];
    memcpy( buf, ptr, cnt );
    buf[cnt] = '\0';

	return strtol( buf, NULL, 16 );
}

static void parseBreathPacket( Imp731__Breath *b, const char *buf, int len);
static void parseEmvInfoPacket(const char *buf, int len);
static void parseStreamPacket( Imp731__Sensors *s, int offset, const char *buf, int len );
static void parseStatusPacket( Imp731__Status *s, const char *buf, int len );

static void dump_pkt( const char *msg, const char *buf, int len) {
	printf( "%s: ", msg);
	for(int i=0; i < len; i++) {
		char ch = buf[i];
		if( ch >= 0x20 && ch < 0xfe ) {
   			printf("%c", ch);
		} else {
			printf("[%02x]", (unsigned char)ch);
		}
	}
	// printf("\n");
}

void IMP731_process_pkt( const struct pista_dev_inst *h, const char *buf, int len )
{
	struct IMP731_context *me = (struct IMP731_context *)h->priv;

    unsigned int buf0 = buf[0];

	if( buf0 != STX ) {
        //if( buf0 == 'x' || buf0 == 0xb8 || buf0 == 0xf8 ) {
            // I don't know what these packets are
            // ...I think they are overflow from a buffer...excess from impact...wrong packet length in their firmware
            // ignore
            //return;
        //}
		// dump_pkt( "NOSTX", buf, len );
		return;
	}

    struct pista_data_packet *sendable = NULL;
    // dump_pkt( "PKT", buf, len );

	switch( (unsigned char)buf[1] ) {
		case GUI_STATUS:
	        // dump_pkt( "GUI", buf, len );
            // printf("G");
		break;
		case BREATH_PACKET:
			parseBreathPacket(&me->b, buf, len);
	        // dump_pkt( "BREATH", buf, len );
            sendable = &me->bi;
            printf("B");
		break;
		case STREAM_PACKET:
            me->packet_cnt = (me->packet_cnt + 1) % 4;  // only parse one packet in four...dont need that resolution
            if( me->packet_cnt == 0 ) {
			    parseStreamPacket(&me->w, me->w_offset, buf, len);
                me->w_offset++;
                if( me->w_offset == me->w.n_w0 ) {
                    me->w_offset = 0;
                    sendable = &me->wi;
                }
            }
            // printf("s");
		break;
		case STATUS_PACKET:
			parseStatusPacket( &me->s, buf, len);
            me->status_cnt++;
            if( me->status_cnt == 10 ) {
                me->status_cnt = 0;
                sendable = &me->si;

	            // dump_pkt( "STATUS", buf, len );
            }
            // printf("S");
		break;
		case UNKNOWN_5F:
			// cout << "MY5F:" << hex << (int)buf[1]  <<  " len=" << len << endl;
            printf("u");
		break;
		case UNKNOWN_63:
			// cout << "MY63:" << hex << (int)buf[1]  <<  " len=" << len << endl;
            printf("v");
		break;
		case UNKNOWN_F6:
			// ??
            printf("w");
		break;
		case READ_CUR_TIME:
		case READ_CUR_DATE:
		case READ_DATE_TIME:
			// cout << "DATE_TIME: ?" << endl;
		break;
		case READ_RUN_HOURS:
		case READ_RUN_STATISTICS:
			// 
		break;
		case EMV_PACKET:
			// Ignoring
            // printf("E");
		break;
		case EMV_PLETH:
			// ignoring PLETH
            // printf("P");
		break;
		case EMV_INFO:
			// the parser is here, but I'm not storing the information
			parseEmvInfoPacket(buf, len);
            printf("I");
		break;
		case IMP_ACK:
		case IMP_NAK:
			puts("\nGOT UNEXPECTED ACK/NACK\n");
		break;
		case READ_SPM_VER:
			puts( "R");;
		default:
			dump_pkt( "UNIMP", buf, len );
			//cout << endl << "UNIMP: 0x" << hex << (int)buf[1]  <<  " len=" << len << ": ";
			//for(int i=0; i<len; i++) {
    			//std::cout << std::hex << (unsigned int)(unsigned char)buf[i] << ".";
			//}
			//cout << endl;
	}

    // printf( "[S] %lx %lx\n", (unsigned long)sendable , (unsigned long)h->event_handler );
    if( sendable != NULL && h->event_handler != NULL ) {
        sendable->tm = pista_get_current_time_with_ms();
        h->event_handler( h->event_priv, sendable );
    }

	return;
}

static void parseEmvInfoPacket( const char *buf, int len ) 
{
	const char *ptr = buf + 4;

	char model[9];
	char serial_no[10];
	char cpu_id[18];
	char adapter_id[18];
	char pim_id[18];
	char spm_model[9];
	char spm_serial[10];
	char silent_mode[18];
	// int contrast;
	char emv_version[9];

	memcpy( model, ptr, sizeof(model)-1 ); ptr+= 9;  // 1
	memcpy( serial_no, ptr, sizeof(serial_no)-1 ); ptr+= 10;  // 2
	memcpy( cpu_id, ptr, sizeof(cpu_id)-1 ); ptr+= 18;  // 3
	memcpy( adapter_id, ptr, sizeof(adapter_id)-1 ); ptr+= 18;  // 4
	memcpy( pim_id, ptr, sizeof(pim_id)-1 ); ptr+= 18;  // 5
	memcpy( spm_model, ptr, sizeof(spm_model)-1 ); ptr+= 9;  // 6
	memcpy( spm_serial, ptr, sizeof(spm_serial)-1 ); ptr+= 10;  // 7
	memcpy( silent_mode, ptr, sizeof(silent_mode)-1 ); ptr+= 18;  // 8
	// contrast = 
    ahextoint( ptr, 2 ); ptr += 2;  // ignore
	memcpy( emv_version, ptr, sizeof(emv_version)-1 ); ptr+= 11;  // 8

	model[sizeof(model)-1] = '\0';
	serial_no[sizeof(serial_no)-1] = '\0';
	cpu_id[sizeof(cpu_id)-1] = '\0';
	adapter_id[sizeof(adapter_id)-1] = '\0';
	pim_id[sizeof(pim_id)-1] = '\0';
	spm_model[sizeof(spm_model)-1] = '\0';
	spm_serial[sizeof(spm_serial)-1] = '\0';
	silent_mode[sizeof(silent_mode)-1] = '\0';
	emv_version[sizeof(emv_version)-1] = '\0';

	printf( "EVM: %s %s %s\n", model, spm_serial, emv_version);

}

static void parseStreamPacket( Imp731__Sensors *s, int offset, const char *buf, int len ) 
{
	const char *ptr = buf + 4;
	s->w0[offset] = ahextoi( ptr ); ptr+= 6;  // 1
	s->w1[offset] = ahextoi( ptr ); ptr+= 6;  // 2
	s->w2[offset] = ahextoi( ptr ); ptr+= 6;  // 2
	s->w3[offset] = ahextoi( ptr ); ptr+= 6;  // 2
	ahextoint( ptr, 1 );
}

/**
 * @brief Parser the status packet.
 */
static void parseStatusPacket( Imp731__Status *s, const char *buf, int len ) 
{
	const char *ptr = buf + 4;
	s->tv = ahextoint( ptr, 4 ); ptr+= 4;  // 1
	s->i_ie = ahextoint( ptr, 6 ); ptr+= 6;  // 2
	s->e_ie = ahextoint( ptr, 6 ); ptr+= 6; // 3
	s->peep = ahextoint( ptr, 4 ); ptr+= 4; // 4
	s->phi = ahextoint( ptr, 4 ); ptr+= 4; // 5
	s->plow = ahextoint( ptr, 4 ); ptr+= 4; // 6
	s->br = ahextoint( ptr, 3 ); ptr+= 3; // 7
	s->fio2 = ahextoint( ptr, 4 ); ptr+= 4; // 8
	s->trigger = ahextoint( ptr, 3 ); ptr+= 3; // 9

    // printf("\n%32.32s ", ptr); // show the alarm bits
	s->nonop_alarm = ahextoint( ptr, 9 ); ptr+= 9; // 10
	s->op_alarm = ahextoint( ptr, 9 ); ptr+= 9; // 11
	s->advisory_alarm = ahextoint( ptr, 9 ); ptr+= 9; // 12
    /**
    * Stream source bit layout:
    *   [0:3] - Stream #1
    *   [4:7] - Stream #2
    *   [8:11] - Stream #3
    *   [12:15] - Stream #4
    *
    * Values:
    *   0   O2 Valve Flow
    *   1   Ambient Pressure
    *   2   Compressor Flow
    *   3   Air Pressure
    *   4   Air Valve Flow
    *   5   Intake Pressure
    *   6   Airway Pressure
    *   ...
    */
	s->s_source = ahextoint( ptr,5 ); ptr+= 5; // 13 -- stream source
	s->s_type = ahextoint( ptr,2 ); ptr+= 2; // 14 --stream type 0x0==Raw, 0x0f=Calibrated
	s->pga_temp = ahextoint( ptr,5 ); ptr+= 5; // 15 -- PGA Temperature
	s->p_o2_tank = ahextoint( ptr,4 ); ptr+= 4; // 16 -- O2 Pressure
	s->p_ambient = ahextoint( ptr,3 ); ptr+= 3; // 16 -- Ambient Pressure
	s->p_mode = ahextoint( ptr,3 ); ptr+= 3; // 18 -- Powerup Mode
	s->mode = ahextoint( ptr,5 ); ptr+= 5; // 19 -- Mode Setting
	s->ie_ratio = ahextoint( ptr,5 ); ptr+= 5; // 20 IE

    // s->bpm_high;
    // s->bpm_low;
    // s->tv_high;
    // s->tv_low;
    // s->p_support;
    // s->p_target;
    // s->rise_tm;

    if( (s->mode & 0x7) == 0 ) {  // standby == 0 in bits [0:2]
	    s->tv = 0;
	    s->i_ie = 0;
	    s->e_ie = 0;
	    s->peep = 0;
	    s->phi = 0;
	    s->plow = 0;
	    s->br = 0;
	    s->fio2 = 0;
	    s->trigger = 0;
	    s->nonop_alarm = 0;
	    s->op_alarm = 0;
	    s->advisory_alarm = 0;
    }
	
}

static void parseBreathPacket( Imp731__Breath *b, const char *buf, int len)
{
	// printf( "BR.TV=%5.5s\n", (buf+3) );
	// printf( "BR.itime=%5.5s\n", (buf+8) );
	// printf( "BR.etime=%5.5s\n", (buf+13) );
    //
	const char *ptr = buf + 4;
	b->tv = ahextoi( ptr ); ptr+= 5;  // 1
    b->i_ie = ahextoi(ptr); ptr += 5;
    b->e_ie = ahextoi(ptr); ptr += 5;
    b->peep = ahextoi(ptr); ptr += 4;
    b->pip = ahextoi(ptr); ptr += 4;
    b->bpm = ahextoi(ptr); ptr += 3;
    b->mv = ahextoi(ptr); ptr += 5;
    b->rpm = ahextoi(ptr); ptr += 5;
    b->pend = ahextoi(ptr); ptr += 4;
    b->pmean = ahextoi(ptr); ptr += 4;
    b->ppeak = ahextoi(ptr); ptr += 4;
    b->mgmpo2 = ahextoi(ptr); ptr += 4;
    b->mgmpo2min = ahextoi(ptr); ptr += 4;
    b->mgmpo2flow = ahextoi(ptr); ptr += 4;
    b->mgmcompflow = ahextoi(ptr); ptr += 4;
    b->leak = ahextoi(ptr); ptr += 4;
    b->airway_baseline = ahextoi(ptr); ptr += 4;
    b->failed_autocal = ahextoi(ptr); ptr += 2;
    ptr += 2; // skip cycle count
    b->baseline_noise = ahextoi(ptr); ptr += 4;
    b->pga_paw_offset = ahextoi(ptr); ptr += 6;
    b->pga_o2_offset = ahextoi(ptr); ptr += 6;
    b->pga_flow_offset = ahextoi(ptr); ptr += 6;
    b->o2_mv = ahextoi(ptr); ptr += 5;
    b->plat = ahextoi(ptr);
}

const char *IMP731_get_id( char *send_buf, int crc_seed ) {
	char ID[] = "?2 00000000 ";
	ID[0] = HOST_MSG_ENABLE;
	int crc = calcCRC( crc_seed, ID, sizeof(ID) - 1 );

	// std::stringstream sstm;
   	// sstm << (char)STX << ID << setfill('0') << setw(2) << hex << crc << (char)ETX;
	// const char *buf = strdup(sstm.str().c_str() );

   	sprintf(send_buf, "%c%s%02x%c", STX, ID, crc , ETX);
	return send_buf;
}

static const char *get_noarg( char *send_buf, int crc_seed, int ch ) {
	char dat[] = "? 0 ";
	dat[0] = ch;
	int crc = calcCRC( crc_seed, dat, sizeof(dat) - 1 );

	// std::stringstream sstm;
   	// sstm << (char)STX << dat << setfill('0') << setw(2) << hex << crc << (char)ETX;
	// const char *send_buf = strdup(sstm.str().c_str() );

   	sprintf(send_buf, "%c%s%02x%c", STX, dat, crc , ETX);
	return send_buf;
}

//static const char *get_ack( char *send_buf, int crc_seed ) {
	//return get_noarg( send_buf, crc_seed, IMP_ACK );
//}
//
//static const char *get_nak( char *send_buf, int crc_seed ) {
	//return get_noarg( send_buf, crc_seed, IMP_NAK );
//}
//
//static const char *get_cur_time( char *send_buf, int crc_seed ) {
	//return get_noarg( send_buf, crc_seed, READ_CUR_TIME);
//}
//
//static const char *get_spm_ver( char *send_buf, int crc_seed ) {
	//return get_noarg( send_buf, crc_seed, READ_SPM_VER);
//}

const char *IMP731_get_emv_info( char *send_buf, int crc_seed ) {
	return get_noarg( send_buf, crc_seed, READ_SPM_VER);
}

