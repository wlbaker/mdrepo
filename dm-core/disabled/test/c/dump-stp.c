
// 
// od --endian=big -f BAMC\ 2719.003.stp 
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool verbose = false;

int read_int( FILE *fp) {
	int val;

	unsigned char *buf = (unsigned char *)&val;
	int nch = fread( &val, 4, 1, fp );
	if( nch < 1 ) {
		return -1;
	}

	unsigned char c;
	c = buf[3];
	buf[3] = buf[0];
	buf[0] = c;
	c = buf[2];
	buf[2] = buf[1];
	buf[1] = c;

	return val;
}

int read_string( FILE *fp, char *buf) {
	int len = read_int( fp );
	int rt = len;
	while( len-- > 0 ) {
		*(buf++) = getc(fp);
	}
	
	*buf = 0;

	return rt;
}

float read_float( FILE *fp) {
	float f;

	unsigned char *buf = (unsigned char *)&f;
	int nch = fread( &f, 4, 1, fp );
	if( nch < 1 ) {
		return -1;
	}

	unsigned char c;
	c = buf[3];
	buf[3] = buf[0];
	buf[0] = c;
	c = buf[2];
	buf[2] = buf[1];
	buf[1] = c;

	return f;
}


double read_double( FILE *fp) {
	double f;

	unsigned char *low = (unsigned char *)&f;
	int nch = fread( &f, 8, 1, fp );
	if( nch < 1 ) {
		return -1;
	}

	unsigned char c;

	c = low[7];
	low[7] = low[0];
	low[0] = c;

	c = low[6];
	low[6] = low[1];
	low[1] = c;

	c = low[5];
	low[5] = low[2];
	low[2] = c;

	c = low[4];
	low[4] = low[3];
	low[3] = c;

	return f;
}

void dump_block_to_array( FILE *fp, int count, float *farr ) {
	for( int i = 0; i < count; i++) {
		float f = read_float( fp );
		*(farr++) = f;
		printf(" %4.2f", f );

		if( i%16 == 15 ) printf("\n");
	}
}

void dump_block( FILE *fp, int count ) {
	for( int i = 0; i < count; i++) {
		float f = read_float( fp );
		printf(" %4.2f", f );
		if( i%16 == 15 ) printf("\n");
	}
}

void dump_block_double( FILE *fp, int count ) {
	for( int i = 0; i < count; i++) {
		double f = read_double( fp );
		printf(" %4.2f", f );
		if( i%16 == 15 ) printf("\n");
	}
}

void dump_int4_to_array( FILE *fp, int count, int *arr ) {
	for( int i = 0; i < count; i++) {
		int val = read_int( fp );
		*(arr++) = val;
		if( val == -1 ) {
			return;
		}
		printf(" %4.4d", val );
		if( i%8 == 7 ) printf("\n");
	}
}

void dump_int4( FILE *fp, int count ) {
	for( int i = 0; i < count; i++) {
		int val = read_int( fp );
		if( val == -1 ) {
			return;
		}
		printf(" %4.4d", val );
		if( i%8 == 7 ) printf("\n");
	}
}

void dump_colors_102( FILE *fp ) {
	int seq = 1;

	int sz = read_int( fp );
	if( sz != 32 ) {
			printf("EXPECTING INT ARRAY SZ 32 != %d\n", sz);
	}
	for( int i = 0; i < sz ; i++) {
		int c0 = getc( fp );
		if( c0 == -1 ) {
			return;
		}
		if( c0 != 0 ) {
			printf("ERROR IN COLOR [c0=%d] ", c0);
		}
		int c1 = getc( fp );
		int c2 = getc( fp );
		int c3 = getc( fp );

		printf("%d: rgb=%2.2d-%2.2d-%2.2d\n", seq++, c1, c2, c3 );
	}
}

int dump_ascii( FILE *fp, int count, unsigned char *buf, bool variable_length ) {

	int consec_zero = 0;

	memset( buf, 255, 1024 );
	int pos = 0;
	for( ; pos < count; pos++) {
		int ch = getc( fp );
		if( ch == -1 ) {
			printf("END OF FILE [%d/%d]\n", pos, count);
			break;
		}
		*(buf++) = ch;
		if( ch < ' ' || ch > '~' ) {
			printf("[%2.2x] ", ch );
		} else {
			printf("%c    ", ch );
		}
		if( pos%16 == 15 ) printf("\n");
		
		if( ch == 0 && variable_length ) {
			consec_zero++;
		} else {
			consec_zero=0;
		}

		if( consec_zero == 4 ) {
			break;
		}
	}
	printf("\n");

	return pos;
}

int parse_accessories( unsigned char *buf, bool with_seq ) {

	int seq = 0;
	do {
		int nch = 0;

		// 4 bytes, big endian
		for( int i = 0; i < 4; i++ ) {
			if( *buf == 255 ) break;
			nch = 256 * nch + *buf;
			buf++;
		}

		if( nch == 0 ) {
			printf("empty accessories\n");
			break;
		}

	    	if( with_seq ) {
			printf("%2.2d ", ++seq);
		}

		printf("string[%d]: ", nch);
		for( int i = 0; i < nch; i++ ) {
			printf("%c", *buf);
			buf++;
		}
		printf("\n");

		int port = *(buf++);
		printf(" PORT: [%d]\n", port );
		int opt = 0;  // only used for accessories
		int nopt = 0;  // only used for accessories

		// 4 bytes, big endian...number of options
		for( int i = 0; i < 4; i++ ) {
			nopt = 256 * nopt + *buf;
			buf++;
		}

		for( int i = 0; i < nopt; i++ ) {
		    int opt_val = 0;
		    for( int i = 0; i < 4; i++ ) {
			opt_val = 256 * opt_val + *buf;
			buf++;
		    }
		    printf( "OPT %d/%d: %d\n", opt++, nopt, opt_val );
		}

		// 4 bytes, big endian--label string
		nch = 0;
		for( int i = 0; i < 4; i++ ) {
			nch = 256 * nch + *buf;
			buf++;
		}

		printf("  LABEL [%d]: ", nch);
		for( int i = 0; i < nch; i++ ) {
			printf("%c", *buf);
			buf++;
		}
		printf("\n");


	} while (1);


	return seq;
}

int parse_strings( unsigned char *buf, bool with_seq ) {

	int seq = 0;
	do {
		int nch = 0;

		// 4 bytes, big endian
		for( int i = 0; i < 4; i++ ) {
			if( *buf == 255 ) break;
			nch = 256 * nch + *buf;
			buf++;
		}
		if( nch == 0 ) {
			break;
		}

	    if( with_seq ) {
			printf("%2.2d ", ++seq);
		}

		printf("string[%d]: ", nch);
		for( int i = 0; i < nch; i++ ) {
			printf("%c", *buf);
			buf++;
		}
		printf("\n");

	} while (1);


	return seq;
}

void decode_01( FILE *fp ) {
	unsigned char buf[1024];
	int sz;

	printf("\n%4.4x Signal??\n", ftell(fp) );
	dump_block( fp, 16 );

	printf("\n%4.4x unitHIGH\n", ftell(fp) );
	dump_block( fp, 16 );

	printf("\n%4.4x unitLOW\n", ftell(fp) );
	dump_block( fp, 16 );
	printf("\n%4.4x vHIGH\n", ftell(fp) );
	dump_block( fp, 16 );

	printf("\n%4.4x vLOW\n", ftell(fp) );
	dump_block( fp, 16 );

	printf("\n%4.4x Precision???\n", ftell(fp) );
	dump_block( fp, 16 );

	printf("\n%4.4x DEVICE\n", ftell(fp) );
	float fdevinfo[9];
	dump_block_to_array( fp, 9, fdevinfo );
	printf( "\n" );
	printf( "* DEVICE ID: %f\n", fdevinfo[0] );
	printf( "* Sample Rate: %f\n", fdevinfo[1] );
	printf( "* ?Source Data: %f\n", fdevinfo[2] );
	printf( "* ?Accessory: %f\n", fdevinfo[3] );
	printf( "* ?Config/NRSE: %f\n", fdevinfo[4] );
	printf( "* Seq No: %f\n", fdevinfo[5] );
	printf( "* Data Set Size(sec): %f\n", fdevinfo[6] );
	printf( "* Timed Save (sec): %f\n", fdevinfo[7] );
	printf( "* Auto Save (sec): %f\n", fdevinfo[8] );
	// printf( "* Marker Number: %f\n", fdevinfo[9] );

	printf("\n%4.4x Channel??\n", ftell(fp) );
	dump_block( fp, 16);

	printf("\n%4.4x X0-Color table?\n", ftell(fp) );
	sz = dump_ascii( fp, 20 * 4, buf, false  );
	printf( "--> sz = %d\n", sz );


	printf("\n%4.4x COLOR ASSIGN\n", ftell(fp) );
	dump_block( fp, 19 );

	printf("\n%4.4x B1\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B2\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B3\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B4\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B5\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B6\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B7\n", ftell(fp) );
	dump_block( fp, 32 );

	printf("\n%4.4x B8\n", ftell(fp) );
	dump_block( fp, 16 );

	int h3 = read_int( fp );
	printf("\n**** h3=%d\n", h3 );

	printf("\n%4.4x LABELS\n", ftell(fp) );
	for( int i = 0; i < 49; i++ ) {
		read_string( fp, buf);
		printf("%2.2d ", i+1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n" );
		} else {
			printf("%s\n", buf );
		}
	}

	printf("\n%4.4x CONFIG-BB\n", ftell(fp));
	for( int i = 0; i < 27; i++ ) {
		read_string( fp, buf);
		printf("%2.2d ", i+1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n" );
		} else {
			printf("%s\n", buf );
		}
	}

	printf("\n%4.4x LABEL/GRAPH\n", ftell(fp) );
	int n_strings = 0;
	for( n_strings = 0; n_strings < 124; n_strings++ ) {
		read_string( fp, buf);
		printf("%2.2d ", n_strings + 1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n");
		} else {
			printf("%s\n", buf );
		}
	}

	//printf("\n%4.4x BINARY2-AA\n", ftell(fp) );
	//dump_ascii( fp, 21*16+6, buf, false );
	//parse_strings( buf, false );

	int h5 = read_int( fp );
	printf("\n**** h5=0x%x == 0xb0\n", h5 );

	printf("\n%4.4x BINARY3-AA\n", ftell(fp) );
	dump_ascii( fp, 16*11, buf, false );

	int h6 = read_int( fp );
	printf("\n**** h6=0x%x == 0x18\n", h6 );
	getc(fp); // FIXME!!!

	printf("\n%4.4x COMS-AA\n", ftell(fp) );
	dump_ascii( fp, 21*40, buf, false );

}

char *layout_text[] = {
	"1 - One Graph",
	"2 - Two Bottom",
	"3 - Two Equal",
	"4 - Two Top",
	"5 - Three Bottom",
	"6 - Three Equal",
	"7 - Three Top",
	"8 - Four Graphs",
	"9 - Custom",
};

char *filter_text[] = {
	"None",
	"Butterworth",
	"Chebyshev",
	"Elliptic",
	"Bessel",
	"Running Average"
};

char *format_text[] = {
	"Scaled Ascii (TXT)",
	"Scaled Binary (SGL)",
	"Unscaled Binary (I16)",
	"Voltage Ascii (TXT)",
	"Voltage Binary (SGL)"
};

char *limit_text[] = {
	"+/- 10.0",
	"+/- 5.0",
	"+/- 2.5",
	"+/- 2.0",
	"+/- 1.0",
	"+/- 0.5",
	"+/- 0.25",
	"+/- 0.20",
	"+/- 0.10",
	"+/- 0.05"
};

void decode_102( FILE *fp ) {
	unsigned char buf[4*1024];
	int sz;

	int h3 = read_int( fp );
	printf("\n**** h3=%d\n", h3 );

	printf("\n%4.4x Units High\n", ftell(fp) );
	dump_block_double( fp, 16 );

	printf("\n%4.4x Units Low\n", ftell(fp) );
	dump_block_double( fp, 16 );

	printf("\n%4.4x Volts High\n", ftell(fp) );
	dump_block_double( fp, 16 );

	printf("\n%4.4x Volts Low\n", ftell(fp) );
	dump_block_double( fp, 16 );

	
	printf("\n%4.4x SETTINGS\n", ftell(fp) );
	double sample_rate = read_double ( fp );
	double two = read_double ( fp );
	double unk = read_double ( fp );
	printf(" * sample rate: %f\n", sample_rate );
	printf(" *         two: %f\n", two );
	printf(" *         unk: %f\n", unk );

	printf("\n%4.4x Band (fh)\n", ftell(fp) );
	dump_block_double( fp, 16 );

	printf("\n%4.4x Cutoff (fh)\n", ftell(fp) );
	dump_block_double( fp, 16 );
	printf("\n%4.4x GRAPH RANGES\n", ftell(fp) );
	dump_block_double( fp, 8 );
	printf("\n%4.4x OTHER DOUBLES\n", ftell(fp) );
	dump_block_double( fp, 120 - 16 - 8 - 3 );

	int h4 = read_int( fp );
	printf("\n**** h4=%d\n", h4 );

	printf("\n%4.4x SIGNAL LABELS\n", ftell(fp) );
	for( int i = 0; i < 49; i++ ) {
		read_string( fp, buf);
		printf("%2.2d ", i+1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n" );
		} else {
			printf("%s\n", buf );
		}
	}

	printf("\n%4.4x CONFIG-AA\n", ftell(fp));
	for( int i = 0; i < 8; i++ ) {
		read_string( fp, buf);
		printf("%2.2d ", i+1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n" );
		} else {
			printf("%s\n", buf );
		}
	}

	printf("\n%4.4x SIGS TO RECORD\n", ftell(fp));
	for( int i = 0; i < 28; i++ ) {
		read_string( fp, buf);
		printf("%2.2d ", i+1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n" );
		} else {
			printf("%s\n", buf );
		}
	}


	printf("\n%4.4x SIGS TO GRAPH\n", ftell(fp) );
	for( int n_strings = 0; n_strings < 16; n_strings++ ) {
		read_string( fp, buf);
		printf("%2.2d ", n_strings + 1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n");
		} else {
			printf("%s\n", buf );
		}
	}

	printf("\n%4.4x HR SOURCES AND VITALS MESSAGES\n", ftell(fp) );
	for( int n_strings = 0; n_strings < 16; n_strings++ ) {
		read_string( fp, buf);
		printf("%2.2d ", n_strings + 1);
		if( strlen(buf) == 0) {
			printf("EMPTY\n");
		} else {
			printf("%s\n", buf );
		}
	}


	printf("\n%4.4x BINARY2-BB\n", ftell(fp) );
	dump_ascii( fp, 21*16, buf, false );
	parse_strings( buf, false );

	int timed_save = getc(fp);
	int auto_save = getc(fp);
	int continuous_save = getc(fp);
	int enable_marker = getc(fp);
	int zero0 = getc(fp);
	int zero1 = getc(fp);

	printf("\nSave/File info\n");
	printf("Timed Save: %d\n", timed_save );
	printf("Auto Save: %d\n", auto_save );
	printf("Continuous Save: %d\n", continuous_save );
	printf("Enable Marker: %d\n", enable_marker );
	printf("z0,z1: %d,%d\n", zero0, zero1 );


	int h5 = read_int( fp );
	printf("\n**** h5=%d\n", h5 );

	printf("\n%4.4x BINARY3xx\n", ftell(fp) );
	dump_int4( fp, 10 );
	printf("\n%4.4x UNK1\n", ftell(fp) );
	dump_int4( fp, 1 );
	printf("\n%4.4x CHANNELS\n", ftell(fp) );
	dump_int4( fp, 16 );
	printf("\n%4.4x LIMITS\n", ftell(fp) );
	int limits[16];
	dump_int4_to_array( fp, 16, limits );
	for( int i = 0 ; i<16;i++) {
		printf(" * LIM SIG%d: %s\n", i, limit_text[limits[i]] );
	}

	printf("\n%4.4x DEVINFO3\n", ftell(fp) );
	int devinfo[9] = { 0 };
	dump_int4_to_array( fp, 9, devinfo);
	printf( "\n");
	printf( "* DEVICE ID: %d\n", devinfo[0] );
	printf( "* NRSE/RSE: %d\n", devinfo[2] );
	printf( "* Recording Mode: %s\n", format_text[ devinfo[3] ] );
	printf( "* Seq No: %d\n", devinfo[4] );
	printf( "* Data Set Size(sec): %d\n", devinfo[5] );
	printf( "* Timed Save (sec): %d\n", devinfo[6] );
	printf( "* Auto Save (sec): %d\n", devinfo[7] );
	printf( "* Marker Number: %d\n", devinfo[8] );
	// printf( "* Opt 1: %d\n", devinfo[9] );
	// printf( "* Opt 2: %d\n", devinfo[10] );
	// printf( "* Opt 3: %d\n", devinfo[11] );
	// printf( "* Opt 4: %d\n", devinfo[12] );

	printf("\n%4.4x Filter Type\n", ftell(fp) );
	int filter[16] = { 0 };
	dump_int4_to_array( fp, 16, filter );
	printf( "\n");
	for( int i = 0; i < 16; i++ ) {
		printf( "* FILTER [%d]: %s\n", i, filter_text[ filter[i] ] );
	}

	printf("\n%4.4x Other?\n", ftell(fp) );
	int other[48 + 7] = { 0 };
	dump_int4_to_array( fp, 48 - 3 + 7, other );


	printf("\n%4.4x BINARY3b\n", ftell(fp) );
	int arr[92] = { 0 };
	dump_int4_to_array( fp, 10*8 + 12, arr );
	printf( "\n");
	printf( "* GRAPH LAYOUT/STYLE: %d\n", layout_text[ arr[1] ] );

	printf("\n%4.4x COLOR MAP\n", ftell(fp) );
	dump_colors_102( fp );

	printf("\n%4.4x ACCESSORIES\n", ftell(fp) );
	int acc_code = read_int( fp );
	printf("\n**** acc=%d\n", acc_code );
	if( acc_code != 16 ) {
		printf("\nERR ACC CODE=%d != 16\n", acc_code );
	}
	dump_ascii( fp, 4*100, buf, false );
	parse_accessories( buf, false );

	printf("\n");
}

int main( int argc, char *argv[] ) {

	int h0, h1;
	float f;

	FILE *fp = stdin;
	h0 = read_int( fp );
	h1 = read_int( fp );

	char tag[32] = { 0 };

	if( h0 == 1 ) {
		printf("DECODE %2.2d.%2.2d\n", h0, h1 );
		decode_01( fp );
	} else {
		rewind(fp);
		for( int count = 0;count < sizeof(tag)-1; count++ ) {
			int ch = getc( fp );
			if( ch  == '\r' ) {
				ch = 0;
			}
			if( ch  == '\n' ) {
				break;
			}
			tag[count] = ch;
		}
		if( strcmp( tag, "DAQmx Setup 102") == 0 ) {
			printf("DECODE 102: %s\n", tag );
			decode_102( fp );
		} else {
			printf("Unknown setup tag: %s\n", tag );
		}
	}


}

