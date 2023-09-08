
#include <stdio.h>
#include <stdlib.h>
#include <visa.h>

#define READ_BUFFER_SIZE 1000

static ViJobId job;
static unsigned char data[READ_BUFFER_SIZE];
static ViAddr uhandle;
static ViStatus status, StatusSession;
static ViSession inst, Sessionparam;
static ViEventType EventTypeparam;
static ViAddr Addressparam;
static ViUInt32 BytesToWrite;
static ViSession defaultRM;
static ViUInt32 rcount, RdCount;

static volatile ViBoolean stopflag = VI_FALSE;

void findRsrc( ViSession sess, char *rsrc, int mode ) {

	ViUInt32 retnCnt;
	ViChar   desc[VI_FIND_BUFLEN];  // ASSUMING so
	ViFindList list;
	ViPFindList plist = NULL;

	//if( mode == 2 ) {
		plist = &list;
	//}

	// attr = viGetAttribute( sess, FIND_RSRC_MODE, 0 );  // save current value
	// viSetAttribute( sess, FIND_RSRC_MODE, mode );

	status = viFindRsrc( sess, rsrc, plist, &retnCnt, desc );
	do {
		if( status == VI_ERROR_MACHINE_NAVAIL ) {
			// nothing found
			viClose( list );

			break;
		} else if( status == VI_SUCCESS ) {
			for( int i = 0; i < retnCnt; i++ ) {
				ViSession devSess;
				ViChar    devName[64];
				long code;

				printf( " found device: %s\n", desc );
				viOpen( sess, desc, VI_NULL, VI_NULL, &devSess );

				viGetAttribute( devSess, VI_ATTR_MODEL_NAME, devName );
				printf( "   --> name: %s\n", devName );
				viGetAttribute( devSess, VI_ATTR_MODEL_CODE, &code );
				printf( "   --> code: %lx\n", code );
				viClose( devSess );
			}
		} else {
			// unknown!!!
			break;
		}
		status = viFindNext( list, "" );
	} while(  true );


	// viSetAttribute( sess, FIND_RSRC_MODE, attr );  // restore prev value
}

int main(int argc, char **argv) {
	   /*
	    *  First we open a session to the VISA resource manager.  We are
	    *  returned a handle to the resource manager session that we must
	    *  use to open sessions to specific instruments.
	    */
	   status = viOpenDefaultRM (&defaultRM);
	   if (status < VI_SUCCESS)
	   {
	      printf("Could not open a session to the VISA Resource Manager!\n");
	      exit (EXIT_FAILURE);
	   }

	   findRsrc( defaultRM, "visa://localhost::RTRTX::0/PXI?*INSTR", 0 );
	   findRsrc( defaultRM, "PXI?*INSTR", 0 );
	   findRsrc( defaultRM, "USB?*::0x3923::?*::RAW", 2 );

	   //status = viOpen (defaultRM, "GPIB::2::INSTR", VI_NULL, VI_NULL, &inst);
	   //status = viEnableEvent (inst, VI_EVENT_IO_COMPLETION, VI_HNDLR, VI_NULL);
	   //viClose(inst);

	   viClose( defaultRM );
}


