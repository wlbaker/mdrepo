#pragma once
#include <vector>

#include "igstkRealTimeClock.h"



class timeReference
{
public:
	double currentTimeReference; //where t=0
	std::vector<double> timeLineSamples;
	std::vector<double> timeLineTimes;
	double geStreamerTimeDifference;

	void initializeGEStreamerTimeDifference(double currentGEStreamerTimeStamp);
	void initializeTimeReference();
	double getTimeDifference(double alternativeTimeReference);//Difference from current and reference
	void resetTimeReference();
	double getCurrentTimeSample();
	double getCurrentPlottingTimeSample();
	void setCurrentPlottingTimeDelay(double delay);

	timeReference(void);
	~timeReference(void);

protected:
	double plotting_delay;
};

