/*
 * NIFuncs.cpp
 *
 *  Created on: Oct 7, 2009
 *      Author: bbaker
 */

#include <iostream>
#include <list>

#include "NIFuncs.h"

using namespace std;

int32 error = 0;
TaskHandle taskHandle = 0;
char errBuff[2048] = { '\0' };
float64 data[500]; // NI's double, also corresponds to java's double


void parse(list<string> &L, const char *s) {

	const char *start = s;
	const char *end = start;
	char *port;
	int len;

	while (*start != '\0' ) {
		end = start;
		while (*end != ',' && *end != '\0') {
			end++;
		}
		len = end - start + 1;
		if (len > 1) {
			port = (char *) malloc(len);
			memcpy(port, start, len - 1);
			port[len - 1] = '\0';

			string s( port );
			L.push_back(s);
		}
		while (*end == ',' || *end == ' ') {
			end++;
		}

		start = end;
	}

}

int ni_getDevices(list<string> &L) {
	// buffersize = DAQmxGetSystemInfoAttribute(DAQmx_Sys_DevNames,devicenames);
	int buffersize = DAQmxGetSysDevNames(NULL, 0);

	if (buffersize <= 0) {
		return 0;
	}

	char *devicenames = new char[buffersize];
	buffersize = DAQmxGetSysDevNames(devicenames, buffersize);

	parse(L, devicenames);

	delete devicenames;

	return L.size();
}

//Get Product Type for a device

int ni_getDevicePorts(list<string> &L, const char *dev) {

	int sizezz = DAQmxGetDevAIPhysicalChans(dev, NULL, 0);

	char *phnames = new char[sizezz];
	DAQmxGetDevAIPhysicalChans(dev, phnames, sizezz);

	parse(L, phnames);

	delete phnames;
	return L.size();
}

int ni_getDevicesSerNum(char *dev) {
	int devicesernum = -1;
	DAQmxGetDeviceAttribute(dev, DAQmx_Dev_SerialNum, &devicesernum, 1);

	return devicesernum;
}

//Get Product Serial Number for the device

//Get Is device simulated? for the device
//? DAQmxGetDeviceAttribute(pch, DAQmx_Dev_IsSimulated,	&is_simulated, 1);

// char* devicetype;

//int devicetype_buffersize = DAQmxGetDeviceAttribute(pch, DAQmx_Dev_ProductType, NULL);
//devicetype = (char *) malloc(devicetype_buffersize);
//
//DAQmxGetDeviceAttribute(pch, DAQmx_Dev_ProductType, devicetype, devicetype_buffersize);
