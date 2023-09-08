#include <stdio.h>
#include <string.h>

#include "medsys3.h"

int main( int argc, char *argv[] ) {

	char buf[32];

	const char *test_str[] = {
		"ABCDEFG",
		"12345",
		"\001",
		"\001cA QX00_X02!",
		"\001cA ",
		"\001d@$RX03_X02=15.67!",
		NULL
	};

	unsigned int test_crc[] = {
		0x82a8,
		0x44bf,
		0x1e0e,
		0xb064,
		0x8b0f,
		0xdb99,
		0x0,
	};

	int i = 0;
	while( test_str[i] != NULL ) {
		const char *str = test_str[i];
		const unsigned int expected = test_crc[i];
		int len = strlen(str);
		unsigned int crc = ms3_asic_crc( str, strlen(str) );

		char * message = (crc == expected) ? "pass" : "FAIL";

		printf("TEST %d: %s[%d] --> 0x%4.4x, expected 0x%4.4x: %s\n", (i+1), str, len, crc, expected, message );
		i++;

	}

	ms3_dump_pkt( " demo-4", test_str[3], strlen(test_str[3]) );
	ms3_dump_pkt( " demo-5", test_str[4], strlen(test_str[4]) );
	ms3_build_connect( buf, 32 );
	ms3_dump_pkt( "connect", buf, strlen(buf) );
}

