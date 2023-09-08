#pragma once
#include <vector>
#include "math.h"
#include <iostream>
// Super class that keeps track of timing and indexing for buffers.
using namespace std;

class timeBuffer
{
public:
	
	int getEndIndex();
	int getStartIndex();
	double getFirstTimeStamp();
	double getLastTimeStamp();

	//used to set a time difference variable. To adjust for different timereferences
	void setTimeDifference(double diff);
	
	int getCurrentBufferSize(){return currentBufferSize;}
	int getMaxBufferSize(){return maxBufferSize;}
	bool isBufferFull();

private:
	
	double timeDifference;
	vector<double> timeStamps;
	size_t nextIndex;
	size_t maxBufferSize;
	size_t currentBufferSize;

	
protected:
	timeBuffer(size_t size);
	~timeBuffer();
	int getClosestTimeIndex(double & timestamp, size_t startIndex, double& diff);
	bool getTimeInterval(double startTime, double endTime, int &startIndex, int & endIndex, vector<double> &times);
	bool getTimeInterval(double endTime, int nSamples, int &startIndex, int & endIndex, vector<double> &times);
	
	int addValueAndGetCurrentIndexIfValidTimestamp(double timeStamp);



};