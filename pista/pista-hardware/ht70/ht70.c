

// #include <stdlib.h>
// #include <stdio.h>
// #include <time.h>
// #include <string.h>

#define _GNU_SOURCE
#include <string.h>  // memmem is gcc specific

#include <ctype.h>  // isspace


#include "pista.h"
#include "pista-internal.h"
#include "ht70.h"

#include <stdlib.h>
#include <stdio.h>
// #include "sax.h"
// #include "sax_parser.h"

static bool verbose = false;

// print n number of string s
static void fpns(int n, char * s) {
	//  char * s = "--";
	//  fprintf(f, "%2d|", n);
	for (int i = 0; i < n; i++) {
		printf("%s", s);
	}
}

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

static unsigned int ms3_asic_crc( const char *str, unsigned char len )
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

static const uint16_t Crc16Table[] =
{
     0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
     0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
     0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
     0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
     0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
     0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
     0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
     0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
     0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
     0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
     0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
     0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
     0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
     0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
     0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
     0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
     0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
     0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
     0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
     0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
     0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
     0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
     0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
     0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
     0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
     0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
     0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
     0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
     0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
     0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
     0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
     0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
}; 

static uint16_t CalculateCrc(uint8_t *Buffer, uint32_t NumberOfBytes, uint16_t CalculatedCrc)
{

   uint8_t  Index;

   while(NumberOfBytes)
   {
      Index = (uint8_t)(((uint8_t)CalculatedCrc ^ *Buffer++)) ;
      CalculatedCrc = ((CalculatedCrc >> 8) & 0x00ff) ^ Crc16Table[Index];
      NumberOfBytes--;
   }

   return CalculatedCrc;
}

static int btoi( char *value ) {
    int rc = -1;
    if( strcmp(value,"On") == 0 ) {
        rc = 1;
    } else if( strcmp(value,"Off") == 0 ) {
        rc = 0;
    }
    return rc;
}

static int atoix10( char *value ) {
    return 10 * atof(value);
}


static void ht70_parse_setting( Ht70__Status *s, char *name, char *value ) {

    // printf("setting: %s=%s\n", name, value );
    if( strcmp(name,"MODE") == 0 ) {
        s->mode = atoi(value);
    } else if( strcmp(name,"MVOLprhi") == 0 ) {
        s->mvolprhi = atoix10(value);
    } else if( strcmp(name,"MVOLprlo") == 0 ) {
        s->mvolprlo = atoix10(value);
    } else if( strcmp(name,"PPAWprhi") == 0 ) {
        s->ppawprhi = atoix10(value);
    } else if( strcmp(name,"PPAWprlo") == 0 ) {
        s->ppawprlo = atoix10(value);
    } else if( strcmp(name,"RATEprhi") == 0 ) {
        s->rateprhi = atoix10(value);
    } else if( strcmp(name,"APINTVL") == 0 ) {
        s->apintvl  = atoix10(value);
    } else if( strcmp(name,"FIO2prhi") == 0 ) {
        s->fio2prhi = btoi(value);
    } else if( strcmp(name,"FIO2prlo") == 0 ) {
        s->fio2prlo = btoi(value);
    } else if( strcmp(name,"ALVOL") == 0 ) {
        s->alvol = atoi(value);
    } else if( strcmp(name,"TVOLprcn") == 0 ) {
        s->tvolprcn = atoix10(value);
    } else if( strcmp(name,"PPAWprcn") == 0 ) {
        s->ppawprcn = atoi(value);
    } else if( strcmp(name,"TI") == 0 ) {
        s->ti = atoix10(value);
    } else if( strcmp(name,"RATEprcn") == 0 ) {
        s->rateprcn = atoi(value);
    } else if( strcmp(name,"TRIG") == 0 ) {
        s->trig = atoix10(value);
    } else if( strcmp(name,"PSprcn") == 0 ) {
        s->psprcn = btoi(value);
    } else if( strcmp(name,"PEEPprcn") == 0 ) {
        s->peepprcn = btoi(value);
    } else if( strcmp(name,"PFLOW") == 0 ) {
        s->pflow = atoi(value);
    } else if( strcmp(name,"FLOWTrig") == 0 ) {
        s->flowtrig = atoix10(value);
    } else if( strcmp(name,"SLOPE") == 0 ) {
        s->slope = atoi(value);
    } else if( strcmp(name,"PSeThresh") == 0 ) {
        s->psethresh = atoi(value);
        // A PERCENT!!!
    } else if( strcmp(name,"PSmaxTI") == 0 ) {
        s->psethresh = atoix10(value);
    } else if( strcmp(name,"WAVE") == 0 ) {
        s->wave = value[0];
    } else if( strcmp(name,"BIASFLOW") == 0 ) {
        s->biasflow = atoi(value);
    } else if( strcmp(name,"NIV") == 0 ) {
        s->niv = btoi(value);
    } else if( strcmp(name,"NMpr") == 0 ) {
        s->nmpr = value[0];
        // vent mode? string
    } else if( strcmp(name,"PCVMODE") == 0 ) {
        s->pcvmode = value[0];
        // vent mode? string
    } else {
        fprintf( stderr, "UNKNOWN SETTING KEY: %s=%s\n", name, value );
    }

    return;
}

static void ht70_parse_measurement( Ht70__Breath *m, char *name, char *value ) {

    if( strcmp(name,"TVOL") == 0 ) {
        m->mvol = atoi(value);
    } else if( strcmp(name,"MVOL") == 0 ) {
        m->mvol = atoix10(value);
    } else if( strcmp(name,"RATE") == 0 ) {
        m->rate = atoix10(value);
    } else if( strcmp(name,"PPAW") == 0 ) {
        m->ppaw = atoix10(value);
    } else if( strcmp(name,"MAP") == 0 ) {
        m->map  = atoix10(value);
    } else if( strcmp(name,"PEEP") == 0 ) {
        m->peep = atoix10(value);
    } else if( strcmp(name,"FIO2") == 0 ) {
        m->fio2 = atoix10(value);
    } else if( strcmp(name,"PFLOW") == 0 ) {
        m->pflow = btoi(value);
    } else if( strcmp(name,"I2E") == 0 ) {
        m->i2e   = btoi(value);
    } else if( strcmp(name,"O2CylTime") == 0 ) {
        m->o2cyltime = atoi(value);
    } else if( strcmp(name,"BATTTIME") == 0 ) {
        m->battime= atoix10(value);
    } else {
        fprintf( stderr, "UNKNOWN MEASUREMENT KEY: %s=%s\n", name, value );
    }
}

static void ht70_parse_alarms( Ht70__Alarms *a, char *name, char *value ) {
    if( strcmp(name,"SYSFAULT") == 0 ) {
        a->sysfault = atoix10(value);
    } else if( strcmp(name,"BATTFail") == 0 ) {
        a->battfail = atoi(value);
    } else if( strcmp(name,"PWRFail") == 0 ) {
        a->pwrfail = atoix10(value);
    } else if( strcmp(name,"OCCLUSIONsust") == 0 ) {
        a->occlusion = btoi(value);
    } else if( strcmp(name,"PROX") == 0 ) {
        a->prox = btoi(value);
    } else if( strcmp(name,"PPAWlo") == 0 ) {
        a->ppawlo = atoi(value);
    } else if( strcmp(name,"OCCLUSION") == 0 ) {
        a->occlusion = atoix10(value);
    } else if( strcmp(name,"APNEA") == 0 ) {
        a->apnea = atoi(value);
    } else if( strcmp(name,"MVOLlo") == 0 ) {
        a->mvollo = atoi(value);
    } else if( strcmp(name,"MVOLhi") == 0 ) {
        a->mvolhi = atoi(value);
    } else if( strcmp(name,"PCVNR") == 0 ) {
        a->pcvnr= atoi(value);
    } else if( strcmp(name,"FIO2lo") == 0 ) {
        a->fio2lo = atoi(value);
    } else if( strcmp(name,"PEEPlo") == 0 ) {
        a->peeplo = atoi(value);
    } else if( strcmp(name,"PEEPhi") == 0 ) {
        a->peephi = atoi(value);
    } else if( strcmp(name,"PPAWhi") == 0 ) {
        a->ppawhi = atoi(value);
    } else if( strcmp(name,"BATTlo") == 0 ) {
        a->battlo= atoi(value);
    } else if( strcmp(name,"BATTon") == 0 ) {
        a->batton= atoi(value);
    } else if( strcmp(name,"ExtBATTlo") == 0 ) {
        a->extbattlo= atoi(value);
    } else if( strcmp(name,"BATTERY") == 0 ) {
        a->battery= atoi(value);
    } else if( strcmp(name,"VTEhi") == 0 ) {
        a->vtehi= atoi(value);
    } else if( strcmp(name,"FIO2hi") == 0 ) {
        a->fio2hi= atoi(value);
    } else if( strcmp(name,"RATEhi") == 0 ) {
        a->ratehi= atoi(value);
    } else if( strcmp(name,"FIO2Sensor") == 0 ) {
        a->fio2sensor= atoi(value);
    } else if( strcmp(name,"BACKUP") == 0 ) {
        a->backup = atoi(value);
    } else if( strcmp(name,"NOPWR") == 0 ) {
        a->nopwr= atoi(value);
    } else {
        fprintf( stderr, "UNKNOWN ALARM KEY: %s=%s\n", name, value );
    }

    return;
}

static void ht70_parse_wave( struct HT70_context *me, int *dest, Ht70__Sensors *a, char *name, char *value ) {
    if( strcmp(name,"Wave") == 0 ) {
        int n = ht70_b64decode(dest, me->charbuf, me->charbuf_pos );

		if( verbose ) {
        	printf("%s WAVE:", me->wave_name );
        	for(int i=0; i < n; i++) {
            	printf(" %d", dest[i] );
        	}
        	printf("\n");
		}
    } else if( strcmp(name,"Points") == 0 ) {
    } else if( strcmp(name,"PointsBytes") == 0 ) {
    } else if( strcmp(name,"Min") == 0 ) {
    } else if( strcmp(name,"Max") == 0 ) {
    } else if( strcmp(name,"Offset") == 0 ) {
    } else if( strcmp(name,"Gain") == 0 ) {
    } else if( strcmp(name,"Hz") == 0 ) {
    } else {
        fprintf( stderr, "UNKNOWN WAVE KEY: %s=%s\n", name, value );
    }
}

/*
 * public function
 */
int ht70_verify_pkt( char *buf, int len ) {

    if( len < 9 ) {
        return PISTA_ERR_NA;
    }

    // FIXME: this shortcuts the CRC check for probe packets, which is failing
    // for unknown reasons
	if( buf[8] == '\r' ) {
        return PISTA_OK;
	}

	int crc = ms3_asic_crc( buf, len - 5 );
    int pkt_crc = 999; // ahextoint( buf + (len-5), 4 );
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


static void chars( void *userData, const char * chars, int len) {
    struct HT70_context *me = (struct HT70_context *)userData;

    if( me->depth <= 1 ) {
        return;
    }

    while( len > 0 && isspace(*chars) ) {
        len--;
        chars++;
    }

    if( len == 0 ) {
        return;
    }

    strncpy( me->charbuf + me->charbuf_pos, chars, len);
    me->charbuf_pos += len;

}

static void ns_start(void *userData, const XML_Char * name, const XML_Char *attrs) {
    struct HT70_context *me = (struct HT70_context *)userData;

    printf("GOT NS START!!! at %d\n", me->depth);
}

static void ns_end(void *userData, const XML_Char * name) {
    struct HT70_context *me = (struct HT70_context *)userData;

    printf("GOT NS END!!! at %d\n", me->depth);
}

static void start_elem(void *userData, const XML_Char * name, const XML_Char **attrs) {
    struct HT70_context *me = (struct HT70_context *)userData;

    bool show_it = false;

    // printf("DEPTH=%d\n", me->depth);
    me->stack[me->depth] = strdup(name);
	me->depth++;
    // printf("INCR DEPTH=%d %s\n", me->depth, name );

    strcpy( me->element_name, "<none>" );

    if( strcmp(name, "s") == 0 ) {
        me->charbuf_pos = 0;
    } else if ( strcmp( name, "m") == 0 ) {
        me->charbuf_pos = 0;
    } else if ( strcmp( name, "a") == 0 ) {
        me->charbuf_pos = 0;
    } else if ( strcmp( name, "xml") == 0 ) {
        // ignore
    } else if ( strcmp( name, "device") == 0 ) {
        // ignore
    } else if ( strcmp( name, "status") == 0 ) {
        me->charbuf_pos = 0;
        // ignore
    } else if ( strcmp( name, "device") == 0 ) {
        // ignore
    } else if ( strcmp( name, "cpc") == 0 ) {
        // ignore
    } else if ( strcmp( name, "crc") == 0 ) {
        me->charbuf_pos = 0;
    } else if ( strcmp( name, "Len") == 0 ) {
        me->charbuf_pos = 0;
    } else if ( strcmp( name, "settings") == 0 ) {
    } else if ( strcmp( name, "measurements") == 0 ) {
        me->w.pawwave[0] = '\0';
        me->w.flowwave[0] = '\0';
    } else if ( strcmp( name, "alarms") == 0 ) {
    } else if ( strcmp( name, "mg") == 0 ) {
    } else {
	    // WLB 17MAY17 fpns(me->depth, "  ");
	    // WLB 17MAY17 printf("<%s", name);
        // char ch_context = name[0];
        show_it = true;
    }
    while( *attrs ) {
        const char *key = *attrs;
        attrs++;
        const char *value = *attrs;
        attrs++;

	    if( show_it ) printf(" %s=\"%s\"\n", key, value);
        if( strcmp( "name", key) == 0 ) {
            strncpy( me->element_name, value, sizeof(me->element_name) );
        }
	}
    if ( strcmp( name, "mg") == 0 ) { strncpy(me->wave_name, me->element_name, sizeof( me->wave_name) ); }
	if( show_it) printf(">\n");
}

static void end_elem(void *userData, const XML_Char *name) {
    struct HT70_context *me = (struct HT70_context *)userData;

    if( me->depth < 2 ) {
        // nothing to process
        // can also be triggered erroneously by a message fragment
        return; 
    }
    // char *top = me->stack[me->depth-1];
    char *prev = me->stack[me->depth-2];

    me->charbuf[me->charbuf_pos] = '\0';
    if( prev == NULL ) {
        fprintf(stderr,"PREV=NULL in ht70...should not be possible.\n");
    } else if( strcmp(name,"s") == 0 ) {
        ht70_parse_setting( &me->s, me->element_name, me->charbuf );
    } else if( strcmp(name,"m") == 0 ) {
        if( strcmp(prev,"mg") == 0 ) {
            int *dest = NULL;
            if( strcmp( me->element_name, "Wave") == 0 ) {
                // printf("ELEMENT NAME=%s.%s\n", me->element_name, me->wave_name );
                if( strcmp( me->wave_name, "FLOWwave" ) == 0  ){
                    dest = me->w.flowwave;
                } else if( strcmp( me->wave_name, "PAWwave" ) == 0 ) {
                    dest = me->w.pawwave;
                } else {
                    printf("ht70: unknown wave %s\n", me->wave_name );
                }
            }
            if( dest != NULL ) {
                ht70_parse_wave( me, dest, NULL, me->element_name, me->charbuf );
                me->fire_waveform = true;
            }
        } else {
            ht70_parse_measurement( &me->m, me->element_name, me->charbuf );
        }
    } else if( strcmp(name,"a") == 0 ) {
        ht70_parse_alarms( &me->a, me->element_name, me->charbuf );
    } else if( strcmp( name, "settings" ) == 0 ) {
        me->fire_status = true;

    } else if( strcmp( name, "measurements" ) == 0 ) {
        me->fire_measurement = true;
    } else if( strcmp( name, "alarms" ) == 0 ) {
        me->fire_alarm = true;
    } else if( strcmp( name, "device" ) == 0 ) {
        // ignore
    } else if( strcmp( name, "cpc" ) == 0 ) {
        // end of document...restart the parser!
        me->reset = true;
    } else if( strcmp( name, "crc" ) == 0 ) {
        // ignore
    } else if( strcmp( name, "Len" ) == 0 ) {
        // ignore
    } else if( strcmp( name, "status" ) == 0 ) {
        // ignore
    } else {
	    // WLB 17MAY17 fpns(me->depth, "  ");
	    // WLB 17MAY17 printf("</%s>\n", name);
    }

	me->depth--;

    if(me->stack[me->depth] == NULL ) {
        fprintf(stderr, "STACK NAME IS NULL at depth=%d\n", me->depth );
    } else {
        free(me->stack[me->depth]);
        me->stack[me->depth] = NULL;
    }

    me->charbuf_pos = 0;
}

//static void begin() {
	//puts("Begin XML\n");
//}

//static void end() {
	//puts("\nEnd XML\n");
//}

//static void proc_inst(char *name, char *data) {
	//fpns(me->depth, "  ");
	//printf("<?%s %s?>\n", name, data);
//}

//static void error(int errnum) {
	//fprintf(stderr, "Error");
//}

void ht70_install_parser(struct HT70_context *me) {

	// SAX_parser *p = SAX_init(stdin);
    // me->p = p;
    // 
	// reg_characters_handler(p, chars);
	// reg_start_document_handler(p, begin);
	// reg_end_document_handler(p, end);
	// reg_start_element_handler(p, start_elem);
	// reg_end_element_handler(p, end_elem);
	// reg_pi_handler(p, proc_inst);
	// reg_error_handler(p, error);
    //
    if( me->p != NULL ) {
        XML_ParserFree( me->p );
    }

    XML_Parser p =  XML_ParserCreate("US-ASCII");
    // XML_SetCdataSectionHandler( p, chars );
    XML_SetElementHandler( p, start_elem, end_elem);
    XML_SetCharacterDataHandler( p, chars );
    XML_SetUserData( p, me );
    XML_SetNamespaceDeclHandler(p, ns_start, ns_end);
	// XML_SetNamespaceDeclHandler( p, ns_elem);

    me->p = p;
    me->fire_alarm = false;
    me->fire_measurement = false;
    me->fire_status = false;
    me->reset = false;
}

#if( !defined(HAVE_MEMMEM) )
void *memmem(const void *haystack_start, size_t haystack_len, const void *needle_start, size_t needle_len)
{

    const unsigned char *haystack = (const unsigned char *) haystack_start;
    const unsigned char *needle = (const unsigned char *) needle_start;
    const unsigned char *h = NULL;
    const unsigned char *n = NULL;
    size_t x = needle_len;

    /* The first occurrence of the empty string is deemed to occur at
    the beginning of the string.  */
    if (needle_len == 0)
        return (void *) haystack_start;

    /* Sanity check, otherwise the loop might search through the whole
        memory.  */
     if (haystack_len < needle_len)
       return NULL;

    for (; *haystack && haystack_len--; haystack++) {

        x = needle_len;
        n = needle;
        h = haystack;

        if (haystack_len < needle_len)
            break;

        if ((*haystack != *needle) || ( *haystack + needle_len != *needle + needle_len))
            continue;

        for (; x ; h++ , n++) {
            x--;

            if (*h != *n) 
                break;

           if (x == 0)
            return (void *)haystack;
        }
    }

    return NULL;
}
#endif

/*
 * public function
 */
int ht70_process_pkt( void *userData, const char *buf, int len ) {
    struct HT70_context *me = (struct HT70_context *)userData;


	int code;
	do {
		// memmem is gnu specific
		char *found = memmem( buf, len, "?>", 2 );
		int n = ( found == NULL ) ? len : ( found - buf ) + 2;

		// printf( "  parse: (%d)%s", n, buf);
    	code = XML_Parse(me->p, buf, n, XML_FALSE); 
    	// 17MAY17 WLB if ( code == XML_STATUS_ERROR) {
        // 17MAY17 WLB     printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(me->p)));
    	// 17MAY17 WLB }

		if( found != NULL ) {
    		ht70_install_parser( me );
		}

		buf += n;
		len -= n;
	} while ( len > 0 );

    return code;
}


/*
int main(int argc, char **argv) {

    const char * input_name = "sample-1.xml";
    char buf[256];
    int n;

    FILE *fp = fopen( input_name , "r");
    if( fp == NULL ) {
        fprintf(stderr,"Could not find input file: %s\n", input_name );
    }

	me = PISTA_MALLOC( sizeof(struct HT70_context) );
    ht70_install_parser( me );

    while( (n = fread( buf, 1, 256, fp )) > 0 ) {
        ht70_process_pkt( me, buf, n );
    }

	return EXIT_SUCCESS;
}
*/

