#pragma once
#include "UDPStructures.h"
#include <iostream>
#include <deque>
#include <QDataStream>
#include <string>
using namespace std;

bool findByteSequence(QDataStream & converter, char *bytes, uint size);

//----------Connect indication event-----------------

class ROapdus;
class ROIVapdu;
class EventReportArgument;
class AttributeList;
class ManagedObjectId;
class SPpdu;
class RORSapdu;
class EventReportResult;
class TYPE;
class ActionArgument;
class AbsoluteTime;
class ActionResult;
class GetArgument;
class GetResult;
class SetArgument;
class SetResult;
typedef quint32 TextId;
typedef quint32 Nomenclature;
typedef quint32 RelativeTime;
typedef quint16 OIDType;
typedef quint16 Handle;
typedef quint16 MdsContext;
typedef AttributeList ConnectIndInfo;
typedef quint32 ProtocolVersion;
const int MDDL_VERSION1 = 0x80000000;
typedef quint32 NomenclatureVersion;
const int NOMEN_VERSION = 0x40000000;
typedef quint32 FunctionalUnits;
const int FUNC_UNIT_ZERO = 0x00000000;
typedef quint32 SystemType;
const int SYST_CLIENT = 0x80000000;
const int SYST_SERVER = 0x00800000;
typedef quint32 StartupMode;
const int HOT_START = 0x80000000;
const int WARM_START = 0x40000000;
const int COLD_START = 0x20000000;

class ConnectIndication{
public:

	ConnectIndication(QDataStream &converter, int &size);
	int getIndicationPort();
	QByteArray getConnectIndication();
private:
    Nomenclature nomenclature;

    ROapdus *ro_apdus; //(ro_type := ROIVapdu)
    ROIVapdu *roiv_apdu; //(command_type := CMD_EVENT_REPORT)
    EventReportArgument *event_report_argument; /*(managed_object:={NOM_MOC_MDS_COMPOS_SINGLE_BED,0,0},
                               event_type := NOM_NOTI_MDS_CONNECT_INDIC)*/
    ConnectIndInfo *connect_ind_info;
};

//----------MDS Create Event-----------------
class MDSCreateInfo{
public:
	MDSCreateInfo();
	MDSCreateInfo(QDataStream & converter, int &size);
	~MDSCreateInfo();
	ManagedObjectId getManagedObject();
	void print(std::string title = "---------Start MDSCreateInfo---------");


private:
    ManagedObjectId* managed_object;
    AttributeList* attribute_list;
};

class MDSCreateEventReport{
public:
	MDSCreateEventReport();
	~MDSCreateEventReport();

	quint16 getInvokeId();
	
private:
    SPpdu *sp_pdu;
    ROapdus *ro_apdus; //(ro_type := ROIV_APDU)
    ROIVapdu *roiv_apdu; //(command_type := CMD_CONFIRMED_EVENT_REPORT)
    EventReportArgument* event_report_argument; /*(managed_object := {NOM_MOC_VMS_MDS, 0, 0},
                                                event_type := NOM_NOTI_MDS_CREATE)*/
    MDSCreateInfo* mds_create_info;
};

//----------MDS Create Event Result-----------------
class MDSCreateEventResult{
public:
	MDSCreateEventResult();
	MDSCreateEventResult(SPpdu &sp_pdu,  ROapdus &ro_apdus, RORSapdu& rors_apdu, EventReportResult& event_report_result);
	~MDSCreateEventResult();

	QByteArray getMDSCreateEventResult();
	void print(std::string title);
private:
    SPpdu* sp_pdu;
    ROapdus *ro_apdus; //(ro_type := RORS_APDU)
    RORSapdu* rors_apdu; /*(invoke_id := mirrored from event report,
                        command_type := CMD_CONFIRMED_EVENT_REPORT)*/
    EventReportResult* event_report_result; /*(managed_object := mirrored from event report,
                            event_type := NOM_NOTI_MDS_CREAT)
                            length := 0*/
};

//----------DATA ACCESS COMMANDS-----------------

//----------Single Poll Data Request-----------------
class PollMdibDataReq{
public:
	PollMdibDataReq();
	PollMdibDataReq(QDataStream &converter);
	PollMdibDataReq(quint16 poll_number, TYPE &polled_obj_type, OIDType polled_attr_grp);
	QByteArray getPollMdibDataReq();
	~PollMdibDataReq();
private:
    quint16 poll_number; //Use as counter
    TYPE *polled_obj_type; // NUMERICS, WAVES, ALERTS, PAT.DEMOG or MDS
    OIDType polled_attr_grp; // OIDType. Defines which set of attributes is polled
};

class MDSSinglePollAction{
public:
	MDSSinglePollAction();
	~MDSSinglePollAction();
private:
    SPpdu *sp_pdu;
    ROapdus *ro_apdus; //(ro_type := ROIV_APDU)
    ROIVapdu *roiv_apdu; // (command_type := CMD_CONFIRMED_ACTION)
    ActionArgument *action_argument; /*(managed_object := {NOM_MOC_VMS_MDS, 0, 0},
                        action_type := NOM_ACT_POLL_MDIB_DATA)*/
    PollMdibDataReq *poll_mdib_data_req;
};

//----------Single Poll Data Result-----------------
class ObservationPoll {
private:
    Handle obj_handle;
    AttributeList* attributes;
public:
	ObservationPoll();
	ObservationPoll(QDataStream &converter);
	~ObservationPoll();
	void print(std::string title="---------Start ObservationPoll---------");
	QByteArray getObservationPoll();
	AttributeList* getAttributes()
	{
		return attributes;
	}
};



class SingleContextPoll{
private:
    MdsContext context_id;
    struct {
        quint16 count;
        quint16 length;
        ObservationPoll **value;
    } poll_info;
public:
	SingleContextPoll();
	SingleContextPoll(QDataStream & converter);
	void print(std::string title="---------Start SingleContextPoll---------");
	QByteArray getSingleContextPoll();
	~SingleContextPoll();
	quint16 getPollInfoCount()
	{
		return poll_info.count;
	}
	ObservationPoll* getPollInfoValue(int index)
	{
		return poll_info.value[index];
	}

} ;

class PollInfoList{
private:
    quint16 count;
    quint16 length;
    SingleContextPoll** value;
public:
	PollInfoList();
	PollInfoList(QDataStream &converter);
	QByteArray getPollInfoList();
	void print(std::string title="---------Start PollInfoList---------");
	~PollInfoList();
	quint16 getCount()
	{
		return count;
	}
	SingleContextPoll* getValue(int index)
	{
		return value[index];
	}


};

class PollMdibDataReply{
private:
    quint16 poll_number;
    RelativeTime rel_time_stamp;
    AbsoluteTime *abs_time_stamp;
    TYPE* polled_obj_type;
    OIDType polled_attr_grp;
    PollInfoList* poll_info_list;

public:
	RelativeTime getRelativeTimeStamp(){return rel_time_stamp;}
	TYPE* getPolledObjectType(){return polled_obj_type;};
	PollInfoList* getPollInfoList(){return poll_info_list;};
	PollMdibDataReply();
	PollMdibDataReply(
		quint16 poll_number, 
		RelativeTime rel_time_stamp, 
		AbsoluteTime &abs_time_stamp,
		TYPE& polled_obj_type,
		OIDType polled_attr_grp,
		PollInfoList& poll_info_list);
	PollMdibDataReply(QDataStream &converter, int &size);

	~PollMdibDataReply();
	void print();
};

class MDSPollActionResult{
public:
	MDSPollActionResult();
	~MDSPollActionResult();
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus; //(ro_type := RORS_APDU)
    RORSapdu* rors_apdu; /*(invoke_id := "mirrored from request message"
                command_type := CMD_CONFIRMED_ACTION)*/
    ActionResult* action_result; /*(managed_object := {NOM_MOC_VMS_MDS, 0, 0},
                action_type := NOM_ACT_POLL_MDIB_DATA)*/
    PollMdibDataReply* poll_mdib_data_reply;
};

//----------Extended Poll Data Request-----------------
class PollMdibDataReqExt{
public:
	PollMdibDataReqExt();
	PollMdibDataReqExt(
		quint16 poll_number, 
		TYPE & polled_obj_type, 
		OIDType polled_attr_grp, 
		AttributeList& poll_ext_attr);

	~PollMdibDataReqExt();
	QByteArray getPollMdibDataReqExt();
	void print(std::string title = "---------Start PollMdibDataReqExt---------");
private:
    quint16 poll_number;
    TYPE* polled_obj_type;
    OIDType polled_attr_grp;
    AttributeList* poll_ext_attr;
} ;

class MDSExtendedPollAction{
public:
	MDSExtendedPollAction();
	~MDSExtendedPollAction();
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus; //(ro_type := ROIV_APDU)
    ROIVapdu* roiv_apdu; //(command_type := CMD_CONFIRMED_ACTION)
    ActionArgument* action_argument; /*(managed_object := {NOM_MOC_VMS_MDS, 0, 0},
                action_type := NOM_ACT_POLL_MDIB_DATA_EXT)*/
    PollMdibDataReqExt* poll_mdib_data_req_ext;
};

//----------Extended Poll Data Result-----------------
class PollMdibDataReplyExt{
private:
    quint16 poll_number;
    quint16 sequence_no;
    RelativeTime rel_time_stamp;
    AbsoluteTime* abs_time_stamp;
    TYPE* polled_obj_type;
    OIDType polled_attr_grp;
    PollInfoList* poll_info_list;

public:
	PollMdibDataReplyExt();
	PollMdibDataReplyExt(
		quint16 poll_number,
		quint16 sequence_no,
		RelativeTime rel_time_stamp,
		AbsoluteTime& abs_time_stamp,
		TYPE& polled_obj_type,
		OIDType polled_attr_grp,
		PollInfoList& poll_info_list
		);
	PollMdibDataReplyExt(QDataStream & converter, int &size);
	QByteArray getPollMdibDataReplyExt();
	void print(std::string title="---------Start PollMdibDataReplyExt---------");
	~PollMdibDataReplyExt(){};
	RelativeTime getRelativeTimeStamp()
	{
		return rel_time_stamp;
	}
	TYPE* getPolledObjectType()
	{
		return polled_obj_type;
	}

	PollInfoList* getPollInfoList()
	{
		return poll_info_list;
	}
};

class MDSPollActionResultExt{
public:
	MDSPollActionResultExt();
	~MDSPollActionResultExt();
private:
    SPpdu* sp_pdu;
    ROapdus* sp_apdus; //(ro_type := RORS_APDU)
    RORSapdu* rors_apdu; /*(invoke_id := "mirrored from request message"
            command_type := CMD_CONFIRMED_ACTION)*/
    ActionResult* action_result; /*(managed_object := {NOM_MOC_VMS_MDS, 0, 0},
            action_type := NOM_ACT_POLL_MDIB_DATA_EXT)*/
    PollMdibDataReplyExt* poll_mdib_data_reply_ext;
};

//----------Get Priority List-----------------
class MDSGetPriorityList{
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus; //(ro_type := ROIV_APDU)
    ROIVapdu* roiv_apdu; //(command_type := CMD_GET)
    GetArgument* get_argument; //(managed_object := {NOM_MOC_VMS_MDS, 0, 0})
public:
	MDSGetPriorityList();

	MDSGetPriorityList(
		SPpdu& sp_pdu,
		ROapdus& ro_apdus,
		ROIVapdu& roiv_apdu, 
		GetArgument& get_argument);

	QByteArray getMDSGetPriorityList();
	
	~MDSGetPriorityList();

};

//----------Get Priority List Result-----------------
class MDSGetPriorityListResult{
public:
	MDSGetPriorityListResult();
	~MDSGetPriorityListResult();
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus; //(ro_type := RORS_APDU)
    RORSapdu* rors_apdu; /*(invoke_id := “mirrored from request message”,
            command_type := CMD_GET)*/
    GetResult* get_result; //(managed_object := {NOM_MOC_VMS_MDS, 0, 0})
};



//----------SET PRIORITY LIST REQUEST-----------------

class MDSSetPriorityList{
public:
	MDSSetPriorityList();
	MDSSetPriorityList(
		SPpdu& sp_pdu,
		ROapdus& ro_apdus,
		ROIVapdu& roiv_apdu,
		SetArgument& set_argument);
	QByteArray getMDSSetPriorityList();

	~MDSSetPriorityList();
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus;/*(ro_type := ROIV_APDU)>
            ROIVapdu (command_type := CMD_CONFIRMED_SET)*/
	ROIVapdu* roiv_apdu;
    SetArgument *set_argument; //(managed_object := {NOM_MOC_VMS_MDS, 0, 0})
};

//----------SET PRIORITY LIST RESULT------------------

class MDSSetPriorityListResult{
public:
	MDSSetPriorityListResult();
	~MDSSetPriorityListResult();
private:
    SPpdu* sp_pdu;
    ROapdus* ro_apdus;// (ro_type := RORS_APDU)>
    RORSapdu* rors_apdu;/*(invoke_id := “mirrored from request message”,
    command_type := CMD_CONFIRMED_SET)*/
    SetResult* set_result;//(managed_object := {NOM_MOC_VMS_MDS, 0, 0})
};

//----------------------ASSOCIATION CONTROL PROTOCOL------------------

//----------Protocol Commands------------------
typedef quint32 LI;
/*
• If the length is smaller or equal 254 bytes, LI is one byte containing the actual length.
• If the length is greater than 254 bytes, LI is three bytes, the first being 0xff, the following two bytes
containing the actual length.
 */
class SessionHeader{
public:
	SessionHeader();
	SessionHeader(QDataStream & converter)
	{
		quint8 l;
		converter >> type >> l;

		if(l<=254)
			length=l;
		else 
		{
			quint16 int16;
			converter>>int16;
			length=int16;
		}
	}
	~SessionHeader(){};
	quint8 getType(){return type;}
	LI getLength(){return length;}
private:
    quint8 type;
    # define CN_SPDU_SI 0x0D //Session Connect header
    # define AC_SPDU_SI 0x0E //Session Accept header
    # define RF_SPDU_SI 0x0C //Session Refuse header
    # define FN_SPDU_SI 0x09 //Session Finish header
    # define DN_SPDU_SI 0x0A //Session Disconnect header
    # define AB_SPDU_SI 0x19 //Session Abort header
    # define DE_PROT 0xE1 //Data Export Protocol (not a session header!!!)
    LI length; //Be aware!
};

class MDSEUserInfoStd {
public:
	MDSEUserInfoStd(ProtocolVersion protocol_version, 
		NomenclatureVersion nomenclature_version,
		FunctionalUnits functional_units,
		SystemType system_type,
		StartupMode startup_mode,
		AttributeList &ol,
		AttributeList &sa);
		
	MDSEUserInfoStd(QDataStream & converter, int size);
	~MDSEUserInfoStd();

	QByteArray getMDSEUserInfoStd();

	void print();

private:
    ProtocolVersion protocol_version;
    NomenclatureVersion nomenclature_version;
    FunctionalUnits functional_units;
    SystemType system_type;
    StartupMode startup_mode;
    AttributeList *option_list;
    AttributeList *supported_aprofiles;
};

class AssocRespUserData
{
public:
	AssocRespUserData(QDataStream &converter, int size);
	~AssocRespUserData();
	void print()
	{
		std::cout<< "asn_length: " << asn_length << std::endl;
		mdse_user_info_std->print();

	}
private:
	quint32 asn_length;
	MDSEUserInfoStd *mdse_user_info_std;
};

class AssociationResponse
{
public:
	AssociationResponse(){};
	AssociationResponse(QDataStream &converter, int size);
	~AssociationResponse();
	void print()
	{
		assoc_resp_user_data->print();
	}
private:
	//AssocRespSessionHeader* assoc_resp_session_header;
	//AssocRespSessionData * assoc_resp_session_data;
	//AssocRespPresentationHeader * assoc_resp_pres_header;
	AssocRespUserData * assoc_resp_user_data;
	//AssocRespPresentationTrailer * assoc_resp_pres_trailer;

};

 // PROTOCOLCOMMANDS_H
