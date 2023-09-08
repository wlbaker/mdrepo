//Author: LabJack
//December 27, 2011
//This example program reads analog inputs AI0-AI4 using stream mode.  Requires
//a U3 with hardware version 1.21 or higher.

#include <math.h>  // debug only
#include <stdio.h>

#include "pista.h"
#include "u3.h"
#include "api.h"


//responses in one large packet, otherwise
//can be any value between 1-25 for 1
//U3_streamData response per packet.
//
//

const uint8 U3_samplesPerUSBPacket[] = { 
        -1,  // zero channels
        25,  // 1 * 25
        24,  // 2 * 12
        24,  // 3 * 8
        24,  // 4 * 6
        25,  // 5 * 5
        24,  // 6 * 4
        21,  // 7 * 3
        24,  // 8 * 3
        18,  // 9 * 2
        20,  // 10 * 2
        22,  // 11 * 2
        24,  // 12 * 2
        13,  // 13 * 1
        14,  // 14 * 1
        15,  // 15 * 1
        16  // 16 * 1
};


int U3_CDM_apply_settings( struct U3_context *cdm) {
	// int hzz, int reads_per_sample, int ms, int fio, int eio;
	
	// config computed values
	cdm->bufsz = ((long) cdm->s.ms * cdm->s.hzz)/(1000);
	cdm->numCh = __builtin_popcount (cdm->s.fin_mask);
    cdm->numCh += __builtin_popcount (cdm->s.ein_mask);
    cdm->usb_spp = U3_samplesPerUSBPacket[ cdm->numCh ];

	//int align_sz = cdm->bufsz * cdm->numCh;
	//if( cdm->usb_spp > align_sz ) {
		//cdm->usb_spp = align_sz;
	//}
	if( cdm->bufsz > 10 ) { // optimize bufsz and hz
		// bufsz should be a multiple of scans in the usb_spp
		int scans = 25 / cdm->usb_spp;
		int residual = cdm->bufsz % scans;
		if( residual > 0 ) {
			cdm->bufsz += (scans - residual);
		}
	}
	int interval = 4000000 / (cdm->s.hzz * cdm->s.rps); // using 4MHz clock
	int skip = interval / 65536; // skipping scans on host side

	cdm->hw_scanInterval = interval / (skip + 1);
	cdm->hw_scanSkip = (skip+1) * cdm->s.rps - 1;

	// cdm->hz = hzz;
	// cdm->pkt_ms = ms;

	cdm->totPackets = 0;  // should really be reset in streamStart
	cdm->discard    = 0;  // should really be reset in streamStart

	cdm->mult = 1;
	cdm->m = cdm->mult;  // this will trigger a read...put in streamStart!
	cdm->pkt_sz = 14 + cdm->usb_spp * 2;
	cdm->recBuff = (uint8 *)malloc(cdm->pkt_sz * cdm->mult );

	printf("numch=%d\n", cdm->numCh );
	printf("hz=%d\n", cdm->s.hzz );
	printf("ms=%d\n", cdm->s.ms );
	printf("fio=%d\n", cdm->s.fin_mask );
	printf("eio=%d\n", cdm->s.ein_mask );
	printf("bufsz=%d\n", cdm->bufsz );
	printf("USBSPP=%d\n", cdm->usb_spp );
	printf("skip/scanInterval=%d/%d\n", cdm->hw_scanSkip, cdm->hw_scanInterval );
	printf("ms-x=%d\n", (cdm->bufsz * 1000) / cdm->s.hzz );

	cdm->u3f = PISTA_MALLOC( sizeof( U3__U3Fsensor ) );
	cdm->u3e = PISTA_MALLOC( sizeof( U3__U3Esensor) );

	u3__u3_fsensor__init( cdm->u3f );
	u3__u3_esensor__init( cdm->u3e );

	int32_t *alloc_if( int mask, size_t count ) {
		int32_t *p = NULL;
		if( mask ) {
			p = (int32_t *)calloc( sizeof(int32_t) * count, 1 );
		}
		return p;
	}

	int nn = cdm->bufsz;
	cdm->u3f->n_ain0 = ( cdm->s.fin_mask & 0x01 ) ? nn : 0;
	cdm->u3f->n_ain1 = ( cdm->s.fin_mask & 0x02 ) ? nn : 0;
	cdm->u3f->n_ain2 = ( cdm->s.fin_mask & 0x04 ) ? nn : 0;
	cdm->u3f->n_ain3 = ( cdm->s.fin_mask & 0x08 ) ? nn : 0;
	cdm->u3f->n_fio4 = ( cdm->s.fin_mask & 0x10 ) ? nn : 0;
	cdm->u3f->n_fio5 = ( cdm->s.fin_mask & 0x20 ) ? nn : 0;
	cdm->u3f->n_fio6 = ( cdm->s.fin_mask & 0x40 ) ? nn : 0;
	cdm->u3f->n_fio7 = ( cdm->s.fin_mask & 0x80 ) ? nn : 0;

	cdm->u3e->n_eio0 = ( cdm->s.ein_mask & 0x01 ) ? nn : 0;
	cdm->u3e->n_eio1 = ( cdm->s.ein_mask & 0x02 ) ? nn : 0;
	cdm->u3e->n_eio2 = ( cdm->s.ein_mask & 0x04 ) ? nn : 0;
	cdm->u3e->n_eio3 = ( cdm->s.ein_mask & 0x08 ) ? nn : 0;
	cdm->u3e->n_eio4 = ( cdm->s.ein_mask & 0x10 ) ? nn : 0;
	cdm->u3e->n_eio5 = ( cdm->s.ein_mask & 0x20 ) ? nn : 0;
	cdm->u3e->n_eio6 = ( cdm->s.ein_mask & 0x40 ) ? nn : 0;
	cdm->u3e->n_eio7 = ( cdm->s.ein_mask & 0x80 ) ? nn : 0;

	cdm->ch_ibuf[0] = cdm->u3f->ain0 = alloc_if( cdm->s.fin_mask & 0x01, nn );
	cdm->ch_ibuf[1] = cdm->u3f->ain1 = alloc_if( cdm->s.fin_mask & 0x02, nn );
	cdm->ch_ibuf[2] = cdm->u3f->ain2 = alloc_if( cdm->s.fin_mask & 0x04, nn );
	cdm->ch_ibuf[3] = cdm->u3f->ain3 = alloc_if( cdm->s.fin_mask & 0x08, nn );
	cdm->ch_ibuf[4] = cdm->u3f->fio4 = alloc_if( cdm->s.fin_mask & 0x10, nn );
	cdm->ch_ibuf[5] = cdm->u3f->fio5 = alloc_if( cdm->s.fin_mask & 0x20, nn );
	cdm->ch_ibuf[6] = cdm->u3f->fio6 = alloc_if( cdm->s.fin_mask & 0x40, nn );
	cdm->ch_ibuf[7] = cdm->u3f->fio7 = alloc_if( cdm->s.fin_mask & 0x80, nn );
	cdm->ch_ibuf[8]  = cdm->u3e->eio0 = alloc_if( cdm->s.ein_mask & 0x01, nn );
	cdm->ch_ibuf[9]  = cdm->u3e->eio1 = alloc_if( cdm->s.ein_mask & 0x02, nn );
	cdm->ch_ibuf[10] = cdm->u3e->eio2 = alloc_if( cdm->s.ein_mask & 0x04, nn );
	cdm->ch_ibuf[11] = cdm->u3e->eio3 = alloc_if( cdm->s.ein_mask & 0x08, nn );
	cdm->ch_ibuf[12] = cdm->u3e->eio4 = alloc_if( cdm->s.ein_mask & 0x10, nn );
	cdm->ch_ibuf[13] = cdm->u3e->eio5 = alloc_if( cdm->s.ein_mask & 0x20, nn );
	cdm->ch_ibuf[14] = cdm->u3e->eio6 = alloc_if( cdm->s.ein_mask & 0x40, nn );
	cdm->ch_ibuf[15] = cdm->u3e->eio7 = alloc_if( cdm->s.ein_mask & 0x80, nn );

	return PISTA_OK;
}

int U3_openUSBConnection( struct U3_context *cdm, int localID)
{
    uint8 buffer[38];  //send size of 26, receive size of 38
    uint16 checksumTotal = 0;
    uint32 numDevices = 0;
    uint32 dev;
    int i, serial;
    cdm->hDevice = 0;

    numDevices = LJUSB_GetDevCount(U3_PRODUCT_ID);
    if( numDevices == 0 )
    {
        printf("Open error: No U3 devices could be found\n");
        return PISTA_ERR_IO;
    }

    for( dev = 1;  dev <= numDevices; dev++ )
    {
        HANDLE hDevice = LJUSB_OpenDevice(dev, 0, U3_PRODUCT_ID);
        if( hDevice != NULL )
        {
            if( localID < 0 )
            {
				cdm->hDevice = hDevice;
        		return PISTA_OK;
            }
            else
            {
                checksumTotal = 0;

                //Setting up a ConfigU3 command
                buffer[1] = (uint8)(0xF8);
                buffer[2] = (uint8)(0x0A);
                buffer[3] = (uint8)(0x08);

                for( i = 6; i < 38; i++ )
                    buffer[i] = (uint8)(0x00);

                extendedChecksum(buffer, 26);

                if( LJUSB_Write(hDevice, buffer, 26) != 26 )
                    goto locid_error;

                if( LJUSB_Read(hDevice, buffer, 38) != 38 )
                    goto locid_error;

                checksumTotal = extendedChecksum16(buffer, 38);
                if( (uint8)((checksumTotal / 256) & 0xFF) != buffer[5] )
                    goto locid_error;

                if( (uint8)(checksumTotal & 0xFF) != buffer[4] )
                    goto locid_error;

                if( extendedChecksum8(buffer) != buffer[0] )
                    goto locid_error;

                if( buffer[1] != (uint8)(0xF8) || buffer[2] != (uint8)(0x10) ||
                    buffer[3] != (uint8)(0x08) )
                    goto locid_error;

                if( buffer[6] != 0 )
                    goto locid_error;

                //Check local ID
                if( (int)buffer[21] == localID ) {
					cdm->hDevice = hDevice;
					return PISTA_OK;
				}

                //Check serial number
                serial = (int)(buffer[15] + buffer[16]*256 + buffer[17]*65536 +
                               buffer[18]*16777216);
                if( serial == localID )
					cdm->hDevice = hDevice;
					return PISTA_OK;

                //No matches, not our device
                LJUSB_CloseDevice(hDevice);
            } //else localID >= 0 end
        } //if hDevice != NULL end
    } //for end

    printf("Open error: could not find a U3 with a local ID or serial number of %d count=%d\n", localID, numDevices );
    return PISTA_ERR_IO;

locid_error:
    printf("Open error: problem when checking local ID\n");
    return PISTA_ERR_IO;
}


void U3_closeUSBConnection(struct U3_context *cdm)
{
    LJUSB_CloseDevice(cdm->hDevice);
	cdm->hDevice = 0;
}



//Sends a ConfigIO low-level command that configures the FIOs, DAC, Timers and
//Counters for this example
//
//set fio=255 and eio=255 for analog input on all channels
//
//you will have to dig deeper to figure out what data is returned and build a
//structure for it
//
int U3_configIO(struct U3_context *cdm, int fio, int eio) {
	uint8 sendBuff[12], recBuff[12];
	uint16 checksumTotal;
	int sendChars, recChars;

	sendBuff[1] = (uint8) (0xF8);  //Command byte
	sendBuff[2] = (uint8) (0x03);  //Number of data words
	sendBuff[3] = (uint8) (0x0B);  //Extended command number

	sendBuff[6] = 13; //Writemask : Setting writemask for timerCounterConfig (bit 0),
					  //            FIOAnalog (bit 2) and EIOAnalog (bit 3)

	sendBuff[7] = 0;  //Reserved
	sendBuff[8] = 64;  //TimerCounterConfig: Disabling all timers and counters,
					   //                    set TimerCounterPinOffset to 4 (bits 4-7)
	sendBuff[9] = 0;  //DAC1Enable...wlb--old firmware version(?)

	sendBuff[10] = fio;  //FIOAnalog : setting all FIOs as analog inputs
	sendBuff[11] = eio;  //EIOAnalog : setting all EIOs as analog inputs
	extendedChecksum(sendBuff, 12);

	//Sending command to U3
	if ((sendChars = LJUSB_Write(cdm->hDevice, sendBuff, 12)) < 12) {
		if (sendChars == 0)
			printf("ConfigIO error : write failed\n");
		else
			printf("ConfigIO error : did not write all of the buffer\n");
		return  PISTA_ERR_IO;
	}

	//Reading response from U3
	if ((recChars = LJUSB_Read(cdm->hDevice, recBuff, 12)) < 12) {
		if (recChars == 0)
			printf("ConfigIO error : read failed\n");
		else
			printf("ConfigIO error : did not read all of the buffer\n");
		return -1;
	}

	checksumTotal = extendedChecksum16(recBuff, 12);
	if ((uint8) ((checksumTotal / 256) & 0xFF) != recBuff[5]) {
		printf("ConfigIO error : read buffer has bad checksum16(MSB)\n");
		return -1;
	}

	if ((uint8) (checksumTotal & 0xFF) != recBuff[4]) {
		printf("ConfigIO error : read buffer has bad checksum16(LBS)\n");
		return -1;
	}

	if (extendedChecksum8(recBuff) != recBuff[0]) {
		printf("ConfigIO error : read buffer has bad checksum8\n");
		return -1;
	}

	if (recBuff[1] != (uint8) (0xF8) || recBuff[2] != (uint8) (0x03) || recBuff[3] != (uint8) (0x0B)) {
		printf("ConfigIO error : read buffer has wrong command bytes\n");
		return -1;
	}

	if (recBuff[6] != 0) {
		printf("ConfigIO error : read buffer received errorcode %d\n", recBuff[6]);
		return -1;
	}

	if (recBuff[8] != 64) {
		printf("ConfigIO error : TimerCounterConfig did not get set correctly\n");
		return -1;
	}

	if (recBuff[10] != 255 && recBuff[10] != (uint8) (0x0F)) {
		printf("ConfigIO error : FIOAnalog did not set get correctly\n");
		return -1;
	}

	if (recBuff[11] != 255) {
		printf("ConfigIO error : EIOAnalog did not set get correctly (%d)\n", recBuff[11]);
		return -1;
	}

        //wlb--support for old firmware(?)
	//if (isDAC1Enabled != NULL) {
		//*isDAC1Enabled = (int) recBuff[9];
	//}

	return 0;
}

//Sends a U3_streamConfig low-level command to configure the stream.
int U3_streamConfig( struct U3_context *cdm ) {
	uint8 sendBuff[64], recBuff[8];
	uint16 checksumTotal;
	int sendBuffSize, sendChars, i;

	for (i = 0; i < 16 ; i++) { cdm->chMap[i] = -1; }

    int numChannels = 0;
	int mask = cdm->s.fin_mask;
	for (i = 0; i < 16 ; i++) {
		bool f = ( mask % 2 );
		if( f ) {
			sendBuff[12 + numChannels * 2] = i;  //PChannel = i
			sendBuff[13 + numChannels * 2] = 31;  //NChannel = 31: Single Ended
			cdm->chMap[numChannels] = i;
        	numChannels++;
		}

       	mask >>= 1;
		if( i == 7) mask = cdm->s.ein_mask;
	}

	if( cdm->numCh != numChannels ) {
		printf("INVALID NUM CHANNELS: %d != %d\n", cdm->numCh, numChannels );
		exit(-2);
	}

        // a GCC built-in to count number of bits set
        // int numChannels = __builtin_popcount (fio);
        // numChannels += __builtin_popcount (eio);

	sendBuffSize = 12 + numChannels * 2;

	sendBuff[1] = (uint8) (0xF8);  //Command byte
	sendBuff[2] = 3 + numChannels; //Number of data words = NumChannels + 3
	sendBuff[3] = (uint8) (0x11);  //Extended command number
	sendBuff[6] = cdm->numCh;      //NumChannels
	sendBuff[7] = cdm->usb_spp;    //samplesPerUSBPacket
	sendBuff[8] = 0;  //Reserved
	sendBuff[9] = 1;  //ScanConfig:
					  // Bit 7: Reserved
					  // Bit 6: Reserved
					  // Bit 3: Internal stream clock frequency = b0: 4 MHz, b1: 48 MHz
					  // Bit 2: Divide Clock by 256 = b0
					  // Bits 0-1: Resolution = b01: 11.9-bit effective, b00: 12.8-bits, b10: 11.3-bits, b11: 10.5-bits

	sendBuff[10] = (uint8) (cdm->hw_scanInterval & (0x00FF)); //Scan interval (low byte)
	sendBuff[11] = (uint8) (cdm->hw_scanInterval / 256);  //Scan interval (high byte)

	uint8 l = sendBuff[10];
	uint8 h = sendBuff[11];
	printf("%d ivl=%d,%d  {%d/%d}\n", cdm->hw_scanInterval, h, l, 256*h+l, 256*l + h);


	extendedChecksum(sendBuff, sendBuffSize);

	//Sending command to U3
	sendChars = LJUSB_Write(cdm->hDevice, sendBuff, sendBuffSize);
	if (sendChars < sendBuffSize) {
		if (sendChars == 0)
			printf("Error : write failed (U3_streamConfig).\n");
		else
			printf("Error : did not write all of the buffer (U3_streamConfig).\n");
		return -1;
	}

	for (i = 0; i < 8; i++)
		recBuff[i] = 0;

	//Reading response from U3
	int recChars = LJUSB_Read(cdm->hDevice, recBuff, 8);
	if (recChars < 8) {
		if (recChars == 0)
			printf("Error : read failed (U3_streamConfig).\n");
		else
			printf("Error : did not read all of the buffer, %d (U3_streamConfig).\n", recChars);

		for (i = 0; i < 8; i++)
			printf("%d ", recBuff[i]);

		return -1;
	}

	checksumTotal = extendedChecksum16(recBuff, 8);
	if ((uint8) ((checksumTotal / 256) & 0xFF) != recBuff[5]) {
		printf("Error : read buffer has bad checksum16(MSB) (U3_streamConfig).\n");
		return -1;
	}

	if ((uint8) (checksumTotal & 0xFF) != recBuff[4]) {
		printf("Error : read buffer has bad checksum16(LBS) (U3_streamConfig).\n");
		return -1;
	}

	if (extendedChecksum8(recBuff) != recBuff[0]) {
		printf("Error : read buffer has bad checksum8 (U3_streamConfig).\n");
		return -1;
	}

	if (recBuff[1] != (uint8) (0xF8) || recBuff[2] != (uint8) (0x01) || recBuff[3] != (uint8) (0x11)
			|| recBuff[7] != (uint8) (0x00)) {
		printf("Error : read buffer has wrong command bytes (U3_streamConfig).\n");
		return -1;
	}

	if (recBuff[6] != 0) {
		printf("Errorcode # %d from U3_streamConfig read.\n", (unsigned int) recBuff[6]);
		return -1;
	}

	return 0;
}

//Sends a U3_streamStart low-level command to start streaming.
int U3_streamStart(struct U3_context *cdm) {
	uint8 sendBuff[2], recBuff[4];
	int sendChars;

	sendBuff[0] = (uint8) (0xA8);  //CheckSum8
	sendBuff[1] = (uint8) (0xA8);  //command byte

	//Sending command to U3
	sendChars = LJUSB_Write(cdm->hDevice, sendBuff, 2);
	if (sendChars < 2) {
		if (sendChars == 0)
			printf("Error : write failed.\n");
		else
			printf("Error : did not write all of the buffer.\n");
		return -1;
	}

	//Reading response from U3
	int recChars = LJUSB_Read(cdm->hDevice, recBuff, 4);
	if (recChars < 4) {
		if (recChars == 0)
			printf("Error : read failed.\n");
		else
			printf("Error : did not read all of the buffer.\n");
		return -1;
	}

	if (normalChecksum8(recBuff, 4) != recBuff[0]) {
		printf("Error : read buffer has bad checksum8 (U3_streamStart).\n");
		return -1;
	}

	if (recBuff[1] != (uint8) (0xA9) || recBuff[3] != (uint8) (0x00)) {
		printf("Error : read buffer has wrong command bytes \n");
		return -1;
	}

	if (recBuff[2] != 0) {
		printf("Errorcode # %d from U3_streamStart read.\n", (unsigned int) recBuff[2]);
		return -1;
	}

	return 0;
}

//Gets calibration information from memory blocks 0-4 of a U3.  Returns the
//calibration information in a calibrationInfo structure.
//hDevice = handle to a U3 device
//caliInfo = structure where calibrarion information will be stored

int U3_getCalibrationInfo( struct U3_context *cdm)
{
    uint8 sendBuffer[8], recBuffer[40];
    uint8 cU3SendBuffer[26], cU3RecBuffer[38];
    int sentRec = 0, offset = 0, i = 0;

    /* Sending ConfigU3 command to get hardware version and see if HV */
    cU3SendBuffer[1] = (uint8)(0xF8);  //Command byte
    cU3SendBuffer[2] = (uint8)(0x0A);  //Number of data words
    cU3SendBuffer[3] = (uint8)(0x08);  //Extended command number

    //Setting WriteMask0 and all other bytes to 0 since we only want to read the
    //response
    for( i = 6; i < 26; i++ )
        cU3SendBuffer[i] = 0;

    extendedChecksum(cU3SendBuffer, 26);

    sentRec = LJUSB_Write(cdm->hDevice, cU3SendBuffer, 26);
    if( sentRec < 26 )
    {
        if( sentRec == 0 )
            goto writeError0;
        else
            goto writeError1;
    }

    sentRec = LJUSB_Read(cdm->hDevice, cU3RecBuffer, 38);
    if( sentRec < 38 )
    {
        if( sentRec == 0 )
            goto readError0;
        else
            goto readError1;
    }

    if( cU3RecBuffer[1] != (uint8)(0xF8) || cU3RecBuffer[2] != (uint8)(0x10) ||
        cU3RecBuffer[3] != (uint8)(0x08))
        goto commandByteError;

	U3CalibrationInfo *caliInfo = &cdm->caliInfo;
    caliInfo->hardwareVersion = cU3RecBuffer[14] + cU3RecBuffer[13]/100.0;
    if( (cU3RecBuffer[37] & 18) == 18 )
        caliInfo->highVoltage = 1;
    else
        caliInfo->highVoltage = 0;

    for( i = 0; i < 5; i++ )
    {
        /* Reading block i from memory */
        sendBuffer[1] = (uint8)(0xF8);  //Command byte
        sendBuffer[2] = (uint8)(0x01);  //Cumber of data words
        sendBuffer[3] = (uint8)(0x2D);  //Extended command number
        sendBuffer[6] = 0;
        sendBuffer[7] = (uint8)i;  //Blocknum = i
        extendedChecksum(sendBuffer, 8);

        sentRec = LJUSB_Write(cdm->hDevice, sendBuffer, 8);
        if( sentRec < 8 )
        {
            if( sentRec == 0 )
                goto writeError0;
            else
                goto writeError1;
        }

        sentRec = LJUSB_Read(cdm->hDevice, recBuffer, 40);
        if( sentRec < 40 )
        {
            if( sentRec == 0 )
                goto readError0;
            else
                goto readError1;
        }

        if( recBuffer[1] != (uint8)(0xF8) || recBuffer[2] != (uint8)(0x11) ||
            recBuffer[3] != (uint8)(0x2D) )
            goto commandByteError;

        offset = i * 4;

        //Block data starts on byte 8 of the buffer
        caliInfo->ccConstants[offset] = FPuint8ArrayToFPDouble(recBuffer + 8, 0);
        caliInfo->ccConstants[offset + 1] = FPuint8ArrayToFPDouble(recBuffer + 8, 8);
        caliInfo->ccConstants[offset + 2] = FPuint8ArrayToFPDouble(recBuffer + 8, 16);
        caliInfo->ccConstants[offset + 3] = FPuint8ArrayToFPDouble(recBuffer + 8, 24);
    }

    caliInfo->prodID = 3;

    return 0;

writeError0:
    printf("Error : getCalibrationInfo write failed\n");
    return -1;
writeError1:
    printf("Error : getCalibrationInfo did not write all of the buffer\n");
    return -1;
readError0:
    printf("Error : getCalibrationInfo read failed\n");
    return -1;
readError1:
    printf("Error : getCalibrationInfo did not read all of the buffer\n");
    return -1;
commandByteError:
    printf("Error : getCalibrationInfo received wrong command bytes for ReadMem\n");
    return -1;
}



//Reads the U3_streamData low-level function response in a loop.  All voltages from
//the stream are stored in the voltages 2D array.
int U3_streamData( struct U3_context *cdm) {
	uint16 checksumTotal;
	int recBuffSize;
	int i, j;

	int readSizeMultiplier = cdm->mult; // (cdm->numCh * cdm->bufsz) / cdm->usb_spp;
	int responseSize = cdm->pkt_sz;

	/* Each U3_streamData response contains (samplesPerUSBPacket / NumChannels) * readSizeMultiplier
	 * samples for each channel.
	 * Total number of scans = (samplesPerUSBPacket / NumChannels) * readSizeMultiplier * numReadsPerDisplay * numDisplay
	 */
	uint8 *recBuff = cdm->recBuff;

	int chIdx = 0;
	bool autoRecoveryOn = false;
	recBuffSize = 14 + cdm->usb_spp * 2;
	if( cdm->caliInfo.hardwareVersion < 1.3 ) {
		printf("UNSUPPORTED HARDWARE VERSION: [%f]", cdm->caliInfo.hardwareVersion);
		return -1;
	}

	// loop needed top account for slow scan rates and discarded packets
	int scanNumber = 0;
	int k = cdm->k;
	int m = cdm->m;
	// int loops = 1 + cdm->hw_scanSkip;
	// printf("READSTART: m=%d k=%d\n", m, k);

	double tot[16];
	for( int i = 0; i < 16; i++) {
		tot[i] = 0.0;
	}
	do {
		//Reading stream response from U3
		if( m >= readSizeMultiplier ) {
			// printf("STREAM READ: %d\n", responseSize * readSizeMultiplier );
			int recChars = LJUSB_Stream(cdm->hDevice, recBuff, responseSize * readSizeMultiplier);
			if (recChars < responseSize * readSizeMultiplier) {
				if (recChars == 0)
					printf("Error : read failed (U3_streamData).\n");
				else
					printf("Error : did not read all of the buffer, expected %d bytes but received %d(U3_streamData).\n",
							responseSize * readSizeMultiplier, recChars);
				return -1;
			}
			m = 0;
			k = 12;
		}

		int chIdx = 0;  // our packets always contain an integer number of channel scan

		for ( ; m < readSizeMultiplier; m++) {
			// printf("one packet: %d < %d\n", m, readSizeMultiplier );
			cdm->m = m;
			cdm->totPackets++;

			checksumTotal = extendedChecksum16(recBuff + m * recBuffSize, recBuffSize);
			if ((uint8) ((checksumTotal / 256) & 0xFF) != recBuff[m * recBuffSize + 5]) {
				printf("Error : read buffer has bad checksum16(MSB) (U3_streamData).\n");
				return -1;
			}

			if ((uint8) (checksumTotal & 0xFF) != recBuff[m * recBuffSize + 4]) {
				printf("Error : read buffer has bad checksum16(LBS) (U3_streamData).\n");
				return -1;
			}

			checksumTotal = extendedChecksum8(recBuff + m * recBuffSize);
			if (checksumTotal != recBuff[m * recBuffSize]) {
				printf("Error : read buffer has bad checksum8 (U3_streamData).\n");
				return -1;
			}

			if (recBuff[m * recBuffSize + 1] != (uint8) (0xF9) || recBuff[m * recBuffSize + 2] != 4 + cdm->usb_spp
					|| recBuff[m * recBuffSize + 3] != (uint8) (0xC0)) {
				printf("Error : read buffer has wrong command bytes (U3_streamData).\n");
				return -1;
			}

			if (recBuff[m * recBuffSize + 11] == 59) {
				if (!autoRecoveryOn) {
					printf(
							"\nU3 data buffer overflow detected in packet %d.\nNow using auto-recovery and reading buffered samples.\n",
							cdm->totPackets);
					autoRecoveryOn = true;
				}
			} else if (recBuff[m * recBuffSize + 11] == 60) {
				printf("Auto-recovery report in packet %d: %d scans were dropped.\nAuto-recovery is now off.\n",
						cdm->totPackets, recBuff[m * recBuffSize + 6] + recBuff[m * recBuffSize + 7] * 256);
				autoRecoveryOn = true;
			} else if (recBuff[m * recBuffSize + 11] != 0) {
				printf("Errorcode # %d from U3_streamData read.\n", (unsigned int) recBuff[11]);
				return -1;
			}

			cdm->backlog = (int) recBuff[m * 48 + 12 + cdm->usb_spp * 2];

			for (; k < (12 + cdm->usb_spp * 2); k += 2) {
				if( chIdx == 0 ) {
				 	if(cdm->discard > 0) {
						cdm->discard--;
					} else {
						cdm->discard = cdm->hw_scanSkip;
					}
				}
				int currCh = cdm->chMap[chIdx++];   // record current ch and increment
				chIdx %= cdm->numCh;



				uint16 l = (uint16) recBuff[m * recBuffSize + k];
				uint16 h = (uint16) recBuff[m * recBuffSize + k + 1];

				uint16 voltageBytes = l + 256*h;
				

				// FIXME: int values are not averaged...you just get the last one
				int32_t *ibuf = cdm->ch_ibuf[currCh];
				ibuf[scanNumber] = voltageBytes;

				double v;
				getAinVoltCalibrated_hw130(&cdm->caliInfo, currCh, 31, voltageBytes, &v );
				tot[currCh] += v;
				
				if( cdm->discard > 0 ) {
					// printf("  skip: %d %d  %f tot=%f\n", currCh, k, v, tot[currCh] );
					continue;
				}
				// printf("   add: %d %d  %f tot=%f\n", currCh, k, v, tot[currCh] );
#ifdef SAVE_AS_VOLTAGE
				cdm->dbuf[currCh].ddat[scanNumber] = 1000 * tot[currCh] / (cdm->hw_scanSkip + 1); // 1000.0 * v;
#endif
				tot[currCh] = 0;


				// printf("Z CH=%d SCAN=%d K=%d VAL=%f **\n", currCh, scanNumber, k, v);
				// if( currCh == 1 ) {
				//	 printf("\n");
				// }

				if( chIdx == 0 ) {  // already incremented for next scan
					scanNumber++;
					if( scanNumber >= cdm->bufsz ) {
						k+=2; // when breaking out of the loop, increment k
						goto full_packet;
					}
				}

			}

		}

		full_packet:
		cdm->k = k;
		if( cdm->backlog ) {
			printf("WARN BackLog: %d\n", cdm->backlog);
		}
		
	} while( scanNumber < cdm->bufsz );

	cdm->m = m;
	printf("READ END: m=%d k=%d == cdm[%d,%d]\n", m, k, cdm->m, cdm->k );

	/*
	printf("    %d scans for CDM=%lx\n", scanNumber, cdm );
	for(int idx =0; idx < cdm->numCh; idx++ ) {
		int ch = cdm->chMap[idx];
		printf("    [%d,%d] dest: %lx\n", idx, ch, cdm->ibuf[ch] );
	}
	for (k = 0; (k < cdm->bufsz) && (k<5); k++) {
		for(int idx =0; idx < cdm->numCh; idx++ ) {
			int ch = cdm->chMap[idx];
			printf("   %2d  AI%d->%d: %8dI == %.4f V", k, idx, ch, cdm->ibuf[ch].idat[k], cdm->dbuf[ch].ddat[k]);
		}
		printf("\n");
	}
*/

	return PISTA_OK;
}

//Sends a U3_streamStop low-level command to stop streaming.
int U3_streamStop( struct U3_context *cdm ) {
	uint8 sendBuff[2], recBuff[4];
	int sendChars;

	sendBuff[0] = (uint8) (0xB0);  //CheckSum8
	sendBuff[1] = (uint8) (0xB0);  //Command byte

	//Sending command to U3
	sendChars = LJUSB_Write(cdm->hDevice, sendBuff, 2);
	if (sendChars < 2) {
		if (sendChars == 0)
			printf("Error : write failed (U3_streamStop).\n");
		else
			printf("Error : did not write all of the buffer (U3_streamStop).\n");
		return -1;
	}

	//Reading response from U3
	int recChars = LJUSB_Read(cdm->hDevice, recBuff, 4);
	if (recChars < 4) {
		if (recChars == 0)
			printf("Error : read failed (U3_streamStop).\n");
		else
			printf("Error : did not read all of the buffer (U3_streamStop).\n");
		return -1;
	}

	if (normalChecksum8(recBuff, 4) != recBuff[0]) {
		printf("Error : read buffer has bad checksum8 (U3_streamStop).\n");
		return -1;
	}

	if (recBuff[1] != (uint8) (0xB1) || recBuff[3] != (uint8) (0x00)) {
		printf("Error : read buffer has wrong command bytes (U3_streamStop).\n");
		return -1;
	}

	if (recBuff[2] != 0) {
		printf("Errorcode # %d from U3_streamStop read.\n", (unsigned int) recBuff[2]);
		return -1;
	}

	return 0;
}
