#include "timeReference.h"

using namespace igstk;

timeReference::timeReference(void)
{
	
	igstk::RealTimeClock::Initialize();
	currentTimeReference = RealTimeClock::GetTimeStamp()/1000;

	plotting_delay=0;//setCurrentPlottingTimeSampleReference(0);
}


timeReference::~timeReference(void)
{
}

double timeReference::getTimeDifference(double alternativeTimeReferenceSample){
	

	double time=RealTimeClock::GetTimeStamp()/1000-alternativeTimeReferenceSample;

	return time;
}

void timeReference::initializeTimeReference()
{

	currentTimeReference = RealTimeClock::GetTimeStamp()/1000;

	//setCurrentPlottingTimeSampleReference(0);

}

void timeReference::initializeGEStreamerTimeDifference(double currentGEStreamerTimeStamp)
{
	double ts = getCurrentTimeSample();
	geStreamerTimeDifference = currentGEStreamerTimeStamp-ts;
}

void timeReference::resetTimeReference(){

	currentTimeReference = RealTimeClock::GetTimeStamp()/1000;

}

double timeReference::getCurrentTimeSample(){

	double time=RealTimeClock::GetTimeStamp()/1000-currentTimeReference;

	return time;
}

double timeReference::getCurrentPlottingTimeSample()
{
	
	double time=getCurrentTimeSample() - plotting_delay;
	
	return time;
}

void timeReference::setCurrentPlottingTimeDelay(double delay)
{
	
	plotting_delay = delay;
	
}