
#include "IMP731Driver.h"
 
IMP731Driver::IMP731Driver() {
}

void IMP731Driver::setConfig() {
	IMP731_CDM_init( 100, 1, 500, 0x07, 0, &cdm );
    // IMP731_CDM_init( 10, 500, 3, 0, &cdm );
}

void IMP731Driver::setCDataModel(IMP731CDataModel *cdm) {
	this->cdm = *cdm;
}

void IMP731Driver::dump() {
	printf("CDM=%lx\n", &cdm);
	for(int i=0; i < 2; i++) {
		printf("DUMP channel%d: %lx\n", i, cdm.dbuf[i] );

		for( int k = 0; k < 5; k++) {
			printf("    AIDBUF%d: %f\n", k, cdm.dbuf[i].ddat[k] );
		}
	}
    // IMP731_CDM_init( 10, 500, 3, 0, &cdm );
}

int IMP731Driver::connect() {
	if( (hDevice = IMP731_openUSBConnection(-1) ) == NULL ) goto done;
	IMP731_getCalibrationInfo( hDevice, &caliInfo );
	if( IMP731_configIO( hDevice, 255, 255) ) goto close;

	IMP731_streamStop(hDevice); // stop existing streams, if any.  ignore err

	if( IMP731_streamConfig( hDevice, &cdm) ) goto close;

	if( IMP731_streamStart(hDevice) ) goto close;

	return 0;

close:
	IMP731_closeUSBConnection(hDevice);
	hDevice = NULL;

done:
	printf("******************** CONNECT ERR");
	return -1;
}

int IMP731Driver::read() {
	return IMP731_streamData(hDevice, &caliInfo, &cdm );
}

int IMP731Driver::disconnect() {

	int rc = IMP731_streamStop(hDevice);
	// maybe warn if rc is not 0, but this is not an error
	IMP731_closeUSBConnection(hDevice);

	hDevice = NULL;
	return rc;
}


void IMP731Driver::tick() {
}


