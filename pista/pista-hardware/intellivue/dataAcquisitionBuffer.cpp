#include "dataAcquisitionBuffer.h"
#include <QDebug>


dataAcquisitionBuffer* dataAcquisitionBuffer::New(int size)
{
	return new dataAcquisitionBuffer(size);
}

dataAcquisitionBuffer::dataAcquisitionBuffer(int size):timeBuffer(size)
{
	dataBufferReal.resize(size);
}


dataAcquisitionBuffer::~dataAcquisitionBuffer()
{
	
}


dataAcquisitionBuffer* dataAcquisitionBuffer::getBuffer(){
	return this;
}


bool dataAcquisitionBuffer::getInterval(double startTime, double endTime, std::vector<double>& data, std::vector<double>& time, int &reference_indexes)
{
	time.clear();
	data.clear();
	int startIndex=reference_indexes, endIndex;
	bool valid=getTimeInterval(startTime, endTime, startIndex, endIndex, time);
	double diff;
	
	if(!valid)
	{
		return 0;
	}
	reference_indexes=startIndex;
	if(endIndex>startIndex)
	{
		data.assign(dataBufferReal.begin()+startIndex, dataBufferReal.begin()+endIndex);
	}
	else
	{
		data.assign(dataBufferReal.begin()+startIndex, dataBufferReal.end());
		data.insert(data.end(), dataBufferReal.begin(), dataBufferReal.begin()+endIndex);
	}
	return 1;
}

bool dataAcquisitionBuffer::getInterval(double start_time, double endTime, int sampling_rate, std::vector<double>& data, std::vector<double>& time, int &reference_indexes)
{
	time.clear();
	data.clear();
	
	double sampling_interval = 1.0/(double)sampling_rate;
	
	double current_time = start_time;
	int current_index=reference_indexes;
	double data_sample, time_sample, diff;

	while(current_time<=endTime)
	{
		current_index=getClosestTimeIndex(current_time, current_index, diff);
		time_sample = current_time;
		if(current_index<0 || current_index == getEndIndex() || current_time == getLastTimeStamp())
		{
			return 0;
		}
		current_time += sampling_interval;
		reference_indexes=current_index;

		if(!time.empty() && time_sample<=time.back())
			continue;
		
		data_sample = dataBufferReal[current_index];
		time.push_back(time_sample);
		data.push_back(data_sample);
		
	}
	return 1;
}




void dataAcquisitionBuffer::addItem(double  data, double timestamp){

	int index=addValueAndGetCurrentIndexIfValidTimestamp(timestamp);

	if(index>=0)
		dataBufferReal[index]=data;
	else
		cout << "Error: could not insert to buffer" << endl;



}

void dataAcquisitionBuffer::addItems(std::vector<double>  data, std::vector<double> timestamp)
{
	if(data.size()!=timestamp.size())
		return;

	int index;
	for(int i=0; i<data.size();i++)
	{
		index=addValueAndGetCurrentIndexIfValidTimestamp(timestamp[i]);
		if(index>=0)
			dataBufferReal[index]=data[i];
	}
}


void dataAcquisitionBuffer::addItems(std::vector<double> data, double startTime, int samplingRate)
{
	int index;
	double time;
    //startTime = startTime*1.0 ;
    //samplingRate = 2 ;
    for(int i=0; i<data.size();i++)
	{
        time=startTime+(double)i/(double)samplingRate;
        //std::cout << "Time de grabacion item: " << i << "- "<< (double)time << "-" << (double)startTime << "-" << (double)i/(double)samplingRate << std::endl ; //Agregado por mi.
        //printf("%f\n",time);

		index=addValueAndGetCurrentIndexIfValidTimestamp(time);
        //qDebug() << "Index obtenido:" << index ;
        if(index>=0)
			dataBufferReal[index]=data[i];//getLastTimeStamp();//
			
	}
}
