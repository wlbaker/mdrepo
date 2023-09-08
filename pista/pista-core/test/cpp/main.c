//Author: LabJack
//December 27, 2011
//This example program reads analog inputs AI0-AI4 using stream mode.  Requires
//a U3 with hardware version 1.21 or higher.

#include "u3.h"
#include "u3Stream.h"

//responses in one large packet, otherwise
//can be any value between 1-25 for 1
//U3_streamData response per packet.

int main(int argc, char **argv)
{
    HANDLE hDevice;
    u3CalibrationInfo caliInfo;
    u3CDataModel cdm;

    // U3_CDM_init( 10, 500, 3, 0, &cdm );
	U3_CDM_init( 100, 500, 3, 0, &cdm );

    //Opening first found U3 over USB
    if( (hDevice = U3_openUSBConnection(-1)) == NULL )
    goto done;

    //Getting calibration information from U3
    if( U3_getCalibrationInfo(hDevice, &caliInfo) < 0 )
    goto close;

    if( U3_configIO(hDevice, 255, 255 ) != 0 )  // tell everything to be AIN
    goto close;

    //Stopping any previous streams
    U3_streamStop(hDevice);
   
    if( U3_streamConfig(hDevice, &cdm) != 0 )
    goto close;
   
    if( U3_streamStart(hDevice) != 0 )
    goto close;

    for( int i = 0; i < 3 ; i++) {
       	U3_streamData(hDevice, &caliInfo, &cdm);
		//printf("(%d,%d) %d ", i, cdm.totPackets, cdm.ibuf[0][0] );
		//printf("%d ", cdm.ibuf[0][1] );
    }
    U3_streamStop(hDevice);

    close:
    U3_closeUSBConnection(hDevice);

    done:
    return 0;
}

