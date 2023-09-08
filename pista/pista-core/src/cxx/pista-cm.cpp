
#include <stdio.h>
#include "pista-cl.h"

using namespace pistax;

PistaCommHandler::PistaCommHandler() {

// printf("PistaCommHandler:: allocted %lx\n", (unsigned long) this );
}

PistaCommHandler:: ~PistaCommHandler() { 
    // printf("PistaCommHandler::~PistaCommHandler(%lx)\n", (unsigned long)this); 
}
int PistaCommHandler::open( )  { printf( "PistaCommHandler::open\n"); return 0; }
int PistaCommHandler::config(int baud, int datab, int stopb, char parity ) { printf( "PistaCommHandler::config\n"); return 0; }
int PistaCommHandler::write( const char data[], size_t len) { printf( "PistaCommHandler::write()\n"); return len; }
int PistaCommHandler::close() { printf( "PistaCommHandler::close\n"); return 0; }

