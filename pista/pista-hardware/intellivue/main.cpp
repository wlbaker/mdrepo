#include <QCoreApplication>
//#include "protocolCommands.h"
//#include "UDPStructures.h"
#include "udpcommunication.h"
#include <vector>

using namespace std;
//#include <QDebug>
//class UDPCommunication;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	timeReference * time_reference=new timeReference();
	time_reference->initializeTimeReference();
	vector<int> waveIDs;
	vector<int> numericIDs;
    //This vector holds PhysIds you want to get from Intellivue
    //One vector for waves and another for numerical data.
    //You may want to get more PhysIds, but you must pay attention to
    //some constraints that are defined on Intellivue Data Export Guide.
	waveIDs.push_back(18964);//ART
	waveIDs.push_back(258);//ECG Lead II
	waveIDs.push_back(19012);//CVP
	waveIDs.push_back(0x4bb4);//Plethysmograph
	waveIDs.push_back(0x50f0);//Airway Pressure Wave

	numericIDs.push_back(0x4182);//Heart rate
    
	UDPCommunication udp_communication(waveIDs, numericIDs, time_reference, &a);
    return a.exec();
}
