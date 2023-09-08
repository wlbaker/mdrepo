#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv ) {

    char *key = "RXc0_X00";

        int code1 = strtol( "C0", NULL, 16 );
        int code2 = strtol( "c0", NULL, 16 );
        int code3 = strtol( "c0_", NULL, 16 );
        int code4 = strtol( key+2, NULL, 16 );

        printf("%2.2x %2.2x %2.2x %2.2x\n", code1, code2, code3, code4 );
}
