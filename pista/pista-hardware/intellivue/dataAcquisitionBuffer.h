#ifndef DATAACQUISITIONBUFFER_H
#define DATAACQUISITIONBUFFER_H

#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "timeBuffer.h"


class dataAcquisitionBuffer: public timeBuffer
{
public:
	int getNumberOfSpectrumLines();
	int getSamplingRate();
	static dataAcquisitionBuffer *New(int bufferSize=10000);
	bool getData(double timestamp, double &time, double &data, int & previousIndex);
	void addItem(double  data, double timestamp);
	void addItems(std::vector<double>  data, std::vector<double> timestamp);
	void addItems(std::vector<double> data, double startTime, int samplingRate);
	bool getInterval(double startTime, double endTime, std::vector<double>& data, std::vector<double>& time, int &reference_indexes);
	bool getInterval(double startTime, double endTime, int sampling_rate, std::vector<double>& data, std::vector<double>& time, int &reference_indexes);

	dataAcquisitionBuffer* getBuffer();

private:

	std::vector<double> dataBufferReal;

	dataAcquisitionBuffer(int bufferSize);
	~dataAcquisitionBuffer();

};

#endif
