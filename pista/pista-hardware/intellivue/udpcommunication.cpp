#include "udpcommunication.h"
#include "InfluxDBAccessor.h"
#include <iomanip>

//#include <inttypes.h>

//ConnectIndication * initConnectIndication(QByteArray);

UDPCommunication::UDPCommunication(vector<int> waveIDs, vector<int> numericIDs, timeReference * time_reference, QObject* parent) : QObject(parent)
{

	firstData=true;
    accessor.reset(new InfluxDBAccessor);
    for(int i=0; i<waveIDs.size(); i++)
	{
		waveAttributes attribute;
		attribute.physio_id = waveIDs[i];
		attribute.text_id = physioOIDTypeToTextId(waveIDs[i]);
		wave_attributes.push_back(attribute);
	}
	wantedWaveIDs.assign(waveIDs.begin(), waveIDs.end());
	time_ref=time_reference;
	int bufferSize=10000;
	for(int i=0; i<wantedWaveIDs.size(); i++)
	{
		waveBuffers.push_back(dataAcquisitionBuffer::New(bufferSize));
	}

	wantedNumericIDs.assign(numericIDs.begin(), numericIDs.end());
	for(int i=0; i<wantedNumericIDs.size(); i++)
	{
		numericBuffers.push_back(dataAcquisitionBuffer::New(bufferSize));
	}

	message_handler= new messageHandler(time_reference, this);
	message_handler->setCallFunction(this);
	

    //setState(this->communicationState::CONNECTED);

    setState(CONNECTED);
	message_handler->connectToSocket(24205,24105);
	this->actAccordingToState();

    //setState(CONNECTING);
	//message_handler->connectToSocket(24205, 24005);
	//actAccordingToState();

}

int UDPCommunication::initializeAssociationPort(ConnectIndication *CI){

	int port = CI->getIndicationPort();

	if(port>=0)
	{
		qDebug() << "Association port: " << port;
		return port;

	}
	else
	{
		return -1;
		qDebug() << "Association port could not be found";
	}

}

void UDPCommunication::readPendingDatagrams(QByteArray datagram)
{
	/*
	receptionTime=igstk::RealTimeClock::GetTimeStamp();
	
	activeSending=0;
	timer.stop();
	//qDebug() << "-------------Pending datagrams-------------: " << writeSocket->hasPendingDatagrams();
	QByteArray datagram;
    QHostAddress sender;
    quint16 senderPort;
    datagram.resize(writeSocket->pendingDatagramSize());
    writeSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
	qDebug() << receptionTime -startTime<< ": RECEIVED datagram at state " << QString::fromStdString(getStateName()) << ". Size: " <<datagram.size();
	*/
	QDataStream converter(datagram);
	//converter.QDataStream::setByteOrder(QDataStream::LittleEndian);
	//SessionHeader session_header(converter);
	quint8 headerType;// = session_header.getType();
	AssociationResponse* association_response;
	ConnectIndication * CI;
	QByteArray ci;
	quint8 byte;
	int newPort;
	int size=datagram.size();

	converter>>headerType;
	//qDebug() << "Type: " << headerType;
	switch(headerType){
	case 0://Connect indication
		
		converter>>byte;
		if(byte!=0)
			return;
		converter>>byte;
		if(byte!=1)
			return;
		converter>>byte;
		if(byte!=0)
			return;

		CI = new ConnectIndication(converter, size);
		newPort= CI->getIndicationPort();
		if(newPort>=0)
		{
			message_handler->disconnectFromSocket();
			message_handler->connectToSocket(24205,newPort);
            setState(CONNECTED);
		}
		//ci = CI->getConnectIndication();
			break;
	case CN_SPDU_SI:

		//qDebug() << "Session Connect header";

		
		break;
	case AC_SPDU_SI:
		
		association_response = new AssociationResponse(converter,0);
		//association_response->print();
		//association_response->
		//setNegotiatedParameters(int max_mtu_rx, int max_mtu_tx, int min_poll_period);
		//qDebug() << "Session Accept header";
		//REMEMBER TO SET MAXIMUM PACKET SIZE ETC HERE!
		//association_response->print();
		//if(getState() == ASSOCIATION_REQUESTED)
			setState(ASSOCIATION_CONFIRMED);
		break;
	case RF_SPDU_SI:
		//qDebug() << "Session Refuse header";
		break;
	case FN_SPDU_SI:
		//qDebug() << "Session Finish header";
		break;
	case DN_SPDU_SI:
		//qDebug() << "Session Disconnect header";
		break;
	case AB_SPDU_SI:
		//qDebug() << "Session Abort header";
		break;
	case DE_PROT:
		//qDebug() << "Data Export Protocol";
		processDataExportPacket(headerType, converter);
		break;
	}
	
	actAccordingToState();
}

void UDPCommunication::actAccordingToState()
{
	//qDebug() << "actAccordingToState. State: " ;
	communicationState state=getState();
	QByteArray byteArray;
	QString *qString;
	switch(state)
	{
        case communicationState::CONNECTED:
		//qDebug() <<"CONNECTED";
		byteArray = constructDefARDatagram();
		message_handler->sendMessage("Association request", byteArray, 1,1, -1);
		setState(communicationState::ASSOCIATION_REQUESTED);
		break;
	case communicationState::CONNECTING:
		//qDebug() <<"CONNECTING";
		break;
	case communicationState::ASSOCIATION_REQUESTED:
		//qDebug() <<"ASSOCIATION_REQUESTED";
		break;
	case communicationState::ASSOCIATION_CONFIRMED:
		//qDebug() <<"ASSOCIATION_CONFIRMED";
		message_handler->stopSendingMessage("Association request");
		setState(WAITING_MDS_CREATE_EVENT_REPORT);
		break;

	case communicationState::WAITING_MDS_CREATE_EVENT_REPORT:
		//qDebug() <<"WAITING_MDS_CREATE_EVENT_REPORT";
		break;
	case communicationState::MDS_CREATE_EVENT_REPORT_CONFIRMED:
		//qDebug() <<"MDS_CREATE_EVENT_REPORT_CONFIRMED";
		byteArray = constructMDSCreateEventResult();
		message_handler->sendMessage("MDS create event result", byteArray, 1, -1,0);

		setState(MDS_CREATE_EVENT_RESULT_SENT);

	case communicationState::MDS_CREATE_EVENT_RESULT_SENT:
		//qDebug() <<"MDS_CREATE_EVENT_RESULT_SENT";
		byteArray=this->constructSetPriorityListRequest();
		setState(SET_PRIORITY_LIST_REQUESTED);
		message_handler->sendMessage("Set priority list request", byteArray, 1, -1,0);


		break;
	case communicationState::POLL_DATA_REQUESTED:
		//qDebug() <<"POLL_DATA_REQUESTED";
		break;
	case communicationState::WAITING_POLL_DATA_RESPONSE:
		//qDebug() <<"WAITING_POLL_DATA_RESPONSE";
		break;
	case communicationState::ASSOCIATION_RELEASE_REQUEST_SENT:
		//qDebug() <<"ASSOCIATION_RELEASE_REQUEST_SENT";
		break;
	case communicationState::WAITING_ASSOCIATION_RELEASE_RESULT:
		//qDebug() <<"WAITING_ASSOCIATION_RELEASE_RESULT";
		break;
	case communicationState::ERROR_MESSAGE:
		//qDebug() << "ERROR!!!";
		break;
	case communicationState::GET_PRIORITY_LIST_REQUESTED:
		//qDebug() << "GET_PRIORITY_LIST_REQUESTED";
		break;
	case communicationState::GET_PRIORITY_LIST_RECEIVED:
		//qDebug() << "GET_PRIORITY_LIST_RECEIVED";
		//byteArray=this->constructGetWaveAttributesRequest();
		//message_handler->sendMessage("Get wave attributes", byteArray, 1, -1,0);
		
		byteArray = constructExtendedPollDataRequest();
		//qDebug() << "bytearray size: " << byteArray.size() <<", " << byteArray;
		message_handler->sendMessage("Extended poll data request", byteArray, 1, (double)1/5.0,0);

		//byteArray = constructSinglePollDataRequest();
		//message_handler->sendMessage("Single poll data request", byteArray, 1, (double)1,0);
		setState(WAITING_POLL_DATA_RESPONSE);
		
		break;
	case communicationState::SET_PRIORITY_LIST_REQUESTED:
		//qDebug() << "SET_PRIORITY_LIST_REQUESTED";
		break;
	case communicationState::SET_PRIORITY_LIST_CONFIRMED:
		//qDebug() << "SET_PRIORITY_LIST_CONFIRMED";
		byteArray= this->constructGetPriorityListRequest();
		message_handler->sendMessage("Get priority list request", byteArray, 1, -1,0);
		//byteArray=constructGetWaveAttributesRequest();
		//message_handler->sendMessage("Get Wave Attribute request", byteArray, 1, -1,0);
		setState(GET_PRIORITY_LIST_REQUESTED);
		
		break;
	}
}

void UDPCommunication::processDataExportPacket(quint8 tmp, QDataStream &converter)
{
	QByteArray byteArray;
	appendData(byteArray, tmp);
	quint8 tmp2;
	converter >> tmp2;
	appendData(byteArray, tmp2);
	QDataStream conv(byteArray);
	
	quint16 sessionID;
	conv >> sessionID;

	quint16 contextID;
	converter >> contextID;
	SPpdu sp_pdu(sessionID, contextID);
	//sp_pdu.print();
	int size=0;
	ROapdus ro_apdus(converter, size);
	quint16 type=ro_apdus.getRoType();
	//ro_apdus.print();
	
	ROIVapdu roiv_apdu;
	RORSapdu rors_apdu;
	ROERapdu roer_apdu;
	ROLRSapdu rolrs_apdu;
	ActionResult action_result;
	MDSCreateInfo mds_create_info;
	EventReportArgument* event_report_argument;
	ProcessingFailure processing_failure;
	QByteArray single_poll_data_req;
	RelativeTime time;
	CMDType CMD_type;
	OIDType id;
	Object* object;
	EventReportResult* event_report_result;
	GetArgument* get_argument;
	SetArgument* set_argument;
	GetResult* get_result;
	SetResult* set_result;

	int length;
	switch(type)
	{
	case ROapdus::ROIV_APDU:
		//qDebug() << "ROIV_APDU-Remote Operation Invoke" << endl;
		roiv_apdu=ROIVapdu(converter, size);
		
		CMD_type=roiv_apdu.getType();
		event_report_argument=new EventReportArgument(converter, size);
		//event_report_arg->print();
		
		length=event_report_argument->getLength();
		time = event_report_argument->getEventTime();
		startTime=time/8000-this->time_ref->getCurrentTimeSample();
		if(firstData)
		{
			for(int i=0; i<waveBuffers.size(); i++)
				waveBuffers[i]->setTimeDifference(startTime);

			for(int i=0; i<numericBuffers.size(); i++)
				numericBuffers[i]->setTimeDifference(startTime);
			//firstData=false;
		}

		id=event_report_argument->getEventType();
		if(id==Object::NOM_NOTI_MDS_CREAT)
		{
			mds_create_info = MDSCreateInfo(converter, size);
			setMDSCreateEventParameters(roiv_apdu.getInvokeID(), mds_create_info.getManagedObject(), time);
			setState(communicationState::MDS_CREATE_EVENT_REPORT_CONFIRMED);
		}
		//qDebug() << "OID type:" << id << ". Size: " << size;

		//processOIDType(*event_report_arg, converter, ROapdus::ROIV_APDU);
		break;
	case ROapdus::RORS_APDU:
		//qDebug() << "RORS_APDU-Remote Operation Result";
		rors_apdu=RORSapdu(converter, size);
		//rors_apdu.print();
		switch(rors_apdu.getCMDType())
		{
		case(CMD_EVENT_REPORT):
			//qDebug() << "CMD_EVENT_REPORT";
			event_report_argument=new EventReportArgument(converter, size);
			break;
		case(CMD_CONFIRMED_EVENT_REPORT):
			//qDebug() << "CMD_CONFIRMED_EVENT_REPORT";
			event_report_result= new EventReportResult(converter, size);
			//event_report_result->print();
			break;
		case(CMD_GET):
			//qDebug() << "CMD_GET";
			get_result =  new GetResult(converter, size);
			//get_result->print();
			setState(GET_PRIORITY_LIST_RECEIVED);
			break;
		case(CMD_SET):
			//qDebug() << "CMD_SET";
			set_argument = new SetArgument(converter, size);
			break;
		case(CMD_CONFIRMED_SET):
			//qDebug() << "CMD_CONFIRMED_SET";
			set_result = new SetResult(converter, size);
			if(this->getState()==communicationState::SET_PRIORITY_LIST_REQUESTED)
				setState(communicationState::SET_PRIORITY_LIST_CONFIRMED);
			break;
		case(CMD_CONFIRMED_ACTION):
			//qDebug() << "CMD_CONFIRMED_ACTION";
			action_result=ActionResult(converter, size);
			//action_result.print();
			object = new Object(action_result.getActionType(),action_result.getLength(), converter);
			if(object->getID()==Object::NOM_ACT_POLL_MDIB_DATA_EXT)
				processPollMdibDataReplyExt((PollMdibDataReplyExt*)object->getAttribute());
			else if(object->getID()==Object::NOM_ACT_POLL_MDIB_DATA)
				processPollMdibDataReply((PollMdibDataReply*)object->getAttribute());
			//object->print();
			break;
		}
		break;
	case ROapdus::ROER_APDU:
		//qDebug() << "ROER_APDU-Remote Operation Error";
		roer_apdu= ROERapdu(converter, size);
		roer_apdu.getErrorValue();
		//roer_apdu.print();
		//roer_apdu.getErrorValue();
		processing_failure=ProcessingFailure(converter, size);
		qDebug() << "processing failure ID: " << processing_failure.getID();
		if(processing_failure.getLength()>0)
		{
			qDebug() <<"Appended error information: ";
		}
		else
			qDebug() << "No appended error information";
		
		//setState(communicationState::ERROR_MESSAGE);
		//setState(communicationState::MDS_CREATE_EVENT_REPORT_CONFIRMED);
		//single_poll_data_req = this->constructSinglePollDataRequest();
		//sendDatagram(single_poll_data_req, 10, 1,"single_poll_data_req");
		
		break;
	case ROapdus::ROLRS_APDU:
		//qDebug() << "ROLRS_APDU-Remote Operation Linked Result";
		rolrs_apdu=ROLRSapdu(converter, size);
		
		action_result=ActionResult(converter, size);
		//action_result.print("ActionResult");
		object = new Object(action_result.getActionType(),action_result.getLength(), converter);
		if(object->getID()==Object::NOM_ACT_POLL_MDIB_DATA_EXT)
			processPollMdibDataReplyExt((PollMdibDataReplyExt*)object->getAttribute());
		else if(object->getID()==Object::NOM_ACT_POLL_MDIB_DATA)
			processPollMdibDataReply((PollMdibDataReply*)object->getAttribute());

		//if(action_result.getActionType()==Object::NOM_ACT_POLL_MDIB_DATA)
		//	(PollInfoList*)object->getAttribute();

		//object->print("object:");
		
		break;
	default:
		qDebug() << "no recognized type";
	}
	
}

void UDPCommunication::processEventReportResult(QDataStream & converter)
{
	int size=0;
	EventReportArgument event_report_arg(converter, size);
	OIDType event_type=event_report_arg.getEventType();
	qDebug() << event_type;

}


QByteArray UDPCommunication::constructMDSCreateEventResult()
{
	quint16 invoke_id;
	ManagedObjectId managed_object_id;
	RelativeTime time;
	this->getMDSCreateEventParameters(invoke_id, managed_object_id, time);

	SPpdu sp_pdu(0xE100,2);//???
	ROapdus ro_apdus(ROapdus::RORS_APDU, 0x0014);//20
	RORSapdu rors_apdu(invoke_id, CMD_CONFIRMED_EVENT_REPORT, 0x000E);//14
    GlbHandle *esteHandle = new GlbHandle(0,0);
	ManagedObjectId managed_object_id2(Object::NOM_MOC_VMS_MDS, *esteHandle);
	double timeDiff=time_ref->getCurrentTimeSample();
	EventReportResult event_report_result(managed_object_id2, time+timeDiff/8, Object::NOM_NOTI_MDS_CREAT, 0);
	MDSCreateEventResult mds_create_result(sp_pdu, ro_apdus, rors_apdu, event_report_result);
	//mds_create_result.print();
	QByteArray result = mds_create_result.getMDSCreateEventResult();
	
	//sendDatagram(result, -1, 1500, "MDS CREATE EVENT RESULT SENDT");
	return result;
}

QByteArray UDPCommunication::constructExtendedPollDataRequest()
{
	PollDataReqPeriod poll_data_req_period(8*8000);
	void* ptr=(void*)&poll_data_req_period;
	Object object(Object::NOM_ATTR_TIME_PD_POLL, sizeof(RelativeTime), ptr);

	int lengthOfAttrList=1;//0
	AVAType *ava_type;
	ava_type=new AVAType[lengthOfAttrList];
	ava_type[0]= AVAType(Object::NOM_ATTR_TIME_PD_POLL, sizeof(RelativeTime), object);
	AttributeList attribute_list(lengthOfAttrList,ava_type[0].getSize()/*0*/, ava_type, "zero attribute");
	
	TYPE type(TYPE::NOM_PART_OBJ, Object::NOM_MOC_VMO_METRIC_SA_RT);
	PollMdibDataReqExt poll_mdib_data_req_ext(1, type, /*Object::NOM_ATTR_GRP_METRIC_VAL_OBS*/0, attribute_list); 
	QByteArray PollMdibDataReqExtBytes=poll_mdib_data_req_ext.getPollMdibDataReqExt();

	int size=0;
	size=size+PollMdibDataReqExtBytes.size();

	GlbHandle glb_handle(0, 0);
	ManagedObjectId managed_object_id(Object::NOM_MOC_VMS_MDS, glb_handle);
	ActionArgument action_argument(managed_object_id, 0, Object::NOM_ACT_POLL_MDIB_DATA_EXT, size);
	QByteArray ActionArgumentBytes=action_argument.getActionArgument();

	size=size+ActionArgumentBytes.size();
	ROIVapdu roiv_apdu(0, CMD_CONFIRMED_ACTION, size);
	QByteArray ROIVapduBytes=roiv_apdu.getROIVapdu();

	size=size+ROIVapduBytes.size();
	ROapdus ro_apdus(ROapdus::ROIV_APDU, size);
	QByteArray ROapdusBytes=ro_apdus.getROapdus();
	
	size=size+ROapdusBytes.size();
	SPpdu sp_pdu(0xE100, 2);
	QByteArray SPpduBytes=sp_pdu.getSPpdu();
	
	QByteArray byteArray;
	appendData(byteArray,SPpduBytes);
	appendData(byteArray,ROapdusBytes);
	appendData(byteArray,ROIVapduBytes);
	appendData(byteArray,ActionArgumentBytes);
	appendData(byteArray,PollMdibDataReqExtBytes);
	return byteArray;

}

QByteArray UDPCommunication::constructSinglePollDataRequest()
{
	QByteArray byteArray;

	SPpdu sp_pdu(0xE100, 2);
	byteArray=appendData(byteArray,sp_pdu.getSPpdu());

	ROapdus ro_apdus(ROapdus::ROIV_APDU, 28);
	byteArray=appendData(byteArray,ro_apdus.getROapdus());

	ROIVapdu roiv_apdu(0, CMD_CONFIRMED_ACTION, 22);
	byteArray=appendData(byteArray,roiv_apdu.getROIVapdu());

	GlbHandle glb_handle(0, 0);

	ManagedObjectId managed_object_id(Object::NOM_MOC_VMS_MDS, glb_handle);

	ActionArgument action_argument(managed_object_id, 0, Object::NOM_ACT_POLL_MDIB_DATA, 8);
	byteArray=appendData(byteArray,action_argument.getActionArgument());

	TYPE type(TYPE::NOM_PART_OBJ, Object::NOM_MOC_VMO_METRIC_NU);

	PollMdibDataReq poll_mdib_data_req(1, type, 0); 
	byteArray=appendData(byteArray,poll_mdib_data_req.getPollMdibDataReq());
	return byteArray;

}

QByteArray UDPCommunication::constructGetWaveAttributesRequest()
{
	QByteArray byteArray;
	
    GlbHandle glb_handle(0, 0);
	ManagedObjectId managed_object_id(Object::NOM_MOC_VMS_MDS, glb_handle);
	quint32 scope=0;
	int numberOfAttributes=1;
	OIDType *oid_values=new OIDType[numberOfAttributes];
	oid_values[1]=Object::NOM_ATTR_TIME_PD_SAMP;
	AttributeIdList attribute_id_list(numberOfAttributes, sizeof(OIDType)*numberOfAttributes, oid_values);

	GetArgument get_argument(managed_object_id, scope, attribute_id_list);
	QByteArray get_argument_BA=get_argument.getGetArgument();
	
	ROIVapdu roiv_apdu( 0, CMD_GET, get_argument_BA.size());
	QByteArray roiv_apdu_BA=roiv_apdu.getROIVapdu();

	ROapdus ro_apdus(ROapdus::ROIV_APDU, get_argument_BA.size()+roiv_apdu_BA.size());
	QByteArray ro_apdus_BA=ro_apdus.getROapdus();

	SPpdu sp_pdu(0xe100,2);
	QByteArray sp_pdu_BA=sp_pdu.getSPpdu();

	byteArray=sp_pdu_BA+ro_apdus_BA+roiv_apdu_BA+get_argument_BA;
	return byteArray;

}


QByteArray UDPCommunication::constructDefARDatagram()
{
	QByteArray ARReqUserData = constructARReqUserData();
    QByteArray ARSessionData = constructARSessionData();
    QByteArray ARPresentationTrailer = constructARPresentationTrailer();
   // int sizeOfSessionData = 14;
    //int sizeOfSessionHeader = 2;
    int sizeOfPresentationHeader = 133;
    //int sizeOfPresentationTrailer = 16;

    int lengthForPresentationHeader = ARReqUserData.size() + ARPresentationTrailer.size() + sizeOfPresentationHeader - 2;
    int lengthForSessionHeader = ARSessionData.size() + sizeOfPresentationHeader + ARReqUserData.size() + ARPresentationTrailer.size();

    QByteArray ARPresentationHeader = constructARPresenationHeader(lengthForPresentationHeader);
    QByteArray ARSessionHeader = constructARSessionHeader(lengthForSessionHeader);

    QByteArray associationRequest = ARSessionHeader + ARSessionData + ARPresentationHeader + ARReqUserData + ARPresentationTrailer;

	return associationRequest;
}

QByteArray UDPCommunication::constructARReqUserData(){
	
	AVAType* null=new AVAType[0];
	AttributeList al(0,0, null);
	PollProfileExt pollprofileext( 0xFF000000/*0xFF(8C)000000*/, al);

	void* pt=(void*)&pollprofileext;
	Object object(Object::NOM_ATTR_POLL_PROFILE_EXT, 8, pt);
	AVAType *option_list1AVAType = new AVAType(Object::NOM_ATTR_POLL_PROFILE_EXT, 8, object); 
	AttributeList option_list(1,12,option_list1AVAType, "option_list1");

	PollProfileSupport poll_profile_support(
		POLL_PROFILE_REV_0,
		0x00000000 ,//800000,//0x00000000(works)
		1500/*0x00000258*/,//0x000003e8,//258(works)
		1500/*0x000002BC*/,
		0x00000000, //0xffffffff,
		0x60000000,
		option_list);

		/*
		0x80000000,
		0x000c3500,
		0x000003e8,
		0x000003e8,
		0xffffffff,
		0x60000000,
		option_list);
		*/
	
	void* ptr=(void*)&poll_profile_support;
	Object object2(Object::NOM_POLL_PROFILE_SUPPORT, 0x0028, ptr);
	AVAType *supported_aprofilesAVAType=new AVAType(Object::NOM_POLL_PROFILE_SUPPORT, 0x0028,  object2);
	AttributeList supported_aprofiles1(1 ,44, supported_aprofilesAVAType, "supported_aprofiles");
	
	ProtocolVersion protocol_version=			0x80000000;
	NomenclatureVersion nomenclature_version=	0x40000000;
	FunctionalUnits functional_units=			0x00000000;
	SystemType system_type=						0x80000000;
	StartupMode startup_mode=					0x20000000;
	AVAType* null2=new AVAType[0];
	AttributeList opt_list(0,0, null2);

	MDSEUserInfoStd *s =new MDSEUserInfoStd(
		protocol_version, 
		nomenclature_version, 
		functional_units, 
		system_type, 
		startup_mode, 
		opt_list, 
		supported_aprofiles1);
	
	QByteArray byteArray= s->getMDSEUserInfoStd();
	quint8 ASNLength=byteArray.size();
	QByteArray length;
	appendData(length, ASNLength);
	//s->print();
	byteArray=length+byteArray;

	//delete s;
	//delete supported_aprofilesAVAType;
	//delete option_list1AVAType;
	//delete null;

	return byteArray;
}

QByteArray UDPCommunication::constructARSessionData()   {
    //Association Request Session Data

    static const char ARSD[]=
    {
        0x05, 0x08, 0x13, 0x01, 0x00, 0x16, 0x01, 0x02,
        0x80, 0x00, 0x14, 0x02, 0x00, 0x02
    };
    QByteArray AssocReqSessionData = QByteArray::fromRawData(ARSD, sizeof(ARSD));

    return AssocReqSessionData;
}

QByteArray UDPCommunication::constructARPresentationTrailer(){
    // Association Presentation Trailer
    static const char ARPT[]=
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    QByteArray AssocReqPresentationTrailer = QByteArray::fromRawData(ARPT, sizeof(ARPT));
    return AssocReqPresentationTrailer;
}

QByteArray UDPCommunication::constructARPresenationHeader(quint8 length){
    //Association Request Presentation Header
    static const char ARPH[] =
    {
        0xC1, length, 0x31, 0x80, 0xA0, 0x80, 0x80, 0x01,
        0x01, 0x00, 0x00, 0xA2, 0x80, 0xA0, 0x03, 0x00,
        0x00, 0x01, 0xA4, 0x80, 0x30, 0x80, 0x02, 0x01,
        0x01, 0x06, 0x04, 0x52, 0x01, 0x00, 0x01, 0x30,
        0x80, 0x06, 0x02, 0x51, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x30, 0x80, 0x02, 0x01, 0x02, 0x06, 0x0C,
        0x2A, 0x86, 0x48, 0xCE, 0x14, 0x02, 0x01, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x30, 0x80, 0x06, 0x0C,
        0x2A, 0x86, 0x48, 0xCE, 0x14, 0x02, 0x01, 0x00,
        0x00, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x61, 0x80, 0x30, 0x80, 0x02, 0x01,
        0x01, 0xA0, 0x80, 0x60, 0x80, 0xA1, 0x80, 0x06,
        0x0C, 0x2A, 0x86, 0x48, 0xCE, 0x14, 0x02, 0x01,
        0x00, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0xBE,
        0x80, 0x28, 0x80, 0x06, 0x0C, 0x2A, 0x86, 0x48,
        0xCE, 0x14, 0x02, 0x01, 0x00, 0x00, 0x00, 0x01,
        0x01, 0x02, 0x01, 0x02, 0x81
    };

    QByteArray AssocReqPresentationHeader = QByteArray::fromRawData(ARPH, sizeof(ARPH));
    return AssocReqPresentationHeader;
}

QByteArray UDPCommunication::constructARSessionHeader(quint8 length){
    //Association Request Session Header
    static const char ARSH[] =
    {
        0x0D, length
    };

    QByteArray AssocReqSessionHeader = QByteArray::fromRawData(ARSH, sizeof(ARSH));

    return AssocReqSessionHeader;
}




QByteArray UDPCommunication::constructGetPriorityListRequest()
{
	SPpdu sp_pdu(0xE100, 2);

	ROapdus ro_apdus(ROapdus::ROIV_APDU, 22);//ro_type := ROIV_APDU

	ROIVapdu roiv_apdu(0,CMD_GET,16);//command_type := CMD_GET

	GlbHandle glb_handle(0,0);
	ManagedObjectId managed_object_id(Object::NOM_MOC_VMS_MDS,glb_handle);

	OIDType * oid_types= new OIDType[1];
	oid_types[0]=Object::NOM_ATTR_POLL_RTSA_PRIO_LIST;//NOM_ATTR_POLL_NU_PRIO_LIST;

	AttributeIdList attribute_id_list(1,2,oid_types);
	GetArgument get_argument(managed_object_id,0, attribute_id_list);//managed_object := {NOM_MOC_VMS_MDS, 0, 0}

	MDSGetPriorityList mds_get_priority_list(sp_pdu, ro_apdus, roiv_apdu, get_argument);

	return mds_get_priority_list.getMDSGetPriorityList();
}

QByteArray UDPCommunication::constructSetPriorityListRequest()
{
	SPpdu sp_pdu(0xE100, 2);

	//SetArgument members:
	GlbHandle glb_handle(0,0);
	ManagedObjectId managed_object(Object::NOM_MOC_VMS_MDS, glb_handle);
	quint32 scope = 0;
	int count=this->wantedWaveIDs.size();
	
	TextId * text_id;
	text_id = new TextId[count];
	for(int i=0; i< count; i++)
	{
		quint16 msb = 0x0002;
		quint16 lsb = (quint16)wantedWaveIDs[i];
		//TextId newVar=0x00020000;
		text_id[i]=(msb<<16)|(lsb&0xffff);
	}

	TextIdList text_id_list(count, count*4, text_id);

	int textIdListSize = text_id_list.getTextIdList().size();
	void* ptr=(void*)&text_id_list;
	Object object(Object::NOM_ATTR_POLL_RTSA_PRIO_LIST, textIdListSize, ptr); 
	AVAType ava_type(Object::NOM_ATTR_POLL_RTSA_PRIO_LIST, textIdListSize, object);
	AttributeModEntry *attribute_mod_entry;
	int numberOfModEntries=1;
	attribute_mod_entry= new AttributeModEntry[numberOfModEntries];
	attribute_mod_entry[0] = AttributeModEntry(REPLACE, ava_type);/*REPLACE*/
	//attribute_mod_entry[1] = AttributeModEntry(SET_TO_DEFAULT, AVAType(Object::NOM_ATTR_TIME_PD_SAMP, 0, Object(0,0, NULL)));/*SET_TO_DEFAULT*/
	int modeEntriesSize=0;
	for(int i=0;i<numberOfModEntries;i++)
		modeEntriesSize+=attribute_mod_entry[i].getSize();

	ModificationList modificationList(numberOfModEntries,modeEntriesSize, attribute_mod_entry);
	SetArgument set_argument(managed_object, scope, modificationList);

	int setArgumentSize=set_argument.getSize();
	ROIVapdu roiv_apdu(0,CMD_CONFIRMED_SET,setArgumentSize);
	ROapdus ro_apdus(ROapdus::ROIV_APDU, setArgumentSize+roiv_apdu.getSize());

	MDSSetPriorityList mds_set_priority_list(sp_pdu, ro_apdus, roiv_apdu, set_argument);

	return mds_set_priority_list.getMDSSetPriorityList();

	/*
	SPpdu sp_pdu(0xE100, 2);

	//SetArgument members:
	GlbHandle glb_handle(0,0);
	ManagedObjectId managed_object(Object::NOM_MOC_VMS_MDS, glb_handle);
	quint32 scope = 0;
	int count=this->wantedWaveIDs.size();
	
	TextId * text_id;
	text_id = new TextId[count];
	for(int i=0; i< count; i++)
	{
		quint16 msb = 0x0002;
		quint16 lsb = (quint16)wantedWaveIDs[i];
		//TextId newVar=0x00020000;
		text_id[i]=(msb<<16)|(lsb&0xffff);
	}

	//text_id[0]=0x00024A10;//NLS_NOM_PRESS_BLD_ART.0x00020102;//NLS_NOM_ECG_ELEC_POTL_II //
	//text_id[1]=0x00020102;
	TextIdList text_id_list(count, count*4, text_id);
	int textIdListSize = text_id_list.getTextIdList().size();
	void* ptr=(void*)&text_id_list;
	Object object(Object::NOM_ATTR_POLL_RTSA_PRIO_LIST, textIdListSize, ptr); 
	AVAType ava_type(Object::NOM_ATTR_POLL_RTSA_PRIO_LIST, textIdListSize, object);
	AttributeModEntry *attribute_mod_entry;
	attribute_mod_entry= new AttributeModEntry[1];
	attribute_mod_entry[0] = AttributeModEntry(0, ava_type);//REPLACE
	ModificationList modificationList(1,attribute_mod_entry[0].getSize(), attribute_mod_entry);
	SetArgument set_argument(managed_object, scope, modificationList);

	int setArgumentSize=set_argument.getSize();
	ROIVapdu roiv_apdu(0,CMD_CONFIRMED_SET,setArgumentSize);
	ROapdus ro_apdus(ROapdus::ROIV_APDU, setArgumentSize+roiv_apdu.getSize());

	MDSSetPriorityList mds_set_priority_list(sp_pdu, ro_apdus, roiv_apdu, set_argument);

	return mds_set_priority_list.getMDSSetPriorityList();
	*/
}

void UDPCommunication::processPollMdibDataReply(PollMdibDataReply* poll_mdib_data_reply)
{
	//poll_mdib_data_reply->print();
	RelativeTime time_stamp = poll_mdib_data_reply->getRelativeTimeStamp();
	if(firstData)
	{
		for(int i=0; i<waveBuffers.size(); i++)
			waveBuffers[i]->setTimeDifference(time_stamp);

		for(int i=0; i<numericBuffers.size(); i++)
			numericBuffers[i]->setTimeDifference(time_stamp);
		firstData=false;
	}
	int polledTypeCode = poll_mdib_data_reply->getPolledObjectType()->getCode();
	processPollInfoList(poll_mdib_data_reply->getPollInfoList(), polledTypeCode, time_stamp);

}
void UDPCommunication::processPollMdibDataReplyExt(PollMdibDataReplyExt* poll_mdib_data_reply_ext)
{
	
	//poll_mdib_data_reply_ext->print();
	RelativeTime time_stamp = poll_mdib_data_reply_ext->getRelativeTimeStamp();
	if(firstData)
	{
		for(int i=0; i<waveBuffers.size(); i++)
			waveBuffers[i]->setTimeDifference((double)time_stamp/8000.0-this->time_ref->getCurrentTimeSample());

		for(int i=0; i<numericBuffers.size(); i++)
			numericBuffers[i]->setTimeDifference((double)time_stamp/8000.0-this->time_ref->getCurrentTimeSample());
		firstData=false;
	}
	int polledTypeCode = poll_mdib_data_reply_ext->getPolledObjectType()->getCode();
	
	processPollInfoList(poll_mdib_data_reply_ext->getPollInfoList(), polledTypeCode, time_stamp);

}

void UDPCommunication::processPollInfoList(PollInfoList* poll_info_list, int poll_type, RelativeTime time_stamp)
{
	
	//poll_info_list->print();
	if(poll_type==Object::NOM_MOC_VMO_METRIC_SA_RT)
	{
		//qDebug() << "NOM_MOC_VMO_METRIC_SA_RT" << endl;
		for(int i=0; i<poll_info_list->getCount();i++)
		{
			int jCount=poll_info_list->getValue(i)->getPollInfoCount();
			for(int j=0; j<jCount;j++)
			{
				ObservationPoll* obs_poll=poll_info_list->getValue(i)->getPollInfoValue(j);
				AttributeList* attribute_list = obs_poll->getAttributes();
	
				// Get physioidentifyer!NOM_ATTR_ID_LABEL
				TextId *physio_id=(TextId*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_ID_LABEL);
				if(physio_id!=NULL)
					for(int i=0; i<wave_attributes.size();i++)
					{
						if(wave_attributes[i].text_id==*physio_id)
						{
							// Get Sampling period. The resolution of theRelativeTimeis 1/8ms (125us).
							RelativeTime *sampling_period=(RelativeTime*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_TIME_PD_SAMP);
							if(sampling_period!=NULL)
								wave_attributes[i].sampling_period=*sampling_period;
							// Get units
							OIDType *unit_code=(OIDType*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_UNIT_CODE);
							if(unit_code!=NULL)
								wave_attributes[i].unit=*unit_code;

							// Get scale info
							ScaleRangeSpec16* scale_range_spec_16=(ScaleRangeSpec16*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_SCALE_SPECN_I16);
							if(scale_range_spec_16!=NULL)
								wave_attributes[i].scale= new ScaleRangeSpec16(*scale_range_spec_16);

						} 
					}


				// Get array
				SaObsValue* sa_obs_value=(SaObsValue*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_SA_VAL_OBS);
				if(sa_obs_value!=NULL)
				{
					OIDType physio_id=sa_obs_value->getPhysioId();
					
					
					for(int i=0; i<wave_attributes.size();i++)
					{
						if(wave_attributes[i].physio_id==physio_id)
						{
                            SampleArray* sample_array=sa_obs_value->getSampleArray();
							int arraySize=sample_array->getSize();
                            //sample_array->print();

                            std::vector<double> newData(sample_array->getDataPointer(), sample_array->getDataPointer()+arraySize);
                            int samplingRate=8000.0/(wave_attributes[i].sampling_period);
                            qDebug() << "Sampling_period: " << wave_attributes[i].sampling_period ;
                            qDebug() << "SamplingRate: " <<  8000/arraySize ;
                            double EstestartTime = ((double)time_stamp/(double)8000);

                            waveBuffers[i]->addItems(newData,((double)time_stamp/(double)8000), samplingRate);
                            qDebug() << waveBuffers[i]->getLastTimeStamp() << " - Wave added Simple. Size: " << newData.size() << endl;
                            qDebug() << wave_attributes[i].physio_id;
                            qDebug() << "time_stamp: "<< time_stamp ;
                            //qDebug() << "time_stamp/8:" << (double)time_stamp/(double)8000 ;
                            //qDebug() << "samplingRate: " << samplingRate ;
                            //qDebug() << "samplingPeriod: "<< wave_attributes[i].sampling_period ;


                            if (wave_attributes[i].physio_id == 258) {
                            std::stringstream salidajson ;
                            salidajson << std::setprecision(5) << std::fixed ;
                            salidajson << "[ { \"name\":" ;
                            //salidajson << "\"" << wave_attributes[i].physio_id << "\"," ;
                            salidajson << "\"" << "ECGII" << "\"," ;
                            salidajson  << "\"columns\":[\"time\",\"values\"],\"points\":[";
                            double offset = 8000.0/arraySize ;

                            //qDebug() << wave_attributes[i].text_id;
                            int j=0;
                            for (std::vector<double>::iterator it = newData.begin() ; it != newData.end(); ++it)
                            {
                                salidajson << "[" << time_stamp+(double)j*(double)offset  << "," << *it << (((it+1) != newData.end()) ? "],":"]") ;
                                j++;
                                double newtime = time_stamp + offset ;
                                //qDebug() << time_stamp;
                                //qDebug() << offset ;
                                //qDebug() << newtime ;
                            }
                            salidajson << "] } ]";
                            std::string estasalida = salidajson.str() ;
                            qDebug() << QString::fromStdString(estasalida) ;
                            const char* outtxt = estasalida.c_str() ;


                            QScopedPointer<QByteArray> dataByteArray(new QByteArray(outtxt));
                            accessor->postData(dataByteArray.data());


                            //dataByteArray->append("\" << wave_attributes[i].physio_id);
                            }

                        }
					}
				}
				//Get array compound
				SaObsValueCmp* sa_obs_value_cmd=(SaObsValueCmp*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_SA_CMPD_VAL_OBS);
				if(sa_obs_value_cmd!=NULL)
				{
					for(int k=0; k<sa_obs_value_cmd->getCount();k++)
					{
						sa_obs_value=sa_obs_value_cmd->getSaObsValue(k);
						OIDType physio_id=sa_obs_value->getPhysioId();
						
						for(int i=0; i<wave_attributes.size();i++)
						{
							if(wave_attributes[i].physio_id==physio_id)
							{
								SampleArray* sample_array=sa_obs_value->getSampleArray();
								int arraySize=sample_array->getSize();
								std::vector<double> newData(sample_array->getDataPointer(), sample_array->getDataPointer()+arraySize);

								int samplingRate=8000.0/(wave_attributes[i].sampling_period);
								//qDebug() << (time_stamp/(double)8000) << " - CMP Wave added - " << i <<": " << newData.size() << endl;
								waveBuffers[i]->addItems(newData,((double)time_stamp/(double)8000), samplingRate);
                                qDebug() << waveBuffers[i]->getLastTimeStamp() << " - Wave added Comp. Size: " << newData.size() << endl;
								break;
								
							}
						}
					}
				}
			}
		}
	}
	else if(poll_type==Object::NOM_MOC_VMO_METRIC_NU)
	{
		//qDebug() << "NOM_MOC_VMO_METRIC_NU" << endl;
		//poll_info_list->print("--------START NUMERICS: PollInfoList:");
		//cout <<"NUMERICS!!!" << endl;
		for(int i=0; i<poll_info_list->getCount();i++)
		{
			int jCount=poll_info_list->getValue(i)->getPollInfoCount();
			for(int j=0; j<jCount;j++)
			{
				ObservationPoll* obs_poll=poll_info_list->getValue(i)->getPollInfoValue(j);
				//if(obs_poll->getAttributes()->==Object::NOM_ATTR_NU_VAL_OBS)
				
				NuObsValue* nu_obs_value=(NuObsValue*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_NU_VAL_OBS);
				if(nu_obs_value!=NULL)
				{
					int physio_id = nu_obs_value->getPhysioId();
					int value = nu_obs_value->getActualValue();
					for(int i=0; i<wantedNumericIDs.size(); i++)
					{
						if(wantedNumericIDs[i]==physio_id)
						{
							numericBuffers[i]->addItem(value,time_stamp/8000);
							qDebug() << numericBuffers[i]->getLastTimeStamp() << " - Numeric added." << endl;
						}
					}
				}
				NuObsValueCmp * nu_obs_value_cmp=(NuObsValueCmp*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_NU_CMPD_VAL_OBS);
				if(nu_obs_value_cmp!=NULL)
				{
					int count = nu_obs_value_cmp->getCount();
					for(int i=0; i< count;i++)
					{
						NuObsValue* nu_obs_value=nu_obs_value_cmp->getValue(i);
						int physio_id = nu_obs_value->getPhysioId();
						int value = nu_obs_value->getActualValue();
						for(int i=0; i<wantedNumericIDs.size(); i++)
						{
							if(wantedNumericIDs[i]==physio_id)
							{
								numericBuffers[i]->addItem(value,time_stamp/8000);
								qDebug() << numericBuffers[i]->getLastTimeStamp() << " - Numeric added." << endl;
							}
						}
					}
				}
			}
		}
	}
	else if(poll_type==Object::NOM_MOC_VMS_MDS)
	{
		//qDebug() << "NOM_MOC_VMS_MDS" << endl;
		//poll_info_list->print("--------START NUMERICS: PollInfoList:");
		//cout <<"NUMERICS!!!" << endl;
		for(int i=0; i<poll_info_list->getCount();i++)
		{
			int jCount=poll_info_list->getValue(i)->getPollInfoCount();
			for(int j=0; j<jCount;j++)
			{
				ObservationPoll* obs_poll=poll_info_list->getValue(i)->getPollInfoValue(j);
				NuObsValue* nu_obs_value=(NuObsValue*)obs_poll->getAttributes()->getAttribute(Object::NOM_ATTR_NU_VAL_OBS);
				vector<OIDType> OIDTypes(obs_poll->getAttributes()->getOIDTypeList());
				for(int p=0;p<OIDTypes.size();p++)
					cout << "ID " << p << ": " << OIDTypes[p] << endl;

			}
		}
	}
}


