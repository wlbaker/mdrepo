#include "timeBuffer.h"
#include <cmath>


timeBuffer::timeBuffer(size_t size)
{
	maxBufferSize=size;
	timeStamps.resize(size);
	nextIndex=0;
	currentBufferSize=0;
	timeDifference=0;
}

timeBuffer::~timeBuffer()
{

}

void timeBuffer::setTimeDifference( double diff)
{
	timeDifference=diff;
}



int timeBuffer::getClosestTimeIndex(double & timestamp, size_t previousIndex, double& diff)
{
	int searchType=1;// See definition below

	if(currentBufferSize==0)
		return -1;

	if(previousIndex<0 || previousIndex>=currentBufferSize)
		searchType=0;
	
	if(timestamp>getLastTimeStamp() || timestamp<getFirstTimeStamp())
	{
		if(timestamp>getLastTimeStamp())
			searchType=3;
		else
			searchType=2;
	}


	int startIndex, lastIndex;
	switch(searchType)
	{
	case(0)://Search from beginning of buffer to end
		startIndex=getStartIndex();
		break;
	case(1)://Search from previous index to end
		startIndex=previousIndex;
		break;
	case(2)://Timestamp smaller than first buffer value; return first value
		return getStartIndex();
	case(3)://Timestamp larger than last buffer value; return last value
		return getEndIndex();
	case(4)://Buffer size == 0;
		return -1;
	}
	lastIndex=getEndIndex();
	int searchIndex;
	int k=0;
	for(searchIndex=startIndex; searchIndex!=lastIndex; searchIndex=(searchIndex+1)%maxBufferSize)
	{
		k++;
		if(abs(timestamp-timeStamps[searchIndex])<abs(timestamp-timeStamps[(searchIndex+1)%maxBufferSize]))
		{
			break;
		}
	}

	diff=abs(timestamp-timeStamps[searchIndex]);
	if(diff>0.1)
		std::cout << "getIndex diff: " << diff << ", iterations: " << k << ", searchtype: " << searchType << std::endl;
	timestamp=timeStamps[searchIndex];
	return searchIndex;
}

double timeBuffer::getLastTimeStamp()
{
	int index=getEndIndex();
    //printf("%d\n", index) ;
	if(index>=0)
		return timeStamps[index];
	else
		return-1000000;
};
double timeBuffer::getFirstTimeStamp()
{
	int index=getStartIndex();
	if(index>=0)
		return timeStamps[index];
	else
		return-1000000;
}

int timeBuffer::getStartIndex()
{
	if(currentBufferSize==0)
		return -1;
	
	int firstIndex=(currentBufferSize<maxBufferSize)?0:nextIndex;
	return firstIndex;
}

int timeBuffer::getEndIndex()
{
	if(currentBufferSize==0)
		return -2;

	int index=nextIndex==0?maxBufferSize-1:nextIndex-1;
	return index;
}





int timeBuffer::addValueAndGetCurrentIndexIfValidTimestamp(double timeStamp)
{
	
    timeStamp=timeStamp-timeDifference;
    //printf("%f\n",timeStamp);
    //printf("%f\n", getLastTimeStamp()) ;
	if(timeStamp<=getLastTimeStamp())
	{
		return -1;
	}
	
    //printf("INSERTANDO UN TIMESTAMP: %d %f", nextIndex, timeStamp);
	timeStamps[nextIndex]=timeStamp;

	nextIndex=(nextIndex+1)%maxBufferSize;
	if(currentBufferSize<maxBufferSize)
		currentBufferSize++;

	int index=getEndIndex();
	return index;//current index for other data
}
bool timeBuffer::isBufferFull()
{
	return currentBufferSize==maxBufferSize?true:false;
}

bool timeBuffer::getTimeInterval(double endTime, int nSamples, int &startIndex, int & endIndex, vector<double> &times)
{
	times.clear();
	double diff;
	
	int tmp_end_index = getClosestTimeIndex(endTime,endIndex, diff);
	int tmp_start_index;
	if(isBufferFull())
		tmp_start_index = abs((getMaxBufferSize() + tmp_end_index-nSamples)%getMaxBufferSize());
	else
		tmp_start_index = (tmp_end_index-nSamples)%getMaxBufferSize();//Negative values is cought by next if

	if(tmp_start_index<0)
		tmp_start_index=0;

	if(tmp_end_index<0 || tmp_end_index==tmp_start_index)
	{
		return 0;
	}


	if(tmp_end_index>tmp_start_index)
	{
		try{
			times.assign(timeStamps.begin()+tmp_start_index, timeStamps.begin()+tmp_end_index);
		}
		catch(std::exception & e)
		{
			cout << "Error in getTimeInterval(): " << e.what() << endl;
		}
	}
	else
	{
		try{
			times.assign(timeStamps.begin()+tmp_start_index, timeStamps.end());
			times.insert(times.end(), timeStamps.begin(), timeStamps.begin()+tmp_end_index);
		}
		catch(std::exception & e)
		{
			cout << "Error in getTimeInterval(): " << e.what() << endl;
		}
	}
	startIndex = tmp_start_index;
	endIndex = tmp_end_index;
	return 1;
}
bool timeBuffer::getTimeInterval(double startTime, double endTime, int &startIndex, int & endIndex, vector<double> &times)
{
	times.clear();
	double diff;

	startIndex=getClosestTimeIndex(startTime,startIndex, diff);
	int end_interval_Index=getClosestTimeIndex(endTime,startIndex, diff);
	if(startIndex<0 || end_interval_Index<0 || end_interval_Index==startIndex)
	{
		return 0;
	}

	if(end_interval_Index>startIndex)
	{
		try{
			times.assign(timeStamps.begin()+startIndex, timeStamps.begin()+end_interval_Index);
		}
		catch(std::exception & e)
		{
			cout << "Error in getTimeInterval(): " << e.what() << endl;
		}
	}
	else
	{
		try{
			times.assign(timeStamps.begin()+startIndex, timeStamps.end());
			times.insert(times.end(), timeStamps.begin(), timeStamps.begin()+end_interval_Index);
		}
		catch(std::exception & e)
		{
			cout << "Error in getTimeInterval(): " << e.what() << endl;
		}
	}
	endIndex=end_interval_Index;

	return 1;
}
