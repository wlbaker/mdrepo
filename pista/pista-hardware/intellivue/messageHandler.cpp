#include "messageHandler.h"
#include <unistd.h>


messageHandler::messageHandler(timeReference * time_ref, QObject* parent) : QObject(parent)
{
	time_reference=time_ref;
	startTime = time_reference->getCurrentTimeSample();
	callFunctionAdded=false;
	signalMapper = new QSignalMapper(this);
	connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(sendDatagram(int)));
	
}

messageHandler::~messageHandler(void)
{
}

bool messageHandler::connectToSocket(int clientPort, int serverPort)
{
	currentPort=serverPort;
	udpSocket= new QUdpSocket(this);
	bool success = udpSocket->bind(serverPort);
	if(success)
	{
		qDebug() << "Connection to port "<< udpSocket->localPort() <<", at" << udpSocket->localAddress()  << "succeeded.";
		
		success = connect(udpSocket, SIGNAL(readyRead()), this, SLOT(receiveDatagram()));
		qDebug() << "Signal connection: " << success;
	}
	else
		qDebug() << "Connection to port "<< currentPort <<", at" << currentIP  << "failed.";
	
	return success;
}

void messageHandler::disconnectFromSocket()
{
	delete udpSocket;
}
void messageHandler::addPendingMessage(string messageID, QByteArray byteArray, double delay, double rate, double duration)
{
	
    usleep(delay*1000);
	
	double t0 = time_reference->getCurrentTimeSample();
	/*
	while((time_reference->getCurrentTimeSample()-t0)<delay)
	{
		Sleep(1);
	}
	*/
	messageIDs.push_back(messageID);
	datagrams.push_back(byteArray);
	startTimes.push_back(t0);
	durations.push_back(duration);
	rates.push_back(rate);
	timers.push_back(new QTimer(this));

	int id = findID(messageID);
	bool singleShot;
	sendDatagram(id);
	
	if(rate==-1)
	{
		//qDebug() << QString::fromUtf8(messageID.c_str(), messageID.size())<< " sendt once";
		return;
	}
	
	singleShot=false;
	
	timers[id]->setSingleShot(singleShot);
	//qDebug() << "sending at rate: " << rate << " successfull: "	<<	
	
    signalMapper->setMapping(timers[id], id);
 
    connect(timers[id], SIGNAL(timeout()), signalMapper, SLOT(map()));

    //connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(sendDatagram(int)));
	//connect(timers[id], SIGNAL(timeout()), this, SLOT(sendDatagram(id)));
	
	timers[id]->start((double)1000/rate);

	//qDebug() << QString::fromUtf8(messageID.c_str(), messageID.size()) << " sendt at rate: " << rate;



	//activeSending=1;
}
void messageHandler::setCallFunction(UDPCommunication * udp_com)
{
	udp_communication=udp_com;
	//*callFunction(QByteArray)=&func;
	//callFunction = UDPCommunication::*readPendingDatagrams;
	//void (*funcPtr)(QByteArray) = func; 
	callFunctionAdded=true;
}

void messageHandler::removePendingMessage(string messageId)
{
	int id=findID(messageId);
	messageIDs.erase(messageIDs.begin()+id);
	datagrams.erase(datagrams.begin()+id);
	startTimes.erase(startTimes.begin()+id);
	durations.erase(durations.begin()+id);
	rates.erase(rates.begin()+id);
	timers[id]->stop();
	disconnect(timers[id], SIGNAL(timeout()), this, SLOT(sendDatagram(id)));
	timers.erase(timers.begin()+id);
}

void messageHandler::sendMessage(string messageID, QByteArray byteArray, double delay, double rate, double duration)
{

	addPendingMessage(messageID, byteArray, delay, rate, duration);
}

int messageHandler::findID(string messageId)
{
	deque<string>::iterator it;
	it = std::find(messageIDs.begin(), messageIDs.end(), messageId);
	int ID = std::distance(messageIDs.begin(), it);
	return ID;
}


void messageHandler::sendDatagram(int ID)
{
	qDebug()<< time_reference->getCurrentTimeSample()-startTime << " SENDING DATAGRAM:"<<ID <<QString::fromUtf8(messageIDs[ID].c_str(), messageIDs[ID].size()) << ". Size: "<<
	//datagrams[ID].size() <<
	udpSocket->writeDatagram(datagrams[ID], QHostAddress("69.255.114.25"), currentPort);
	this;
}

void messageHandler::stopSendingMessage(string messageID)
{
	removePendingMessage(messageID);
}

QByteArray messageHandler::receiveDatagram()
{
	QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    datagram.resize(udpSocket->pendingDatagramSize());
    udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
	qDebug() << time_reference->getCurrentTimeSample()-startTime <<" RECEIVED datagram of size: " << datagram.size();
	if(callFunctionAdded)
		udp_communication->readPendingDatagrams(datagram);//callFunction(datagram);

	return datagram;
}
