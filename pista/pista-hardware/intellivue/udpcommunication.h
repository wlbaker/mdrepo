#ifndef UDPTRANSMISSION_H
#define UDPTRANSMISSION_H
#include <QObject>
//#include <QtNetwork/QUdpSocket>
//#include <QtNetwork/qtcpsocket.h>
#include "protocolCommands.h"
#include "UDPStructures.h"
#include "qtimer.h"
//#include <Windows.h>
//#include "Utils\igstkRealTimeClock.h"
#include <string>
#include <iostream>
#include <QString>
#include <vector>
#include "messageHandler.h"
#include "dataAcquisitionBuffer.h"
#include "timeReference.h"
#include "InfluxDBAccessor.h"
using namespace std;

#define TO_STREAM(stream,variable) (stream) <<#variable": "<<(variable)
class messageHandler;


/*
const int philipsNumericIDs[]=
{
	0x4a11,//OR 15,16,17. ABP - syst
	0x4a12,//diast
	0x4a13,//mean
	0x4dbc,//CCO
	0x4b04,//CO
	0x4182,//HR
	0x4b84,//SV
	0x4a45,//CVP - syst
	0x4a46,//diast
	0x4a47,//mean
	0x4bb8,//AOS
	0x5109,//PIP
	0x51a8//PEEP
};
const int philipsWaveIDs[]=
{
	0x4a14,//OR 14//ART10			18964
	0x0102,//ECG Lead II			258
	0x4a44,//CVP					19012
	0x4bb4,//Plethysmograph			19380
	0x50f0,//Airway Pressure Wave	20720
	0x4A48//SYNCH!					19016
};
*/


class UDPCommunication: public QObject
{
    Q_OBJECT
private:
	struct waveAttributes
	{
		OIDType physio_id;
		TextId text_id;
		OIDType unit;
		RelativeTime sampling_period;
		ScaleRangeSpec16* scale;
	};
	vector<int> wantedWaveIDs;
	vector<int> wantedNumericIDs;
	vector<waveAttributes> wave_attributes;
    QScopedPointer<InfluxDBAccessor> accessor;
	messageHandler* message_handler;
	
	enum communicationState
	{
		CONNECTING,
		CONNECTED,
		ASSOCIATION_REQUESTED,
		ASSOCIATION_CONFIRMED,
		WAITING_MDS_CREATE_EVENT_REPORT,
		MDS_CREATE_EVENT_REPORT_CONFIRMED,
		MDS_CREATE_EVENT_RESULT_SENT,
		POLL_DATA_REQUESTED,
		WAITING_POLL_DATA_RESPONSE,
		ASSOCIATION_RELEASE_REQUEST_SENT,
		WAITING_ASSOCIATION_RELEASE_RESULT,
		ERROR_MESSAGE,
		GET_PRIORITY_LIST_REQUESTED,
		GET_PRIORITY_LIST_RECEIVED,
		SET_PRIORITY_LIST_REQUESTED,
		SET_PRIORITY_LIST_CONFIRMED
	} communication_state;
	double startTime;
	ManagedObjectId *MDSCreateEventMngdObjId;
	RelativeTime MDSCreateEventMngdTime;
	quint16 MDSCreateEventMngdInvoke_id;
	int testBool;
	double receptionTime;
	QTimer timer;
	QByteArray pendingDatagram;
	int currentPort;
	QHostAddress currentAddress;
	int sendRate;
	bool activeSending;
	communicationState state;
	std::vector<dataAcquisitionBuffer*> waveBuffers;
	std::vector<dataAcquisitionBuffer*> numericBuffers;
	void setMeasurementsSetup();
	timeReference* time_ref;
	bool firstData;
public:
	std::vector<dataAcquisitionBuffer*> getWaveBuffers(){return waveBuffers;}
	std::vector<dataAcquisitionBuffer*> getNumericBuffers(){return numericBuffers;}
	//dataAcquisitionBuffer* getBuffer(int index){return buffers[index];}
    explicit UDPCommunication(vector<int> waveIDs, vector<int> numericIDs, timeReference* time_reference, QObject *parent=0);
    QUdpSocket *connectIndicationSocket;
	QUdpSocket *readSocket;
	QUdpSocket *writeSocket;
    QHostAddress connectIndicationAddress;
    QHostAddress associationAddress;
    int connectIndicationPort;
    int associationPort;
    ConnectIndication * CI;
	//void processOIDType(EventReportArgument & event_report_argument, QDataStream & converter,quint16 invoke_id);
	//void processOIDType(OIDType id, QDataStream &converter);

    //Association request
	void establishLogicalConnection();
	QByteArray constructDefARDatagram();
    QByteArray constructARSessionData();
    QByteArray constructARPresentationTrailer();
    QByteArray constructARReqUserData();
    QByteArray constructARPresenationHeader(quint8 length);
    QByteArray constructARSessionHeader(quint8 length);
	void processDataExportPacket(quint8 session_id, QDataStream &converter);
	QByteArray constructSinglePollDataRequest();
	QByteArray constructExtendedPollDataRequest();
	QByteArray constructGetPriorityListRequest();
	QByteArray constructSetPriorityListRequest();
	QByteArray constructGetWaveAttributesRequest();
    int initializeAssociationPort(ConnectIndication *CI);
	void processEventReportResult(QDataStream & converter);
	void setMDSCreateEventParameters(quint16 invoke_id, ManagedObjectId managed_object_id, RelativeTime time)
	{
		MDSCreateEventMngdInvoke_id=invoke_id;
		MDSCreateEventMngdObjId=new ManagedObjectId();
		MDSCreateEventMngdTime=time;
	};
	void getMDSCreateEventParameters(quint16 &invoke_id, ManagedObjectId& managed_object_id, RelativeTime& time)
	{
		invoke_id=MDSCreateEventMngdInvoke_id;
		managed_object_id=*MDSCreateEventMngdObjId;
		time=MDSCreateEventMngdTime;

	};
	void processPollMdibDataReplyExt(PollMdibDataReplyExt* poll_mdib_data_reply_ext);
	void processPollMdibDataReply(PollMdibDataReply* poll_mdib_data_reply);
	void processPollInfoList(PollInfoList* poll_info_list, int poll_type, RelativeTime time_stamp);
	
	
	//void sendMDSCreateEventResult();
	QByteArray constructMDSCreateEventResult();
		void sendAssociationRequest(QByteArray AR);
	void setState(communicationState newState)
	{
		state=newState;
	}
	communicationState getState()
	{
		//TO_STREAM(std::cout, state);
		return state;		
	};
	std::string getStateName()
	{
        switch( state )
		{
		case CONNECTING:
			return "CONNECTING";
			break;
		case CONNECTED:
			return "CONNECTED";
			break;
		case ASSOCIATION_REQUESTED:
			return "ASSOCIATION_REQUESTED";
			break;
		case ASSOCIATION_CONFIRMED:
			return "ASSOCIATION_CONFIRMED";
			break;
		case WAITING_MDS_CREATE_EVENT_REPORT:
			return "WAITING_MDS_CREATE_EVENT_REPORT";
			break;
		case MDS_CREATE_EVENT_REPORT_CONFIRMED:
			return "MDS_CREATE_EVENT_REPORT_CONFIRMED";
			break;
		case MDS_CREATE_EVENT_RESULT_SENT:
			return "MDS_CREATE_EVENT_RESULT_SENT";
			break;
		case POLL_DATA_REQUESTED:
			return "POLL_DATA_REQUESTED";
			break;
		case WAITING_POLL_DATA_RESPONSE:
			return "WAITING_POLL_DATA_RESPONSE";
			break;
		case ASSOCIATION_RELEASE_REQUEST_SENT:
			return "ASSOCIATION_RELEASE_REQUEST_SENT";
			break;
		case WAITING_ASSOCIATION_RELEASE_RESULT:
			return "WAITING_ASSOCIATION_RELEASE_RESULT";
			break;
		case ERROR_MESSAGE:
			return "ERROR_MESSAGE";
			break;
		default:
			return "!!NO STATE!!";
			break;
		}
		

	};
	void actAccordingToState();
	TextId physioOIDTypeToTextId(OIDType type)
	{
		switch(type)
		{
			//Waves
		case(0x4A17):
		case(0x4A16):
		case(0x4A15):
		case(0x4a14):
			return 0x00024A14;
		case(0x0102):
			return 0x00020102;
		case(0x4a44):
			return 0x00024A44;
		case(0x4bb4):
			return 0x00024BB4;
		case(0x50f0):
			return 0x000250F0;
		case(0x4A48):
			return 0x00024A48;
		default:
			return 0;
			//Numerics
			/*
		case(0x4a11):
			return 0x00024A10;
		case(0x4a12):
			return 0x00024A10;
		case(0x4a13):
			return 0x00024A10;
		case(0x4dbc):
			return 0x00024A10;
		case(0x4b04):
			return 0x00024A10;
		case(0x4182):
			return 0x00024A10;
		case(0x4b84):
			return 0x00024A10;
		case(0x4a45):
			return 0x00024A10;
		case(0x4a46):
			return 0x00024A10;
		case(0x4a47):
			return 0x00024A10;
		case(0x4bb8):
			return 0x00024A10;
		case(0x5109):
			return 0x00024A10;
		case(0x51a8):
			return 0x00024A10;
			*/
		}

	};
	OIDType physioTextIdToOIDType(TextId  type)
	{
		switch(type)
		{
			//Waves
		case(0x00024a14):
			return 0x4A14;
		case(0x00020102):
			return 0x0102;
		case(0x00024a44):
			return 0x4A44;
		case(0x00024bb4):
			return 0x4BB4;
		case(0x000250f0):
			return 0x50F0;
		case(0x00024A48):
			return 0x4A48;
		default:
			return 0;
		}

	};
public slots:
    void readPendingDatagrams(QByteArray);
};

#endif // UDPTRANSMISSION_H
