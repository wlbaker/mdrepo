#pragma once
#include <string>
#include <deque>
#include <QByteArray>
#include <QtNetwork/QUdpSocket>
#include <qtimer.h>
//#include <Windows.h>
#include "igstkRealTimeClock.h"
#include "timeReference.h"
#include <QObject>
#include "udpcommunication.h"
#include <QSignalMapper>

class UDPCommunication;

using namespace std;
class messageHandler: public QObject
{
	Q_OBJECT
private:
	double startTime;
	//deque<double> delays;
	deque<string> messageIDs;
	deque<QByteArray> datagrams;
	deque<double> startTimes;
	deque<double> durations;
	deque<double> rates;
	deque<QTimer*> timers;
	QUdpSocket * udpSocket;
	int currentPort;
	QHostAddress currentIP;
	UDPCommunication * udp_communication;
	//void (UDPCommunication::*readPendingDatagrams)(QByteArray); 
	//void (UDPCommunication::*callFunction)(QByteArray); 

	bool callFunctionAdded;
	int findID(string messageId);
	void addPendingMessage(string messageID, QByteArray byteArray, double delay, double rate, double duration);
	void removePendingMessage(string messageId);
	QSignalMapper* signalMapper;
	timeReference *time_reference;
public:
	messageHandler(timeReference *time_ref, QObject *parent=0);
	~messageHandler(void);
	void setCallFunction(UDPCommunication * udp_com);

	bool connectToSocket(int clientPort, int serverPort);
	void disconnectFromSocket();
	void sendMessage(string messageID, QByteArray byteArray, double delay, double rate, double duration);
	void stopSendingMessage(string messageID);
	
public slots:
	
	QByteArray receiveDatagram();
	void sendDatagram(int ID);
};

