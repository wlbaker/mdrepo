#pragma once
//#include <stdint.h>
#include <QtGlobal>
//#include <Q_INT8>
//#include <Q_UINT8>
//#include <Q_INT16>
//#include <Q_UINT16>
//#include <Q_INT32>
//#include <Q_UINT32>
//#include <Q_INT64>
//#include <Q_UINT64>
#include <typeinfo>
//#include "udpTransmission/protocolCommands.h"
#include <QDataStream>
#include <QDebug>
#include <string>
#include "protocolCommands.h"
#include <math.h>
#include <fstream>

quint8 bcdToDec(quint8 val);

quint8 decToBcd(quint8 val);

//Float type
typedef quint32 FLOATType; //exponent 8 bits + mantissa 24 bits

float FLOATTypeToFloat(FLOATType val);


// Relative time
typedef quint32 RelativeTime;

//OID types
typedef quint16 OIDType;
typedef quint16 PrivateOID;
//void processOIDType(OIDType id, QDataStream &converter);


/*
template <typename Type>
QByteArray appendData(QByteArray & datagram, Type data);
QByteArray appendData(QByteArray & datagram, QByteArray &data);
*/

QByteArray appendData(QByteArray & datagram, quint32 data);
QByteArray appendData(QByteArray & datagram, quint16 data);
QByteArray appendData(QByteArray & datagram, quint8 data);
QByteArray appendData(QByteArray & datagram, QByteArray data);


class AVAType;

class AttributeList{
private:
	std::string name; 
    quint16 count;
    quint16 length;
    AVAType **value;
public:
	AttributeList(std::string name="default");
	AttributeList(quint16 count, quint16 length, AVAType *avat_value, std::string name="default");
	AttributeList(QDataStream &converter, int &size);
	~AttributeList();
	QByteArray getAttributeList();
	std::vector<OIDType> getOIDTypeList();
	//void* getObject(OIDType id);
	void* getAttribute(OIDType id);
	void print(std::string title="---------Start AttributeList---------");

};

//-----------Command Data Types------------------

/*
enum sizeOfStructs{
    RORLS_ID_SIZE = 2,
    MANAGED_OBJECT_ID_SIZE = 6,
    GET_ERROR_SIZE = 4,
    SET_ERROR_SIZE = 6,
    ATTRIBUTE_ID_LIST_SIZE = 6,
    MODIFICATION_LIST_SIZE = 0,
    RO_APDUS_SIZE = 4,
    ROIV_APDU_SIZE = 6,
    EVENT_REPORT_ARGUMENT_SIZE =14,
    NU_OBS_VALUE_SIZE = 0,
    METRIC_STRUCTURE_SIZE = 0,
    SAMPLE_TYPE_SIZE = 0,
    SA_FIXED_VAL_SPEC_ENTRY16_SIZE = 0,
    SA_OBS_VALUE_SIZE = 0,
    PROTO_SUPPORT_ENTRY_SIZE = 0,
    MAC_ADDRESS_SIZE = 0,
    IP_ADDRESS_SIZE = 0
};
*/

//Absolute time
class AbsoluteTime{
public:
	AbsoluteTime()
	{
		this->century=0;
		this->year=0;
		this->month=0;
		this->day=0;
		this->hour=0;
		this->minute=0;
		this->second=0;
		this->sec_fractions=0;
	}
	AbsoluteTime(quint8 century, quint8 year, quint8 month, quint8 day, quint8 hour, quint8 minute, quint8 second, quint8 sec_fractions)
	{
		this->century=century;
		this->year=year;
		this->month=month;
		this->day=day;
		this->hour=hour;
		this->minute=minute;
		this->second=second;
		this->sec_fractions=sec_fractions;
	};
	AbsoluteTime(QDataStream &converter, int &size)
	{
		quint8 byte;
		converter>>byte;
		century= bcdToDec(byte);

		converter>>byte;
		year= bcdToDec(byte);

		converter>>byte;
		month= bcdToDec(byte);

		converter>>byte;
		day= bcdToDec(byte);

		converter>>byte;
		hour= bcdToDec(byte);

		converter>>byte;
		minute= bcdToDec(byte);

		converter>>byte;
		second= bcdToDec(byte);

		converter>>byte;
		sec_fractions= bcdToDec(byte);
		/*
		converter 
			>> century 
			>> year 
			>> month 
			>> day 
			>> hour
			>> minute 
			>> second 
			>> sec_fractions;
			*/
	};

	QByteArray getAbsoluteTime()
	{
		QByteArray datagram;
		appendData(datagram, century);
		appendData(datagram, year);
		appendData(datagram, month);
		appendData(datagram, day);
		appendData(datagram, hour);
		appendData(datagram, minute);
		appendData(datagram, second);
		appendData(datagram, sec_fractions);
		return datagram;
	};
	void print(std::string title="---------Start AbsoluteTime---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint8 century: " << century;
		qDebug() << "quint8 year: " << year;
		qDebug() << "quint8 month: " << month;
		qDebug() << "quint8 day: " << day;
		qDebug() << "quint8 hour: " << hour;
		qDebug() << "quint8 minute: " << minute;
		qDebug() << "quint8 second: " << second;
		qDebug() << "quint8 sec_fractions: " << sec_fractions;
		qDebug() << "---------End AbsoluteTime---------";
	}

private:
    quint8 century;
    quint8 year;
    quint8 month;
    quint8 day;
    quint8 hour;
    quint8 minute;
    quint8 second;
    quint8 sec_fractions;
};

typedef quint16 NomPartition;
class TYPE{
private:

    NomPartition partition;
    OIDType code;
public:
	//Type
	static const int NOM_PART_OBJ = 1;          //Object oriented element, device nomenclature
	static const int NOM_PART_SCADA = 2;       //Types of measurement and place of the measurement
	static const int NOM_PART_EVT = 3;          //Codes for alerts
	static const int NOM_PART_DIM = 4;          //Units of measurement
	static const int NOM_PART_PGRP = 6;         //Identification of parameter groups
	static const int NOM_PART_INFRASTRUCT = 8;  //Infrastructure for Data Export applications

	TYPE()
	{
		this->partition=0;
		this->code=0;
	};
	TYPE(NomPartition partition, OIDType code)
	{
		this->partition=partition;
		this->code=code;
	};
	TYPE(QDataStream &converter)
	{
		converter >> partition >> code;
	};

	QByteArray getTYPE()
	{
		QByteArray datagram;
		appendData(datagram, partition);
		appendData(datagram, code);
		return datagram;
	};
	OIDType getCode()
	{
		return code;
	}
	void print(std::string title="---------Start TYPE---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "NomPartition partition: " << partition;
		switch(partition)
		{
		case NOM_PART_OBJ:
			qDebug() << "Object oriented element, device nomenclature";
			break;
		case NOM_PART_SCADA:
			qDebug() << "SCADA: Types of measurement and place of the measurement";
			break;
		case NOM_PART_EVT:
			qDebug() << "Codes for alerts";
			break;
		case NOM_PART_DIM:
			qDebug() << "Units of measurement";
			break;
		case NOM_PART_PGRP:
			qDebug() << "Identification of parameter groups";
			break;
		case NOM_PART_INFRASTRUCT:
			qDebug() << "Infrastructure for Data Export applications";
			break;
		}
		qDebug() << "OIDType code: " << code;
		qDebug() << "---------End TYPE---------";
	}

};

//Handle
typedef quint16 Handle;

//Global handle
typedef quint16 MdsContext;

class GlbHandle {
public:
	GlbHandle(void)
	{
		this->context_id=0;
		this->handle=0;
	};
	GlbHandle(MdsContext context_id, Handle handle)
	{
		this->context_id=context_id;
		this->handle=handle;
	};
	GlbHandle(QDataStream &converter, int &size)
	{
		size-=4;
		converter >> context_id >> handle;
	};

	QByteArray getGlbHandle()
	{
		QByteArray datagram;
		appendData(datagram, context_id);
		appendData(datagram, handle);
		return datagram;
	};
	void print(std::string title="---------Start GlbHandle---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "MdsContext context_id: " <<  context_id;
		qDebug() << "Handle handle: " <<  handle;
		qDebug() << "---------End GlbHandle---------";
	}
	private:
    MdsContext context_id;
    Handle handle;
};

//Managed object identifier
class ManagedObjectId{
public:
	ManagedObjectId()
	{
		m_obj_class=0;
		m_obj_inst=new GlbHandle();
	};
    ManagedObjectId(OIDType m_obj_class, GlbHandle& m_obj_inst);
    ManagedObjectId(QDataStream &converter, int &size);
	QByteArray getManagedObjectId();
	void print(std::string title="---------Start ManagedObjectId---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "OIDType m_obj_class: " << m_obj_class;
		m_obj_inst->print();
		qDebug() << "---------End ManagedObjectId---------";
	}
	~ManagedObjectId();
	private:
	OIDType m_obj_class;
    GlbHandle* m_obj_inst;
};


//Attribute Value Assertion

//class AVAType;

//Attribute list
//class AttributeList;


//String
class String{
public:
	String()
	{
		length=0;
		value= new quint16[length/2];
	};
	String(quint16 length, quint16 *stringValues)
	{
		this->length=length;
		value=new quint16[length/2];
		for(int i =0;i<length/2; i++)
			value[i]=stringValues[i];
	};

	String(QDataStream &converter, int &size)
	{
		converter >> length;
		value = new quint16[length/2];

		for(int i =0;i<length/2; i++)
			converter >> value[i];
	};

	~String()
	{
		//delete[] value;
	};

	QByteArray getString()
	{
		QByteArray datagram;
		appendData(datagram, length);
		//appendData(datagram, value);

		for(int i =0;i<length/2; i++)
			appendData(datagram, value[i]);

		return datagram;
	};
	void print(std::string title="---------Start String---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		/*std::string s="";
		for(int i =0;i<length/2; i++)
			s=s+value[i];
		
		qDebug() << QString::fromStdString(s);
		*/
		qDebug() << "String of " << length << " characters";
		qDebug() << "---------End String---------";
	}
	private:
    quint16 length;
    quint16 *value;
};


//Variable label
class VariableLabel{
public:
	VariableLabel()
	{
		length=0;
		value=new quint8[length];
	};
	VariableLabel(quint16 length, quint8 *VLValues)
	{
		this->length=length;
		value=new quint8[length];
		for(int i =0;i<length; i++)
			value[i]=VLValues[i];
	};

	VariableLabel(QDataStream &converter, int &size)
	{
		converter >> length;
		value = new quint8[length];

		for(int i =0;i<length; i++)
			converter >> value[i];
	};

	~VariableLabel()
	{
		//delete value;
	};

	QByteArray getVariableLabel()
	{
		QByteArray datagram;
		appendData(datagram, length);
		for(int i =0;i<length; i++)
			appendData(datagram, value[i]);

		return datagram;
	};
	private:
    quint16 length;
    quint8 *value;
};


//Text ID
typedef quint32 TextId;

class TextIdList{
public:
	TextIdList(QDataStream & converter)
	{
		converter >> count >> length;
		value=new TextId[count];
		for(int i=0;i<count;i++)
		{
			TextId tmp;
			converter >> tmp;
			value[i]=TextId(tmp);
		}
	}
	TextIdList(quint16 count, quint16 length, TextId* value)
	{
		this->count=count;
		this->length=length;
		this->value=new TextId[count];
		for(int i=0; i<count;i++)
			this->value[i]=value[i];

	}
	TextIdList(){};
	~TextIdList(){};
	void print(std::string title="---------Start TextIdList---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0;i<count;i++)
		{
			qDebug() << "TextId** value[" << i<<"]: "
				<< value[i];
		}
	}
	QByteArray getTextIdList()
	{
		QByteArray byteArray;
		appendData(byteArray, count);
		appendData(byteArray, length);
		for(int i=0;i<count;i++)
			appendData(byteArray, value[i]);
		return byteArray;

	}
private:
    quint16 count;
    quint16 length;
    TextId* value;
};



//-----------Protocol Command Structure------------------

//Session/presentation header
class SPpdu{
public:
	SPpdu()
	{
		this->session_id=0;
		this->p_context_id=0;
	};
	SPpdu(quint16 session_id, quint16 p_context_id)
	{
		this->session_id=session_id;
		this->p_context_id=p_context_id;
	};
	SPpdu(QDataStream &converter, int &size)
	{
		converter >> session_id >> p_context_id;
	};
	QByteArray getSPpdu()
	{
		QByteArray datagram;
		appendData(datagram, session_id);
		appendData(datagram, p_context_id);
		return datagram;
	};
	void print(std::string title="---------Start SPpdu---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 session_id" <<  session_id;
		qDebug() << "quint16 p_context_id" <<  p_context_id;
		qDebug() << "---------End SPpdu---------";

	};
	quint16 getSessionID(){return session_id;}
	quint16 getContextID(){return p_context_id;}
	private:
    quint16 session_id; /* contains a fixed value 0xE100 */
    quint16 p_context_id; /* negotiated in association phase */
};

//Remote Operation Header
class ROapdus{
public:
	ROapdus()
	{
		ro_type=0;
		length=0;
	};
	ROapdus(quint16 ro_type, quint16 length)
	{
		this->ro_type=ro_type;
		this->length=length;
	};
	ROapdus(QDataStream &converter, int &size)
	{
		size-=4;
		//qDebug() << "size: " << size;
		converter >> ro_type >> length;
		//qDebug() << "lenght: " << length;
	};
	QByteArray getROapdus()
	{
		QByteArray datagram;
		appendData(datagram, ro_type);
		appendData(datagram, length);
		return datagram;
	};
	void print(std::string title="---------Start ROapdus---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 ro_type: " << ro_type;
		switch(ro_type)
		{
		case ROIV_APDU:
			qDebug() << "Remote Operation Invoke";
			break;
		case RORS_APDU:
			qDebug() << "Remote Operation Result";
			break;
		case ROER_APDU:
			qDebug() << "Remote Operation Error";
			break;
		case ROLRS_APDU:
			qDebug() << "Remote Operation Linked Result";
			break;
		}
		qDebug() << "quint16 length: " << length;
		qDebug() << "---------End ROapdus---------";
	}
	quint16 getRoType(){return ro_type;}
	static const int ROIV_APDU = 1;    //Remote Operation Invoke
    static const int RORS_APDU = 2;    //Remote Operation Result
    static const int ROER_APDU = 3;    //Remote Operation Error
    static const int ROLRS_APDU = 5;   //Remote Operation Linked Result
	private:
    quint16 ro_type; /* ID for operation */

    quint16 length; /* bytes to follow */
};

//Command Types
typedef quint16 CMDType;
const int CMD_EVENT_REPORT = 0;
const int CMD_CONFIRMED_EVENT_REPORT = 1;
const int CMD_GET = 3;
const int CMD_SET = 4;
const int CMD_CONFIRMED_SET = 5;
const int CMD_CONFIRMED_ACTION = 7;


//Remote operation invoke
class ROIVapdu {
public:
	ROIVapdu()
	{
		this->invoke_id=0;
		this->command_type=0;
		this->length=0;
	};
	ROIVapdu(quint16 invoke_id, CMDType command_type, quint16 length)
	{
		this->invoke_id=invoke_id;
		this->command_type=command_type;
		this->length=length;
	};
	ROIVapdu(QDataStream &converter, int &size)
	{
		size-=6;
		//qDebug() << "size: " << size;
		converter >> invoke_id >> command_type >> length;
		//qDebug() << "length: " << length;
	};
	QByteArray getROIVapdu()
	{
		QByteArray datagram;
		appendData(datagram, invoke_id);
		appendData(datagram, command_type);
		appendData(datagram, length);
		return datagram;
	};
	CMDType getType(){return command_type;}
	quint16 getInvokeID(){return invoke_id;}
	int getSize()
	{
		QByteArray byteArray=getROIVapdu();
		return byteArray.size();

	}
	void print(std::string title="---------Start ROIVapdu---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 invoke_id" << invoke_id;
		qDebug() << "CMDType command_type" << command_type;
		switch(command_type)
		{
		case CMD_EVENT_REPORT:
			qDebug() << "CMD_EVENT_REPORT";
			break;
		case CMD_CONFIRMED_EVENT_REPORT:
			qDebug() << "CMD_CONFIRMED_EVENT_REPORT";
			break;
		case CMD_GET:
			qDebug() << "CMD_GET";
			break;
		case CMD_SET:
			qDebug() << "CMD_SET";
			break;
		case CMD_CONFIRMED_SET:
			qDebug() << "CMD_CONFIRMED_SET";
			break;
		case CMD_CONFIRMED_ACTION:
			qDebug() << "CMD_CONFIRMED_ACTION";
			break;
		
		}
		qDebug() << "quint16 length" << length;
		qDebug() << "---------End ROIVapdu---------";
	}
	private:
    quint16 invoke_id; /* identifies the transaction */
    CMDType command_type; /* identifies type of command */
    quint16 length; /* no. of bytes in rest of message */
};

//Remote operation result
class RORSapdu{
public:
	RORSapdu()
	{
		this->invoke_id=0;
		this->command_type=0;
		this->length=0;
	};
	RORSapdu(quint16 invoke_id, CMDType command_type, quint16 length)
	{
		this->invoke_id=invoke_id;
		this->command_type=command_type;
		this->length=length;
	};
	RORSapdu(QDataStream &converter, int &size)
	{
		converter >> invoke_id >> command_type >> length;
	};
	QByteArray getRORSapdu()
	{
		QByteArray datagram;
		appendData(datagram, invoke_id);
		appendData(datagram, command_type);
		appendData(datagram, length);
		return datagram;
	};
	void print(std::string title="---------Start RORSapdu---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 invoke_id: " << invoke_id;
		qDebug() << "CMDType command_type : " << command_type;
		qDebug() << "quint16 length : " << length;
		qDebug() << "---------End RORSapdu---------";
	}
	CMDType getCMDType(){return command_type;}
	private:
    quint16 invoke_id; /* mirrored back from op. invoke */
    CMDType command_type; /* identifies type of command */
    quint16 length; /* no of bytes in rest of message */
};

//Remote Operation Linked Result
class RorlsId{
public:
	RorlsId()
	{
		this->state=0;
		this->count=0;
	};
	RorlsId(quint8 state, quint8 count)
	{
		this->state=state;
		this->count=count;
	};
	RorlsId(QDataStream &converter, int &size)
	{
		converter >> state >> count;
	};
	QByteArray getRorlsId()
	{
		QByteArray datagram;
		appendData(datagram, state);
		appendData(datagram, count);
		return datagram;
	};
	quint8 getState()
	{
		return state;
	}
	std::string getStateAsString()
	{
		switch(state)
		{
		case RORLS_FIRST:
			return "RORLS_FIRST";
		case RORLS_NOT_FIRST_NOT_LAST:
			return "RORLS_NOT_FIRST_NOT_LAST";
		case RORLS_LAST:
			return "RORLS_LAST";
		}

	}
	quint8 getCount(){return count;}
	static const int RORLS_FIRST = 1; /* set in the first message */
    static const int RORLS_NOT_FIRST_NOT_LAST = 2;
    static const int RORLS_LAST = 3; /* last RORLSapdu, one RORSapdu to follow */
	private:
    quint8 state;

    
    quint8 count; /* counter starts with 1 */
};

class ROLRSapdu{
public:
	ROLRSapdu()
	{
		linked_id= new RorlsId(); /* see below */
		invoke_id=0; /* see below */
		command_type=0; /* identifies type of command */
		length=0;
	};
	ROLRSapdu(RorlsId &Rorls_Id, quint16 invoke_id, CMDType command_type, quint16 length);

	ROLRSapdu(QDataStream &converter, int &size);

	~ROLRSapdu()
	{
		//delete linked_id;
	};
	RorlsId* getLinked_ID(){return linked_id;}
	QByteArray getROLRSapdu()
	{
		QByteArray datagram;
		appendData(datagram, linked_id->getRorlsId());
		appendData(datagram, invoke_id);
		appendData(datagram, command_type);
		appendData(datagram, length);
		return datagram;
	};
private:
    RorlsId* linked_id; /* see below */
    quint16 invoke_id; /* see below */
    CMDType command_type; /* identifies type of command */
    quint16 length; /* no of bytes in rest of message */
};


//Remote operation error
class ROERapdu{
public:
	ROERapdu()
	{
		this->invoke_id=0;
		this->error_value=0;
		this->length=0;
	};
	ROERapdu(quint16 invoke_id, quint16 error_value, quint16 length)
	{
		this->invoke_id=invoke_id;
		this->error_value=error_value;
		this->length=length;
	};

	ROERapdu(QDataStream &converter, int &size)
	{
		converter >> invoke_id >> error_value >> length;
	};

	QByteArray getROERapdu()
	{
		QByteArray datagram;
		appendData(datagram,invoke_id);
		appendData(datagram,error_value);
		appendData(datagram,length);
		return datagram;
	};
	quint16 getErrorValue()
	{
		switch(error_value)
		{
		case NO_SUCH_OBJECT_CLASS:
			qDebug() << "NO_SUCH_OBJECT_CLASS";
			break;
		case NO_SUCH_OBJECT_INSTANCE:
			qDebug() << "NO_SUCH_OBJECT_INSTANCE";
			break;
		case ACCESS_DENIED:
			qDebug() << "ACCESS_DENIED";
			break;
		case GET_LIST_ERROR:
			qDebug() << "GET_LIST_ERROR";
			break;
		case SET_LIST_ERROR:
			qDebug() << "SET_LIST_ERROR";
			break;
		case NO_SUCH_ACTION:
			qDebug() << "NO_SUCH_ACTION";
			break;
		case PROCESSING_FAILURE:
			qDebug() << "PROCESSING_FAILURE";
			break;
		case INVALID_ARGUMENT_VALUE:
			qDebug() << "INVALID_ARGUMENT_VALUE";
			break;
		case INVALID_SCOPE:
			qDebug() << "INVALID_SCOPE";
			break;
		case INVALID_OBJECT_INSTANCE:
			qDebug() << "INVALID_OBJECT_INSTANCE";
			break;
		}
		return error_value;
	}

	void print(std::string title="---------ROERapdu---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 invoke_id: " <<  invoke_id;
		qDebug() << "quint16 error_value: " <<  error_value;
		qDebug() << "quint16 length: " <<  length;
		qDebug() << "";
	}
	static const int NO_SUCH_OBJECT_CLASS = 0;
    static const int NO_SUCH_OBJECT_INSTANCE = 1;
    static const int ACCESS_DENIED = 2;
    static const int GET_LIST_ERROR = 7;
    static const int SET_LIST_ERROR = 8;
    static const int NO_SUCH_ACTION = 9;
    static const int PROCESSING_FAILURE = 10;
    static const int INVALID_ARGUMENT_VALUE = 15;
    static const int INVALID_SCOPE = 16;
    static const int INVALID_OBJECT_INSTANCE = 17;
private:
    quint16 invoke_id;
    quint16 error_value;

    quint16 length;
};

typedef quint16 ErrorStatus;
const int ATTR_ACCESS_DENIED = 2;
const int ATTR_NO_SUCH_ATTRIBUTE = 5;
const int ATTR_INVALID_ATTRIBUTE_VALUE = 6;
const int ATTR_INVALID_OPERATION = 24;
const int ATTR_INVALID_OPERATOR = 25;

typedef quint16 ModifyOperator;
const int REPLACE = 0;
const int ADD_VALUES = 1;
const int REMOVE_VALUES = 2;
const int SET_TO_DEFAULT = 3;

class GetError {
public:
	GetError()
	{
		this->error_status=0;
		this->attribute_id=0;
	};
	GetError(ErrorStatus error_status, OIDType attribute_id)
	{
		this->error_status=error_status;
		this->attribute_id=attribute_id;
	};
	GetError(QDataStream &converter, int &size)
	{
		converter >> error_status >> attribute_id;
	};
	QByteArray getGetError(){
		QByteArray datagram;
		appendData(datagram, error_status);
		appendData(datagram, attribute_id);
		return datagram;
	};
private:
    ErrorStatus error_status;
    OIDType attribute_id;
};

class getInfoList{
public:
	getInfoList()
	{
		count=0;
		length=0;
		value=new GetError*[count];
	};
	getInfoList(quint16 count, quint16 length, GetError* error_value);
	getInfoList(QDataStream &converter, int &size);
	~getInfoList()
	{
		/*
		for(int i=0;i<count; i++)
			delete value[i];

		delete[] value;
		*/
	};
	QByteArray getGetInfoList(){
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);
		for(int i=0; i<count;i++)
			appendData(datagram, value[i]->getGetError());

		return datagram;
	};
private:
    quint16 count;
    quint16 length;
    GetError **value;
};

class GetListError{
public:
	GetListError()
	{
		get_info_list= new getInfoList();
		managed_object= new ManagedObjectId();
	};
	GetListError(ManagedObjectId &mngd_obj_id, getInfoList &info_list);
	GetListError(QDataStream &converter, int &size);
	~GetListError()
	{
		/*
		delete managed_object;
		delete get_info_list;
		*/
	};
	QByteArray getGetListError()
	{
		QByteArray datagram;
		appendData(datagram, get_info_list->getGetInfoList());
		appendData(datagram, managed_object->getManagedObjectId());
		return datagram;
	};
private:
	getInfoList* get_info_list;
    ManagedObjectId *managed_object;

};

class SetError {
public:
	SetError()
	{
		error_status=0;
		modify_operator=0;
		attribute_id=0;
	};
	SetError(ErrorStatus errorStatus, ModifyOperator modifyOperator, OIDType attributeId)
	{
		error_status=errorStatus;
		modify_operator=modifyOperator;
		attribute_id=attributeId;
	};
	SetError(QDataStream &converter, int &size)
	{
		converter >> error_status >> modify_operator >> attribute_id;
	};
	QByteArray getSetError()
	{
		QByteArray datagram;
		appendData(datagram, error_status);
		appendData(datagram, modify_operator);
		appendData(datagram, attribute_id);
		return datagram;
	};
private:
    ErrorStatus error_status;
    ModifyOperator modify_operator;
    OIDType attribute_id;
};

class setInfoList 
{
public:
	setInfoList()
	{
		count=0;
		length=0;
		value=new SetError*[count];
	};
	setInfoList(quint16 count, quint16 length, SetError *error_values);
	setInfoList(QDataStream &converter, int &size);
	~setInfoList()
	{
		/*
		for(int i=0;i<count; i++)
			delete value[i];

		delete[] value;
		*/
	};
	QByteArray getSetInfoList()
	{
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);
		for(int i=0;i<count;i++)
			appendData(datagram, value[i]->getSetError());
		return datagram;
	};
private:
	quint16 count;
	quint16 length;
	SetError **value;
};


class SetListError{
public:
	SetListError()
	{

	};
	SetListError(ManagedObjectId& mngd_obj, setInfoList &info_list);
	SetListError(QDataStream &converter, int &size);
	~SetListError()
	{
		/*
		delete managed_object;
		delete set_info_list;
		*/
	};

	QByteArray getSetListError()
	{
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, set_info_list->getSetInfoList());
		return datagram;
	};
private:
    ManagedObjectId *managed_object;
	setInfoList* set_info_list;
};

class ProcessingFailure{
public:
	ProcessingFailure(){};
	ProcessingFailure(OIDType error_id, quint16 length)
	{
		this->error_id=error_id;
		this->length=length;
	};
	ProcessingFailure(QDataStream &converter, int &size)
	{
		converter >> error_id >> length;
	};
	QByteArray getProcessingFailure()
	{
		QByteArray datagram;
		appendData(datagram, error_id);
		appendData(datagram, length);
		return datagram;
	};
	OIDType getID(){return error_id;}
	quint16 getLength(){return length;}
private:
    OIDType error_id;
    quint16 length;
};

//Event report
class EventReportArgument {
public:
	EventReportArgument();
	EventReportArgument(ManagedObjectId& mngd_obj, RelativeTime event_time, OIDType event_type, quint16 length);
	EventReportArgument(QDataStream &converter, int &size);

	~EventReportArgument()
	{
		//delete managed_object;
	}

	QByteArray getEventReportArgument(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, event_time);
		appendData(datagram, event_type);
		appendData(datagram, length);
		return datagram;
	};
	OIDType getEventType(){return event_type;}
	quint16 getLength(){return length;}
	RelativeTime getEventTime(){return event_time;}
	ManagedObjectId getManagedObject(){
		return *managed_object;
	}
	void print(std::string title="---------Start EventReportArgument---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		managed_object->print();
		qDebug() << "RelativeTime event_time: " << event_time;
		qDebug() << "OIDType event_type: " << event_type;
		qDebug() << "quint16 length: " << length;
		qDebug() << "---------End EventReportArgument---------";
	}
private:
    ManagedObjectId *managed_object; /* ident. of sender */
    RelativeTime event_time; /* event time stamp */
    OIDType event_type; /* identification of event */
    quint16 length; /* size of appended data */
};

//Event report result
class EventReportResult {
public:
	EventReportResult(){};
	EventReportResult(ManagedObjectId& mngd_obj, RelativeTime current_time, OIDType event_type, quint16 length);
	EventReportResult(QDataStream &converter, int &size);
	~EventReportResult()
	{
		//delete managed_object;
	};
	QByteArray getEventReportResult(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, current_time);
		appendData(datagram, event_type);
		appendData(datagram, length);
		return datagram;
	};
	void print(std::string title = "---------Start EventReportResult---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		managed_object->print();
		qDebug() << "RelativeTime current_time: " << current_time;
		qDebug() << "OIDType event_type: " << event_type;
		qDebug() << "quint16 length: " << length;
		qDebug() << "---------End EventReportResult---------";
	}
private:
    ManagedObjectId *managed_object; /* mirrored from EvRep */
    RelativeTime current_time; /* result time stamp */
    OIDType event_type; /* identification of event */
    quint16 length; /* size of appended data */
};

//Action
class ActionArgument{
private:
    ManagedObjectId *managed_object;/* addressed object */
    quint32 scope; /* fixed value 0 */
    OIDType action_type; /* identification of method */
    //#define NOM_ACT_POLL_MDIB_DATA 3094
    //#define NOM_ACT_POLL_MDIB_DATA_EXT 61755
    quint16 length; /* size of appended data */

public:
	ActionArgument();
	ActionArgument(ManagedObjectId &mngd_obj, quint32 scope, OIDType action_type, quint16 length);
	ActionArgument(QDataStream &converter, int &size);
	~ActionArgument()
	{
		//delete managed_object;
	}
	QByteArray getActionArgument(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, scope);
		appendData(datagram, action_type);
		appendData(datagram, length);
		return datagram;
	};
};

//Action result
class ActionResult{
public:
	ActionResult(){};
	ActionResult(ManagedObjectId &mngd_obj, OIDType action_type, quint16 length);
	ActionResult(QDataStream &converter, int &size);
	~ActionResult()
	{
		//delete managed_object;
	};
	QByteArray getActionResult(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, action_type);
		appendData(datagram, length);
		return datagram;
	};
	OIDType getActionType()
	{
		return action_type;
	}
	quint16 getLength()
	{
		return length;
	}
	void print(std::string title="---------Start ActionResult---------");
private:
	ManagedObjectId *managed_object;
    OIDType action_type; /* identification of method */
    quint16 length; /* size of appended data */
};

//Get
class AttributeIdList{
public:
	AttributeIdList();
	AttributeIdList(quint16 count, quint16 length, OIDType *oidt_value);
	AttributeIdList(QDataStream &converter, int &size);
	~AttributeIdList()
	{


		//delete[] value;
	};
	QByteArray getAttributeIdList()
	{
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);

		for(int i=0; i<count; i++)
			appendData(datagram, value[i]);

		return datagram;
	};
	void print(std::string title="---------Start AttributeIdList---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0;i< count; i++)
			qDebug() << "OIDType *value[" << i << "]: " << value[i];
		qDebug()<<"---------End AttributeIdList---------";

	}
private:
    quint16 count;
    quint16 length;
    OIDType *value;
};

class GetArgument{
public:
	GetArgument();
	GetArgument(ManagedObjectId &mngd_obj, quint32 scope, AttributeIdList &attr_id_list);
	GetArgument(QDataStream &converter, int &size);
	~GetArgument()
	{
		//delete managed_object;
		//delete attribute_id_list;
	};

	QByteArray getGetArgument(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, scope);
		appendData(datagram, attribute_id_list->getAttributeIdList());
		return datagram;
	};
	void print(std::string title="---------Start GetArgument---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		managed_object->print();
		qDebug() << "quint32 scope: " << scope;
		attribute_id_list->print();
		qDebug() << "---------End GetArgument---------";

	}
private:
    ManagedObjectId *managed_object;
    quint32 scope;
    AttributeIdList *attribute_id_list;
};

//Get result
class GetResult;

//Set
class AttributeModEntry;


class ModificationList;
class AttributeList;

class SetArgument {
public:
	SetArgument();
	SetArgument(ManagedObjectId &mngd_obj, quint32 scope, ModificationList& mod_list);
	SetArgument(QDataStream &converter, int &size);
	~SetArgument();
	QByteArray getSetArgument();
	int getSize();
private:
    ManagedObjectId *managed_object;
    quint32 scope;
    ModificationList *modification_list;
};


//Set result
class SetResult {
public:
	SetResult(ManagedObjectId &mngd_obj, AttributeList &attr_list);
	SetResult(QDataStream &converter, int &size);
	~SetResult();
	QByteArray getSetResult();
private:
    ManagedObjectId *managed_object;
    AttributeList *attribute_list;
};

class PollDataReqPeriod {
public:
	PollDataReqPeriod()
	{
		active_period=0;
	};
	PollDataReqPeriod(RelativeTime active_period)
	{
		this->active_period=active_period;
	};
	PollDataReqPeriod(QDataStream &converter, int &size)
	{
		size-=4;
		converter >> active_period;
	};
	QByteArray getPollDataReqPeriod(){
		QByteArray datagram;
		appendData(datagram, active_period);
		return datagram;
	};
	void print(std::string title="---------Start PollDataReqPeriod---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "RelativeTime active_period: " <<  active_period;
		qDebug() << "---------End PollDataReqPeriod---------";

	}
private:
    RelativeTime active_period;
};

typedef quint32 PollProfileRevision;
const int POLL_PROFILE_REV_0 = 0x80000000;
typedef quint32 PollProfileOptions;
const int P_OPT_DYN_CREATE_OBJECTS = 0x40000000;
const int P_OPT_DYN_DELETE_OBJECTS = 0x20000000;


class PollProfileSupport{
public:
	PollProfileSupport();
	PollProfileSupport(
		PollProfileRevision poll_profile_revision, 
		RelativeTime min_poll_period, 
		quint32 max_mtu_rx,
		quint32 max_mtu_tx,
		quint32 max_bw_tx,
		PollProfileOptions options,
		AttributeList& opt_packages);
	PollProfileSupport (QDataStream &converter, int &size);
	~PollProfileSupport();
	QByteArray getPollProfileSupport();
	void print(std::string title="---------Start PollProfileSupport---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() <<"PollProfileRevision poll_profile_revision: " << poll_profile_revision;
		qDebug() <<"RelativeTime min_poll_period: " << min_poll_period;
		qDebug() <<"quint32 max_mtu_rx: " << max_mtu_rx;
		qDebug() <<"quint32 max_mtu_tx: " << max_mtu_tx;
		qDebug() <<"quint32 max_bw_tx: " << max_bw_tx;
		qDebug() <<"PollProfileOptions options: " << options;
		optional_packages->print();
		qDebug() << "---------End PollProfileSupport---------";

	}
private:
    PollProfileRevision poll_profile_revision;
    RelativeTime min_poll_period;
    quint32 max_mtu_rx;
    quint32 max_mtu_tx;
    quint32 max_bw_tx;
    PollProfileOptions options;
    AttributeList *optional_packages;
};

typedef quint32 PollProfileExtOptions;
const int POLL_EXT_PERIOD_NU_1SEC = 0x80000000;
const int POLL_EXT_PERIOD_NU_AVG_12SEC = 0x40000000;
const int POLL_EXT_PERIOD_NU_AVG_60SEC = 0x20000000;
const int POLL_EXT_PERIOD_NU_AVG_300SEC = 0x10000000;
const int POLL_EXT_PERIOD_RTSA = 0x08000000;
const int POLL_EXT_ENUM = 0x04000000;
const int POLL_EXT_NU_PRIO_LIST = 0x02000000;
const int POLL_EXT_DYN_MODALITIES = 0x01000000;

class PollProfileExt{
public:
	PollProfileExt()
	{
		options=0;
		ext_attribute= new AttributeList();
	};
	PollProfileExt(PollProfileExtOptions options, AttributeList &ext_attr);
	PollProfileExt(QDataStream &converter, int &size);
	~PollProfileExt();
	QByteArray getPollProfileExt();
	void print(std::string title="---------Start PollProfileExt---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "PollProfileExtOptions options: " << options;
		ext_attribute->print();
		qDebug() << "---------End PollProfileExt---------";
	};
private:

    PollProfileExtOptions options;
    AttributeList *ext_attribute;
};

typedef quint16 MeasurementState;
const int INVALID = 0x8000;
const int QUESTIONABLE = 0x4000;
const int UNAVAILABLE = 0x2000;
const int CALIBRATION_ONGOING = 0x1000;
const int TEST_DATA = 0x0800;
const int DEMO_DATA = 0x0400;
const int VALIDATED_DATA = 0x0080;
const int EARLY_INDICATION = 0x0040;
const int MSMT_ONGOING = 0x0020;
const int MSMT_STATE_IN_ALARM = 0x0002;
const int MSMT_STATE_AL_INHIBITED = 0x0001;

class NuObsValue{
private:
    OIDType physio_id;
    MeasurementState state;
    OIDType unit_code;
    FLOATType value;
	float actual_value;

public:
	OIDType getPhysioId(){return physio_id;}
	int getActualValue(){return actual_value;}
	NuObsValue()
	{
		this->physio_id=0;
		this->state=0;
		this->unit_code=0;
		this->value=0;
	}
	NuObsValue(OIDType physio_id,MeasurementState state, OIDType unit_code, FLOATType value)
	{
		this->physio_id=physio_id;
		this->state=state;
		this->unit_code=unit_code;
		this->value=value;
		actual_value=FLOATTypeToFloat(value);
	};
	NuObsValue(QDataStream &converter, int &size)
	{
		converter >> physio_id;
		converter >> state;
		converter >> unit_code;
		converter >> value;
		actual_value=FLOATTypeToFloat(value);
	};
	QByteArray getNuObsValue(){
		QByteArray datagram;
		appendData(datagram, physio_id);
		appendData(datagram, state);
		appendData(datagram, unit_code);
		appendData(datagram, value);
		return datagram;
	};

	void print(std::string title="---------Start NuObsValue---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "OIDType physio_id: " << physio_id;
		qDebug() << "MeasurementState state: " << state;
		qDebug() << "OIDType unit_code: " << unit_code;
		qDebug() << "FLOATType value: " << value;
		qDebug() << "Actual value: " << actual_value;
		qDebug() << "---------End NuObsValue---------";
	}

};

class NuObsValueCmp{
private:
    quint16 count;
    quint16 length;
    NuObsValue **value;
public:
	quint16 getCount(){return count;}
	NuObsValue * getValue(int i){return value[i];}
	NuObsValueCmp()
	{
		count=0;
		length=0;
		value=new NuObsValue*[count];
	}
	NuObsValueCmp(quint16 count, quint16 length, NuObsValue *nu_obs_value);
	NuObsValueCmp(QDataStream &converter, int &size);
	~NuObsValueCmp()
	{
		/*
		for(int i=0;i<count; i++)
			delete value[i];

		delete[] value;
		*/
	};
	QByteArray getNuObsValueCmp(){
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);

		for(int i=0; i < count; i++)
			appendData(datagram, value[i]->getNuObsValue());
    
		return datagram;
	};
	void print(std::string title="---------Start NuObsValueCmp---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0; i<count;i++)
		{
			qDebug() << "NuObsValue **value " << i << ": ";
			value[i]->print();
		}

		qDebug() << "---------End NuObsValueCmp---------";
	}

};

typedef quint16 SimpleColour;
const int COL_BLACK = 0;
const int COL_RED = 1;
const int COL_GREEN = 2;
const int COL_YELLOW = 3;
const int COL_BLUE = 4;
const int COL_MAGENTA = 5;
const int COL_CYAN = 6;
const int COL_WHITE = 7;
const int COL_PINK = 20;
const int COL_ORANGE = 35;
const int COL_LIGHT_GREEN = 50;
const int COL_LIGHT_RED = 65;

typedef quint16 MetricCategory;
const int MCAT_UNSPEC = 0;
const int AUTO_MEASUREMENT = 1;
const int MANUAL_MEASUREMENT = 2;
const int AUTO_SETTING = 3;
const int MANUAL_SETTING = 4;
const int AUTO_CALCULATION = 5;
const int MANUAL_CALCULATION = 6;
const int MULTI_DYNAMIC_CAPABILITIES = 5;
const int AUTO_ADJUST_PAT_TEMP = 128;
const int MANUAL_ADJUST_PAT_TEMP = 129;
const int AUTO_ALARM_LIMIT_SETTING = 130;

typedef quint16 MetricAccess;
const int AVAIL_INTERMITTEND = 0x8000;
const int UPD_PERIODIC = 0x4000;
const int UPD_EPISODIC = 0x2000;
const int MSMT_NONCONTINUOUS = 0x1000;

class MetricStructure {
public:
	MetricStructure()
	{
		this->ms_struct=0;
		this->ms_comp_no=0;
	}
	MetricStructure(quint8 ms_struct, quint8 ms_comp_no)
	{
		this->ms_struct=ms_struct;
		this->ms_comp_no=ms_comp_no;
	};
	MetricStructure(QDataStream &converter, int &size)
	{
		converter >> ms_struct >> ms_comp_no;
	};
	QByteArray getMetricStructure(){
		QByteArray datagram;
		appendData(datagram, ms_struct);
		appendData(datagram, ms_comp_no);
		return datagram;
	};
	void print(std::string title="---------Start MetricStructure---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint8 ms_struct: " << ms_struct;
		qDebug() << "quint8 ms_comp_no: " << ms_comp_no;

		qDebug() << "---------End MetricStructure---------";
	}
private:
    quint8 ms_struct;
    quint8 ms_comp_no;
};

typedef quint16 MetricRelevance;

class MetricSpec
{
public:
	MetricSpec()
	{
		this->update_period=0;
		this->category=0;
		this->access=0;
		this->structure=new MetricStructure();
		this->relevance=0;
	}
	MetricSpec(
		RelativeTime update_period,
		MetricCategory category,
		MetricAccess access,
		MetricStructure &strct,
		MetricRelevance relevance)
	{
		this->update_period=update_period;
		this->category=category;
		this->access=access;
		this->structure=new MetricStructure(strct);
		this->relevance=relevance;
	};
	MetricSpec(QDataStream &converter, int &size)
	{
		converter >> update_period >> category >> access;
		structure = new MetricStructure(converter, size);
		converter >> relevance;
	};
	~MetricSpec()
	{
		//delete structure;
	};
	QByteArray getMetricSpec(){
		QByteArray datagram;
		appendData(datagram, update_period);
		appendData(datagram, category);
		appendData(datagram, access);
		appendData(datagram, structure->getMetricStructure());
		appendData(datagram, relevance);

		return datagram;
	};
	void print(std::string title="---------Start MetricSpec---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "RelativeTime update_period: " << update_period;
		qDebug() << "MetricCategory category: " << category;
		qDebug() << "MetricAccess access: " << access;
		structure->print();
		qDebug() << "MetricRelevance relevance: " << relevance;
		qDebug() << "---------End MetricSpec---------";
	}
private:
    RelativeTime update_period;
    MetricCategory category;
    MetricAccess access;
    MetricStructure *structure;
    MetricRelevance relevance;
};

class SampleType {
public:
	SampleType()
	{
		sample_size=0;
		significant_bits=0;
	};
	SampleType(quint8 sample_size, quint8 significant_bits)
	{
		this->sample_size=sample_size;
		this->significant_bits=significant_bits;
	};
	SampleType(QDataStream &converter, int &size)
	{
		converter >> sample_size>> significant_bits;
	};
	QByteArray getSampleType(){
		QByteArray datagram;
		appendData(datagram, sample_size);
		appendData(datagram, significant_bits);
		return datagram;
	};
	void print(std::string title="---------Start SampleType---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint8 sample_size: " <<sample_size; 
		qDebug() << "quint8 significant_bits: " <<significant_bits; 

		qDebug() << "---------End SampleType---------";
	}
private:
    quint8 sample_size;
    quint8 significant_bits;
};

typedef quint16 SaFlags;
const int SMOOTH_CURVE = 0x8000;
const int DELAYED_CURVE = 0x4000;
const int STATIC_SCALE = 0x2000;
const int SA_EXT_VAL_RANGE = 0x1000;

class SaSpec{
public:
	SaSpec()
	{
		this->array_size=0;
		this->sample_type=new SampleType();
		this->flags=0;
	}
	SaSpec(quint16 array_size, SampleType &samp_t, SaFlags flags)
	{
		this->array_size=array_size;
		this->sample_type=new SampleType(samp_t);
		this->flags=flags;
	};
	SaSpec(QDataStream &converter, int &size)
	{
		converter >> array_size;
		sample_type = new SampleType(converter, size);
		converter >> flags;
		//print();
	};
	~SaSpec()
	{
		//delete sample_type;
	};
	QByteArray getSaSpec(){
		QByteArray datagram;
		appendData(datagram, array_size);
		appendData(datagram, sample_type->getSampleType());
		appendData(datagram, flags);
		return datagram;
	};
	void print(std::string title="---------Start SaSpec---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 array_size: " << array_size;
		sample_type->print();
		qDebug() << "SaFlags flags: " << flags;

		qDebug() << "---------End SaSpec---------";

	}
private:
    quint16 array_size;
    SampleType *sample_type;
    SaFlags flags;
};

class SaCalData16{
private:
	FLOATType lower_absolute_value;
	FLOATType upper_absolute_value;
	quint16 lower_scaled_value;
	quint16 upper_scaled_value;
	quint16 increment;
	quint16 cal_type;
public:
	SaCalData16(){};
	~SaCalData16(){};
	SaCalData16(QDataStream & converter)
	{
		converter >>
			lower_absolute_value >>
			upper_absolute_value >>
			lower_scaled_value >>
			upper_scaled_value >>
			increment >>
			cal_type;

	};
	void print(std::string title="---------Start SaCalData16---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "FLOATType lower_absolute_value: " << lower_absolute_value;
		qDebug() << "FLOATType upper_absolute_value: " << upper_absolute_value;
		qDebug() << "quint16 lower_scaled_value: " << lower_scaled_value;
		qDebug() << "quint16 upper_scaled_value: " << upper_scaled_value;
		qDebug() << "quint16 increment: " << increment;
		qDebug() << "quint16 cal_type: " << cal_type;

		qDebug() << "---------End SaCalData16---------";

	}
	QByteArray getSaCalData16()
	{
		QByteArray byteArray;
		appendData(byteArray, lower_absolute_value);
		appendData(byteArray, upper_absolute_value);
		appendData(byteArray, lower_scaled_value);
		appendData(byteArray, upper_scaled_value);
		appendData(byteArray, increment);
		appendData(byteArray, cal_type);
		return byteArray;
	}
	#define BAR 0
	#define STAIR 1
};

typedef quint16 SaFixedValId;
const int SA_FIX_UNSPEC = 0;
const int SA_FIX_INVALID_MASK = 1;
const int SA_FIX_PACER_MASK = 2;
const int SA_FIX_DEFIB_MARKER_MASK = 3;
const int SA_FIX_SATURATION = 4;
const int SA_FIX_QRS_MASK = 5;

class SaFixedValSpecEntry16{
public:
	SaFixedValSpecEntry16()
	{
		sa_fixed_val_id=0;
		sa_fixed_val=0;
	}
	SaFixedValSpecEntry16(SaFixedValId sa_fixed_val_id, quint16 sa_fixed_val)
	{
		this->sa_fixed_val_id=sa_fixed_val_id;
		this->sa_fixed_val=sa_fixed_val;
	};
	SaFixedValSpecEntry16(QDataStream &converter, int &size)
	{
		converter >> sa_fixed_val_id >> sa_fixed_val;
	};
	QByteArray getSaFixedValSpecEntry16()
	{
		QByteArray datagram;
		appendData(datagram, sa_fixed_val_id);
		appendData(datagram, sa_fixed_val);
		return datagram;
	};
	void print(std::string title="---------Start SaFixedValSpecEntry16---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "SaFixedValId sa_fixed_val_id: " << sa_fixed_val_id;
		qDebug() << "quint16 sa_fixed_val: " << sa_fixed_val;
		qDebug() << "---------End SaFixedValSpecEntry16---------";
	}
private:
    SaFixedValId sa_fixed_val_id;
    quint16 sa_fixed_val;
};

class SaFixedValSpec16{
public:
	SaFixedValSpec16()
	{
		this->count=0;
		this->length=0;
		value=new SaFixedValSpecEntry16*[count];
		for(int i=0; i<count; i++)
			value[i]= new SaFixedValSpecEntry16();
	}
	SaFixedValSpec16(quint16 count, quint16 length, SaFixedValSpecEntry16 *SaValue)
	{
		this->count=count;
		this->length=length;
		value=new SaFixedValSpecEntry16*[count];
		for(int i=0; i<count; i++)
			value[i]= new SaFixedValSpecEntry16(SaValue[i]);
	};
	SaFixedValSpec16(QDataStream &converter, int &size)
	{
		converter>> count >> length;
		value= new SaFixedValSpecEntry16*[count];
		for(int i =0; i < count; i++)
			value[i]=new SaFixedValSpecEntry16(converter, size);
		
	};
	~SaFixedValSpec16()
	{
		/*
		for(int i=0;i<count; i++)
			delete value[i];
		delete[] value;
		*/
	};
	QByteArray getSaFixedValSpec16(){
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);

		for(int i =0; i < count; i++){
			appendData(datagram, value[i]->getSaFixedValSpecEntry16());
		}
		return datagram;
	};
	void print(std::string title="---------Start SaFixedValSpec16---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0; i< count ; i++)
		{
			qDebug() << "SaFixedValSpecEntry16 **value " <<i << ": ";
			value[i]->print();
		}

		qDebug() <<"---------End SaFixedValSpec16---------";
	}
private:
    quint16 count;
    quint16 length;
    SaFixedValSpecEntry16 **value;
};

typedef quint16 MetricState;
const int METRIC_OFF = 0x8000;

typedef quint16 MeasureMode;
const int CO2_SIDESTREAM = 0x0400;
const int ECG_PACED = 0x0200;
const int ECG_NONPACED = 0x0100;
const int ECG_DIAG = 0x0080;
const int ECG_MONITOR = 0x0040;
const int ECG_FILTER = 0x0020;
const int ECG_MODE_EASI = 0x0008;
const int ECG_LEAD_PRIMARY = 0x0004;

class ScaleRangeSpec16{
public:
	ScaleRangeSpec16()
	{
		this->lower_absolute_value = 0;
		this->upper_absolute_value = 0;
		this->lower_scaled_value = 0;
		this->upper_scaled_value = 0;
	}

	ScaleRangeSpec16(FLOATType lower_absolute_value,
		FLOATType upper_absolute_value,
		quint16 lower_scaled_value,
		quint16 upper_scaled_value)
	{
		this->lower_absolute_value = lower_absolute_value;
		this->upper_absolute_value = upper_absolute_value;
		this->lower_scaled_value = lower_scaled_value;
		this->upper_scaled_value = upper_scaled_value;
		actual_lower_absolut_value=FLOATTypeToFloat(lower_absolute_value);
		actual_upper_absolut_value=FLOATTypeToFloat(upper_absolute_value);
	};
	ScaleRangeSpec16(QDataStream &converter, int &size)
	{
		converter 
			>> lower_absolute_value
			>> upper_absolute_value
			>> lower_scaled_value
			>> upper_scaled_value;
		actual_lower_absolut_value=FLOATTypeToFloat(lower_absolute_value);
		actual_upper_absolut_value=FLOATTypeToFloat(upper_absolute_value);
	};
	QByteArray getScaleRangeSpec16(){
		QByteArray datagram;
		appendData(datagram, lower_absolute_value);
		appendData(datagram, upper_absolute_value);
		appendData(datagram, lower_scaled_value);
		appendData(datagram, upper_scaled_value);
		return datagram;
	};
	void print(std::string title="---------Start ScaleRangeSpec16---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "FLOATType lower_absolute_value: " << lower_absolute_value;
		qDebug() << "FLOATType upper_absolute_value: " << upper_absolute_value;
		qDebug() << "quint16 lower_scaled_value: " << lower_scaled_value;
		qDebug() << "quint16 upper_scaled_value: " << upper_scaled_value;
		qDebug() << "actual lower_absolut_value: " << actual_lower_absolut_value;
		qDebug() << "actual upper_absolut_value: " << actual_upper_absolut_value;
		qDebug() << "---------End ScaleRangeSpec16---------";
	}
		 
private:
    FLOATType lower_absolute_value;
    FLOATType upper_absolute_value;
    quint16 lower_scaled_value;
    quint16 upper_scaled_value;
	float actual_lower_absolut_value;
	float actual_upper_absolut_value;
};

class ScaledRange16 {
public:
	ScaledRange16()
	{
		this->lower_scaled_value=0;
		this->lower_scaled_value=0;
	}
	ScaledRange16(quint16 lower_scaled_value, quint16 upper_scaled_value)
	{
		this->lower_scaled_value=lower_scaled_value;
		this->upper_scaled_value=upper_scaled_value;
	};
	ScaledRange16(QDataStream &converter, int &size)
	{
		converter >> lower_scaled_value 
			>> upper_scaled_value;
	};
	QByteArray getScaledRange16(){
		QByteArray datagram;
		appendData(datagram, lower_scaled_value);
		appendData(datagram, upper_scaled_value);
		return datagram;
	};
	void print(std::string title="---------Start ScaledRange16---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 lower_scaled_value: " << lower_scaled_value;
		qDebug() << "quint16 upper_scaled_value: " << upper_scaled_value;

		qDebug()<<"---------End ScaledRange16---------";
	}
private:
    quint16 lower_scaled_value;
    quint16 upper_scaled_value;
};

class SampleArray{
public:
	SampleArray()
	{
		this->length=0;
		this->value=new quint16[length/2];
	}
	SampleArray(quint16 length, quint16 *values)
	{
		this->length=length;
		this->value=new quint16[length/2];
		for(int i=0; i<length/2;i++)
			value[i]=values[i];
	};
	SampleArray(QDataStream &converter, int &size)
	{
		converter >> length;
		value=new quint16[length/2];


		for(int i=0; i<length/2;i++)
		{
			converter >> value[i];
		}
	};
	~SampleArray()
	{
		//delete[] value;
	};
	QByteArray getSampleArray(){
		QByteArray datagram;
		appendData(datagram, length);
		for(int i=0; i<length/2;i++)
			appendData(datagram, value[i]);
		return datagram;
	};
	void print(std::string title="---------Start sampleArray---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "Length: " << length;
		qDebug() << "---------End sampleArray---------";
	}
	int getSize(){return length/2;}
	quint16* getDataPointer(){return &value[0];}
private:
    quint16 length;
    //quint8 *value; from the guide
	quint16 *value;
};
	
class SaObsValue{
private:
    OIDType physio_id;
    MeasurementState state;
	SampleArray* sample_array;
public:
	SaObsValue()
	{
		this->physio_id=0;
		this->state=0;
		this->sample_array=new SampleArray();
	}
	SaObsValue(OIDType physio_id, MeasurementState state, SampleArray& samp_array)
	{
		this->physio_id=physio_id;
		this->state=state;
		this->sample_array=new SampleArray(samp_array);
	};
	SaObsValue(QDataStream &converter, int &size)
	{
		converter >> physio_id >> state;
		sample_array = new SampleArray(converter, size);
	};
	~SaObsValue()
	{
		//delete sample_array;
	};
	QByteArray getSaObsValue(){
		QByteArray datagram;
		appendData(datagram, physio_id);
		appendData(datagram, state);
		appendData(datagram, sample_array->getSampleArray());
		return datagram;
	};
	void print(std::string title="---------Start SaObsValue---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "OIDType physio_id: " << physio_id;
		qDebug() << "MeasurementState state: " << state;
		sample_array->print();
		qDebug() << "---------End SaObsValue---------";
	}
	OIDType getPhysioId()
	{
		return physio_id;
	}
	SampleArray* getSampleArray()
	{
		return sample_array;
	}
    
};

class SaObsValueCmp{
public:
	SaObsValueCmp()
	{
		this->count=0;
		this->length=0;
		value=new SaObsValue*[count];
	}
	SaObsValueCmp(quint16 count, quint16 length, SaObsValue * sa_obs_value)
	{
		this->count=count;
		this->length=length;
		value=new SaObsValue*[count];
		for(int i=0; i<count; i++)
			value[i]=new SaObsValue(sa_obs_value[i]);
	};
	SaObsValueCmp(QDataStream &converter, int &size)
	{
		converter >> count >> length;
		value= new SaObsValue*[count];

		for(int i =0; i < count; i++)
			value[i]=new SaObsValue(converter, size);
	};
	~SaObsValueCmp()
	{
		/*
		for(int i=0;i<count; i++)
			delete value[i];
		delete[] value;
		*/

	};
	QByteArray getSaObsValueCmp(){
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);

		for(int i =0; i <count; i++)
			appendData(datagram, value[i]->getSaObsValue());
    
		return datagram;
	};
	void print(std::string title="---------Start SaObsValueCmp---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0; i< count; i++)
		{
			qDebug() << "SaObsValue **value " << i <<": ";
			value[i]->print();
		}
		qDebug() << "---------End SaObsValueCmp---------";
	}
	quint16 getCount(){return count;}
	SaObsValue * getSaObsValue(int i){return value[i];}
private:
    quint16 count;
    quint16 length;
    SaObsValue **value;
};

typedef quint16 ApplProtoId;
const int AP_ID_ACSE = 1;
const int AP_ID_DATA_OUT = 5;
typedef quint16 TransProtoId;
const int TP_ID_UDP = 1;
typedef quint16 ProtoOptions;
const int P_OPT_WIRELESS = 0x8000;

class ProtoSupportEntry{
public:
	ProtoSupportEntry(ApplProtoId appl_proto, 
		TransProtoId trans_proto, 
		quint16 port_number,
		ProtoOptions options)
	{
		this->appl_proto=appl_proto;
		this->trans_proto=trans_proto;
		this->port_number=port_number;
		this->options=options;
	};
	ProtoSupportEntry(QDataStream &converter, int &size)
	{
		converter >> appl_proto
			>> trans_proto
			>> port_number
			>> options;
	};
	QByteArray getProtoSupportEntry(){
		QByteArray datagram;
		appendData(datagram, appl_proto);
		appendData(datagram, trans_proto);
		appendData(datagram, port_number);
		appendData(datagram, options);
		return datagram;
	};
	ApplProtoId getApplProto(){return appl_proto;}
	quint16 getPortNumber(){return port_number;}
	void print(std::string title="---------Start ProtoSupportEntry---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "ApplProtoId appl_proto: " << appl_proto;
		qDebug() << "TransProtoId trans_proto: " << trans_proto;
		qDebug() << "quint16 port_number: " << port_number;
		qDebug() << "ProtoOptions options: " << options;
		qDebug() << "---------End ProtoSupportEntry---------";
	}
private:
    ApplProtoId appl_proto;
    TransProtoId trans_proto;
    quint16 port_number;
    ProtoOptions options;
};

class MACAddress{
public:
	MACAddress()
	{
		for(int i=0; i<6; i++)
			this->value[i]=0;
	}
	MACAddress(quint8 MACvalue[6])
	{
		for(int i=0; i<6; i++)
			this->value[i]=MACvalue[i];
	};
	MACAddress(QDataStream &converter, int &size)
	{
		for(int i=0;i<6;i++)
			converter >> value[i];
	};
	QByteArray getMACAddress(){
		QByteArray datagram;
		for(int i=0;i<6;i++)
			appendData(datagram, value[i]);
    
		return datagram;
	};
private:
    quint8 value[6];
};

class IPAddress {
	public:
	IPAddress()
	{
		for(int i=0; i<4; i++)
			this->value[i]=0;
	}
	IPAddress(quint8 IPvalue[4])
	{
		for(int i=0; i<4; i++)
			this->value[i]=IPvalue[i];
	};
	IPAddress(QDataStream &converter, int &size)
	{
		for(int i=0; i<4; i++)
			converter >> value[i];
	};
	QByteArray getIPAddress(){
		QByteArray datagram;
		for(int i=0;i<4;i++)
			appendData(datagram, value[i]);
		return datagram;
	};
private:
    quint8 value[4];
};

class ProtoSupport{
public:
	ProtoSupport()
	{
		this->count=0;
		this->length=0;
		proto_support_entry=new ProtoSupportEntry*[count];
	}
	ProtoSupport(quint16 count, quint16 length, ProtoSupportEntry *p_s_entry)
	{
		this->count=count;
		this->length=length;
		proto_support_entry=new ProtoSupportEntry*[count];
		for(int i=0; i<count; i++)
			proto_support_entry[i]=new ProtoSupportEntry(p_s_entry[i]);
	};
	ProtoSupport(QDataStream &converter, int &size)
	{
		converter >> count >> length;
		proto_support_entry= new ProtoSupportEntry*[count];

		for(int i =0; i < count; i++)
			proto_support_entry[i]=new ProtoSupportEntry(converter, size);
	};
	~ProtoSupport()
	{
		/*
		for(int i=0;i<count; i++)
			delete proto_support_entry[i];
		delete[] proto_support_entry;
		*/
	};
	QByteArray getProtoSupport(){
		QByteArray datagram;
		appendData(datagram, count);
		appendData(datagram, length);

		for(int i =0; i < count; i++)
			appendData(datagram, proto_support_entry[i]->getProtoSupportEntry());

		return datagram;
	};
	ProtoSupportEntry* getProtoSupportEntry(ApplProtoId appl_proto)
	{
		//qDebug() << "getProtoSupportEntry. Count: " << count;
		for(int i=0; i< count;i++)
			if(proto_support_entry[i]->getApplProto()==appl_proto)
			{
				//qDebug() << i << ": " << proto_support_entry[i]->getPortNumber();
				return proto_support_entry[i];
				
			}
			return NULL;
			
	}
	void print(std::string title="---------Start ProtoSupport---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "quint16 count: " << count;
		qDebug() << "quint16 length: " << length;
		for(int i=0; i<count ;i++)
		{
			qDebug() << "ProtoSupportEntry **proto_support_entry" << i << ": ";
			proto_support_entry[i]->print();
		}

		qDebug() << "---------End ProtoSupport---------";

	}
private:

    quint16 count;
    quint16 length;
    ProtoSupportEntry **proto_support_entry;
};

class IpAddressInfo{
public:
	IpAddressInfo()
	{
		mac_address = new MACAddress();
		ip_address = new IPAddress();
		subnet_mask = new IPAddress();
	}
	IpAddressInfo(MACAddress& mac, IPAddress& ip, IPAddress& subnet)
	{
		this->mac_address=new MACAddress(mac);
		this->ip_address= new IPAddress(ip);
		this->subnet_mask= new IPAddress(subnet);
	};
	IpAddressInfo(QDataStream &converter, int &size)
	{
		mac_address = new MACAddress(converter, size);
		ip_address = new IPAddress(converter, size);
		subnet_mask = new IPAddress(converter, size);
	};
	~IpAddressInfo()
	{
		/*
		delete mac_address;
		delete ip_address;
		delete subnet_mask;
		*/
	};
	QByteArray getIpAddressInfo(){
		QByteArray datagram;
		appendData(datagram, mac_address->getMACAddress());
		appendData(datagram, ip_address->getIPAddress());
		appendData(datagram, subnet_mask->getIPAddress());
		return datagram;
	};
	void print(std::string title="---------Start IpAddressInfo---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "---------End IpAddressInfo---------";
	}
private:
    MACAddress *mac_address;
    IPAddress *ip_address;
    IPAddress *subnet_mask;
};

class PollMdibDataReply;
class PollMdibDataReplyExt;
class PollMdibDataReqExt;

class Object
{
public:
	Object()
	{
	    poll_data_req_period=new PollDataReqPeriod();
		number_of_prioritized_objects=0;
		poll_profile_support= new PollProfileSupport();
		poll_profile_ext= new PollProfileExt;
		length=0;
		//Numeric Object Attributes
		handle=0;
		type = new TYPE();
		nu_obs_value = new NuObsValue();
		nu_obs_val_cmp = new NuObsValueCmp();
		absolute_time = new AbsoluteTime();
		relative_time=0;
		text_id=0;
		string= new String();
		simple_colour=0;

		//Wave objects
		metric_spec=new MetricSpec();
		sa_spec= new SaSpec();
		sa_fixed_val_spec16= new SaFixedValSpec16();
		metric_state=0;
		oid_type=0;
		measure_mode=0;
		scale_range_spec16=new ScaleRangeSpec16();
		scaled_range_16= new ScaledRange16();
		sa_obs_value= new SaObsValue();
		sa_obs_value_cmp=new SaObsValueCmp();
		proto_support= new ProtoSupport();
		ip_address_info= new IpAddressInfo();
	};
	Object(OIDType id, quint16 length, QDataStream &converter);
	//template <typename Type>
	Object(OIDType id, quint16 length, void* attribute);
	QByteArray getObject();
	//Object(OIDType id, quint16 length, QDataStream &converter);
	~Object(){};
	void * getAttribute();
	void print(std::string title="---------Start OBJECT---------");
	OIDType getID();
	enum objectClasses
	{
		NOM_MOC_VMO=1,
		//VMO

		NOM_MOC_VMO_METRIC_ENUM=5,
		//Enumeration

		NOM_MOC_VMO_METRIC_NU=6,
		//Numeric

		NOM_MOC_VMO_METRIC_SA_RT=9,
		//Realtime Sample Array

		NOM_MOC_VMS_MDS=33,
		//MDS

		NOM_MOC_VMS_MDS_COMPOS_SINGLE_BED=35,
		//Composit Single Bed MDS

		NOM_MOC_VMS_MDS_SIMP=37,
		//Simple MDS

		NOM_MOC_BATT=41,
		//Battery

		NOM_MOC_PT_DEMOG=42,
		//Patient Demographics

		NOM_MOC_VMO_AL_MON=54,
		//Alert Monitor

		NOM_ACT_POLL_MDIB_DATA=3094,
		//Poll Action

		NOM_NOTI_MDS_CREAT=3334,
		//MDS Create

		NOM_NOTI_CONN_INDIC=3351,
		//Connect Indication

		NOM_DEV_METER_CONC_SKIN_GAS=4264,
		//Skin Gas

		NOM_DEV_METER_FLOW_BLD=4284,
		//Blood Flow

		NOM_DEV_ANALY_CONC_GAS_MULTI_PARAM_MDS=4113,
		//Gas Analyzer

		NOM_DEV_METER_CONC_SKIN_GAS_MDS=4265,
		//Skin Gas

		NOM_DEV_MON_PHYSIO_MULTI_PARAM_MDS=4429,
		//Multi-Param

		NOM_DEV_PUMP_INFUS_MDS=4449,
		//Pump Infus

		NOM_DEV_SYS_PT_VENT_MDS=4465,
		//Ventilator

		NOM_DEV_SYS_MULTI_MODAL_MDS=4493,
		//Multi-Modal MDS

		NOM_DEV_SYS_VS_CONFIG_MDS=5209,
		//config MDS

		NOM_DEV_SYS_VS_UNCONFIG_MDS=5213,
		//unconfig MDS

		NOM_DEV_ANALY_SAT_O2_VMD=4106,
		//sat O2

		NOM_DEV_ANALY_CONC_GAS_MULTI_PARAM_VMD=4114,
		//Gas

		NOM_DEV_ANALY_FLOW_AWAY_VMD=4130,
		//Flow Away

		NOM_DEV_ANALY_CARD_OUTPUT_VMD=4134,
		//C.O.

		NOM_DEV_ANALY_PRESS_BLD_VMD=4174,
		//Press

		NOM_DEV_ANALY_RESP_RATE_VMD=4186,
		//RR

		NOM_DEV_CALC_VMD=4206,
		//Calculation

		NOM_DEV_ECG_VMD=4262,
		//ECG

		NOM_DEV_METER_CONC_SKIN_GAS_VMD=4266,
		//Skin Gas

		NOM_DEV_EEG_VMD=4274,
		//EEG

		NOM_DEV_METER_TEMP_BLD_VMD=4350,
		//Blood Temp

		NOM_DEV_METER_TEMP_VMD=4366,
		//Temp

		NOM_DEV_MON_BLD_CHEM_MULTI_PARAM_VMD=4398,
		//Bld Chem

		NOM_DEV_SYS_PT_VENT_VMD=4466,
		//Ventilator

		NOM_DEV_SYS_MULTI_MODAL_VMD=4494,
		//Multi-Modal

		NOM_DEV_SYS_ANESTH_VMD=4506,
		//Aneshesia

		NOM_DEV_GENERAL_VMD=5122,
		//General

		NOM_DEV_ECG_RESP_VMD=5130,
		//ECG-Resp

		NOM_DEV_ARRHY_VMD=5134,
		//Arrythmia

		NOM_DEV_PULS_VMD=5138,
		//Pulse

		NOM_DEV_ST_VMD=5142,
		//ST

		NOM_DEV_CO2_VMD=5146,
		//CO2

		NOM_DEV_PRESS_BLD_NONINV_VMD=5150,
		//Noninv Press

		NOM_DEV_CEREB_PERF_VMD=5154,
		//Cereb Perf

		NOM_DEV_CO2_CTS_VMD=5158,
		//CO2 CTS

		NOM_DEV_CO2_TCUT_VMD=5162,
		//TcCO2

		NOM_DEV_O2_VMD=5166,
		//O2

		NOM_DEV_O2_CTS_VMD=5170,
		//CTS

		NOM_DEV_O2_TCUT_VMD=5174,
		//Tc02

		NOM_DEV_TEMP_DIFF_VMD=5178,
		//Diff Temp

		NOM_DEV_CNTRL_VMD=5182,
		//Control

		NOM_DEV_WEDGE_VMD=5190,
		//Wedge

		NOM_DEV_O2_VEN_SAT_VMD=5194,
		//O2 Vent Sat

		NOM_DEV_CARD_RATE_VMD=5202,
		//HR

		NOM_DEV_PLETH_VMD=5238,
		//Pleth

		NOM_SAT_O2_TONE_FREQ=61448,
		//Private Attribute

		NOM_OBJ_HIF_KEY=61584,
		//Key

		NOM_OBJ_DISP=61616,
		//Display

		NOM_OBJ_SOUND_GEN=61648,
		//Sound Generator

		NOM_OBJ_SETTING=61649,
		//Setting

		NOM_OBJ_PRINTER=61650,
		//Printer

		NOM_OBJ_EVENT=61683,
		//Event

		NOM_OBJ_BATT_CHARGER=61690,
		//Battery Charger

		NOM_OBJ_ECG_OUT=61691,
		//ECG out

		NOM_OBJ_INPUT_DEV=61692,
		//Input Device

		NOM_OBJ_NETWORK=61693,
		//Network

		NOM_OBJ_QUICKLINK=61694,
		//Quicklink Bar

		NOM_OBJ_SPEAKER=61695,
		//Speaker

		NOM_OBJ_PUMP=61716,
		//Pump

		NOM_OBJ_IR=61717,
		//IR

		NOM_ACT_POLL_MDIB_DATA_EXT=61755,
		//Extended Poll Action

		NOM_DEV_ANALY_PULS_CONT=61800,
		//Puls Cont

		NOM_DEV_ANALY_BISPECTRAL_INDEX_VMD=61806,
		//BIS

		NOM_DEV_HIRES_TREND=61820,
		//Hires Trend

		NOM_DEV_HIRES_TREND_MDS=61821,
		//Hires Trend

		NOM_DEV_HIRES_TREND_VMD=61822,
		//Hires Trend

		NOM_DEV_MON_PT_EVENT_VMD=61826,
		//Events

		NOM_DEV_DERIVED_MSMT=61828,
		//Derived Measurement

		NOM_DEV_DERIVED_MSMT_MDS=61829,
		//Derived Measurement

		NOM_DEV_DERIVED_MSMT_VMD=61830,
		//Derived Measurement

		NOM_OBJ_SENSOR=61902,
		//Sensor

		NOM_OBJ_XDUCR=61903,
		//Transducer

		NOM_OBJ_CHAN_1=61916,
		//Channel 1

		NOM_OBJ_CHAN_2=61917,
		//Channel 2

		NOM_OBJ_AWAY_AGENT_1=61918,
		//Agent 1

		NOM_OBJ_AWAY_AGENT_2=61919,
		//Agent 2

		NOM_OBJ_HIF_MOUSE=61983,
		//MOUSE

		NOM_OBJ_HIF_TOUCH=61984,
		//TOUCH

		NOM_OBJ_HIF_SPEEDPOINT=61985,
		//Speedpoint

		NOM_OBJ_HIF_ALARMBOX=61986,
		//Alarmbox

		NOM_OBJ_BUS_I2C=61987,
		//I2C Bus

		NOM_OBJ_CPU_SEC=61988,
		//2nd CPU

		NOM_OBJ_LED=61990,
		//LED

		NOM_OBJ_RELAY=61991,
		//Relay

		NOM_OBJ_BATT_1=61996,
		//Battery 1

		NOM_OBJ_BATT_2=61997,
		//Battery 2

		NOM_OBJ_DISP_SEC=61998,
		//2nd Display

		NOM_OBJ_AGM=61999,
		//AGM

		NOM_OBJ_TELEMON=62014,
		//TeleMon

		NOM_OBJ_XMTR=62015,
		//Transmitter

		NOM_OBJ_CABLE=62016,
		//Cable

		NOM_OBJ_TELEMETRY_XMTR=62053,
		//Telemetry Transmitter

		NOM_OBJ_DISP_THIRD=62073,
		//Third Display

		NOM_OBJ_BATT=62078,
		//Battery

		NOM_OBJ_BATT_TELE=62091,
		//Battery Tele

		NOM_DEV_PROT_WATCH_CHAN=62095,
		//Protocol Watch generic

		NOM_OBJ_PROT_WATCH_1=62097,
		//Protocol Watch Protocol No. 1

		NOM_OBJ_PROT_WATCH_2=62098,
		//Protocol Watch Protocol No. 2

		NOM_OBJ_PROT_WATCH_3=62099,
		//Protocol Watch Protocol No. 3

	};

	enum unitCodes
	{
		// NOS  ( no dimension )
		NOM_DIM_NOS	= 0,

		// ( / )
		NOM_DIM_DIV = 2,

		// -  ( no dimension )
		NOM_DIM_DIMLESS = 512,

		// % ( percentage )
		NOM_DIM_PERCENT = 544,

		// ppth  ( parts per thousand )
		NOM_DIM_PARTS_PER_THOUSAND = 576,

		// ppm  ( parts per million )
		NOM_DIM_PARTS_PER_MILLION = 608,

		// mol/mol  ( mole per mole )
		NOM_DIM_X_MOLE_PER_MOLE = 864,

		// ppb  ( parts per billion )
		NOM_DIM_PARTS_PER_BILLION = 672,

		// ppt  ( parts per trillion )
		NOM_DIM_PARTS_PER_TRILLION = 704,

		// pH ( pH )
		NOM_DIM_PH = 992,

		// drop  ( vital signs count drop )
		NOM_DIM_DROP = 1024,

		// rbc  ( vital signs count red blood cells )
		NOM_DIM_RBC = 1056,

		// beat  ( vital signs count beat )
		NOM_DIM_BEAT = 1088,

		// breath  ( vital signs count breath )
		NOM_DIM_BREATH = 1120,

		// cell  ( vital signs count cells )
		NOM_DIM_CELL = 1152,

		// cough  ( vital signs count cough )
		NOM_DIM_COUGH = 1184,

		// sigh  ( vital signs count sigh )
		NOM_DIM_SIGH = 1216,

		// %PCV  ( percent of packed cell volume )
		NOM_DIM_PCT_PCV = 1248,

		// m ( meter )
		NOM_DIM_X_M = 1280,

		// cm ( centimeter )
		NOM_DIM_CENTI_M = 1297,

		// mm ( millimeter )
		NOM_DIM_MILLI_M = 1298,

		// µm  ( micro-meter )
		NOM_DIM_MICRO_M = 1299,

		// in  ( inch )
		NOM_DIM_X_INCH = 1376,

		// ml/m2  ( used e.g. for SI and ITBVI )
		NOM_DIM_MILLI_L_PER_M_SQ = 1426,

		// /m  ( per meter )
		NOM_DIM_PER_X_M = 1440,

		// /mm  ( per millimeter )
		NOM_DIM_PER_MILLI_M = 1458,

		// m2  ( used e.g. for BSA calculation )
		NOM_DIM_SQ_X_M = 1472,

		// in2  ( used e.g. for BSA calculation )
		NOM_DIM_SQ_X_INCH = 1504,

		// m3  ( cubic meter )
		NOM_DIM_CUBIC_X_M = 1568,

		// cm3  ( cubic centimeter )
		NOM_DIM_CUBIC_CENTI_M = 1585,

		// l  ( liter )
		NOM_DIM_X_L = 1600,

		// ml  ( milli-liters used e.g. for EVLW ITBV SV )
		NOM_DIM_MILLI_L = 1618,

		// ml/breath  ( milli-liter per breath )
		NOM_DIM_MILLI_L_PER_BREATH = 1650,

		// /cm3  ( per cubic centimeter )
		NOM_DIM_PER_CUBIC_CENTI_M = 1681,

		// /l  ( per liter )
		NOM_DIM_PER_X_L = 1696,

		// = 1/nl  ( per nano-liter )
		NOM_DIM_PER_NANO_LITER = 1716,

		// g  ( gram )
		NOM_DIM_X_G = 1728,

		// kg ( kilo-gram )
		NOM_DIM_KILO_G = 1731,

		// mg ( milli-gram )
		NOM_DIM_MILLI_G = 1746,

		// µg ( micro-gram )
		NOM_DIM_MICRO_G = 1747,

		// ng ( nono-gram )
		NOM_DIM_NANO_G = 1748,

		// lb  ( pound )
		NOM_DIM_X_LB = 1760,

		// oz ( ounce )
		NOM_DIM_X_OZ = 1792,

		// /g  ( per gram )
		NOM_DIM_PER_X_G = 1824,

		// g-m  ( used e.g. for LVSW RVSW )
		NOM_DIM_X_G_M = 1856,

		// kg-m  ( used e.g. for RCW LCW )
		NOM_DIM_KILO_G_M = 1859,

		// g-m/m2  ( used e.g. for LVSWI and RVSWI )
		NOM_DIM_X_G_M_PER_M_SQ = 1888,

		// kg-m/m2  ( used e.g. for LCWI and RCWI )
		NOM_DIM_KILO_G_M_PER_M_SQ = 1891,

		// kg-m2  ( gram meter squared )
		NOM_DIM_KILO_G_M_SQ = 1923,

		// kg/m2  ( kilo-gram per square meter )
		NOM_DIM_KG_PER_M_SQ = 1955,

		// kg/m3  ( kilo-gram per cubic meter )
		NOM_DIM_KILO_G_PER_M_CUBE = 1987,

		// g/cm3  ( gram per cubic meter )
		NOM_DIM_X_G_PER_CM_CUBE = 2016,

		// mg/cm3  ( milli-gram per cubic centimeter )
		NOM_DIM_MILLI_G_PER_CM_CUBE = 2034,

		// µg/cm3 ( micro-gram per cubic centimeter )
		NOM_DIM_MICRO_G_PER_CM_CUBE = 2035,

		// ng/cm3  ( nano-gram per cubic centimeter )
		NOM_DIM_NANO_G_PER_CM_CUBE = 2036,

		// g/l  ( gram per liter )
		NOM_DIM_X_G_PER_L = 2048,

		// g/dl  ( used e.g. for Hb )
		NOM_DIM_X_G_PER_DL = 2112,

		// mg/dl  ( milli-gram per deciliter )
		NOM_DIM_MILLI_G_PER_DL = 2130,

		// g/ml  ( gram per milli-liter )
		NOM_DIM_X_G_PER_ML = 2144,

		// mg/ml ( milli-gram per milli-liter )
		NOM_DIM_MILLI_G_PER_ML = 2162,

		// µg/ml ( micro-gram per milli-liter )
		NOM_DIM_MICRO_G_PER_ML = 2163,

		// ng/ml  ( nano-gram per milli-liter )
		NOM_DIM_NANO_G_PER_ML = 2164,

		// sec  ( seconds )
		NOM_DIM_SEC = 2176,

		// msec ( milli-seconds )
		NOM_DIM_MILLI_SEC = 2194,

		// µsec ( micro-seconds )
		NOM_DIM_MICRO_SEC = 2195,

		// min  ( minutes )
		NOM_DIM_MIN = 2208,

		// hrs ( hours )
		NOM_DIM_HR = 2240,

		// days ( days )
		NOM_DIM_DAY = 2272,

		// weeks ( weeks )
		NOM_DIM_WEEKS = 2304,

		// months  ( months )
		NOM_DIM_MON = 2336,

		// years  ( years )
		NOM_DIM_YR = 2368,

		// TOD  ( time of day )
		NOM_DIM_TOD = 2400,

		// date  ( date )
		NOM_DIM_DATE = 2432,

		// /sec  ( per second )
		NOM_DIM_PER_X_SEC = 2464,

		// Hz ( hertz )
		NOM_DIM_HZ = 2496,

		// /min  ( per minute used e.g. for the PVC count numerical value )
		NOM_DIM_PER_MIN = 2528,

		// /hour  ( per hour )
		NOM_DIM_PER_HR = 2560,

		// /day  ( per day )
		NOM_DIM_PER_DAY = 2592,

		// /week  ( per week )
		NOM_DIM_PER_WK = 2624,

		// /month  ( per month )
		NOM_DIM_PER_MO = 2656,

		// /year  ( per year )
		NOM_DIM_PER_YR = 2688,

		// bpm  ( beats per minute used e.g. for HR/PULSE )
		NOM_DIM_BEAT_PER_MIN = 2720,

		// puls/min  ( puls per minute )
		NOM_DIM_PULS_PER_MIN = 2752,

		// rpm  ( respiration breathes per minute )
		NOM_DIM_RESP_PER_MIN = 2784,

		// m/sec  ( meter per second )
		NOM_DIM_X_M_PER_SEC = 2816,

		// mm/sec  ( speed for recordings )
		NOM_DIM_MILLI_M_PER_SEC = 2834,

		// l/min/m2  ( used for CI )
		NOM_DIM_X_L_PER_MIN_PER_M_SQ = 2848,

		// ml/min/m2  ( used for DO2I VO2I O2AVI )
		NOM_DIM_MILLI_L_PER_MIN_PER_M_SQ = 2866,

		// m2/sec  ( square meter per second )
		NOM_DIM_SQ_X_M_PER_SEC = 2880,

		// cm2/sec ( square centimeter per second )
		NOM_DIM_SQ_CENTI_M_PER_SEC = 2897,

		// m3/sec  ( cubic meter per second )
		NOM_DIM_CUBIC_X_M_PER_SEC = 2912,

		// cm3/sec  ( cubic centimeter per second )
		NOM_DIM_CUBIC_CENTI_M_PER_SEC = 2929,

		// l/sec  ( liter per second )
		NOM_DIM_X_L_PER_SEC = 3040,

		// l/min  ( liter per minutes )
		NOM_DIM_X_L_PER_MIN = 3072,

		// dl/min  ( deciliter per second )
		NOM_DIM_DECI_L_PER_MIN = 3088,

		// ml/min  ( used for DO2 VO2 ALVENT )
		NOM_DIM_MILLI_L_PER_MIN = 3090,

		// l/hour  ( liter per hour )
		NOM_DIM_X_L_PER_HR = 3104,

		// ml/hour  ( milli-liter per hour )
		NOM_DIM_MILLI_L_PER_HR = 3122,

		// l/day  ( liter per day )
		NOM_DIM_X_L_PER_DAY = 3136,

		// ml/day  ( milli-liter per day )
		NOM_DIM_MILLI_L_PER_DAY = 3154,

		// ml/kg  ( used e.g. for EVLWI )
		NOM_DIM_MILLI_L_PER_KG = 3186,

		// kg/sec  ( kilo-gram per second )
		NOM_DIM_KILO_G_PER_SEC = 3299,

		// g/min  ( gram per minute )
		NOM_DIM_X_G_PER_MIN = 3328,

		// kg/min  ( kilo-gram per minute )
		NOM_DIM_KILO_G_PER_MIN = 3331,

		// mg/min  ( milli-gram per minute )
		NOM_DIM_MILLI_G_PER_MIN = 3346,

		// µg/min  ( micro-gram per minute )
		NOM_DIM_MICRO_G_PER_MIN = 3347,

		// ng/min  ( nano-gram per minute )
		NOM_DIM_NANO_G_PER_MIN = 3348,

		// g/hour  ( gram per hour )
		NOM_DIM_X_G_PER_HR = 3360,

		// kg/hour  ( kilo-gram per hour )
		NOM_DIM_KILO_G_PER_HR = 3363,

		// mg/hour  ( milli-gram per hour )
		NOM_DIM_MILLI_G_PER_HR = 3378,

		// µg/hour  ( micro-gram per hour )
		NOM_DIM_MICRO_G_PER_HR = 3379,

		// ng/hr  ( nano-gram per hour )
		NOM_DIM_NANO_G_PER_HR = 3380,

		// kg/day  ( kilo-gram per day )
		NOM_DIM_KILO_G_PER_DAY = 3395,

		// g/kg/min  ( gram per kilo-gram per minute )
		NOM_DIM_X_G_PER_KG_PER_MIN = 3456,

		// mg/kg/min  ( milli-gram per kilo-gram per minute )
		NOM_DIM_MILLI_G_PER_KG_PER_MIN = 3474,

		// µg/kg/min  ( micro-gram per kilo-gram per minute )
		NOM_DIM_MICRO_G_PER_KG_PER_MIN = 3475,

		// ng/kg/min  ( nano-gram per kilo-gram per minute )
		NOM_DIM_NANO_G_PER_KG_PER_MIN = 3476,

		// g/kg/hour  ( gram per kilo-gram per hour )
		NOM_DIM_X_G_PER_KG_PER_HR = 3488,

		// mg/kg/hour  ( mili-gram per kilo-gram per hour )
		NOM_DIM_MILLI_G_PER_KG_PER_HR = 3506,

		// µg/kg/hour ( micro-gram per kilo-gram per hour )
		NOM_DIM_MICRO_G_PER_KG_PER_HR = 3507,

		// ng/kg/hour  ( nano-gram per kilo-gram per hour )
		NOM_DIM_NANO_G_PER_KG_PER_HR = 3508,

		// kg/l/sec  ( kilo-gram per liter per second )
		NOM_DIM_KILO_G_PER_L_SEC = 3555,

		// kg/m/sec  ( kilo-gram per meter per second )
		NOM_DIM_KILO_G_PER_M_PER_SEC = 3683,

		// kg-m/sec  ( kilo-gram meter per second )
		NOM_DIM_KILO_G_M_PER_SEC = 3715,

		// N-s  ( newton seconds )
		NOM_DIM_X_NEWTON_SEC = 3744,

		// N  ( newton )
		NOM_DIM_X_NEWTON = 3776,

		// Pa  ( pascal )
		NOM_DIM_X_PASCAL = 3840,

		// hPa ( hekto-pascal )
		NOM_DIM_HECTO_PASCAL = 3842,

		// kPa ( kilo-pascal )
		NOM_DIM_KILO_PASCAL = 3843,

		// mmHg  ( mm mercury )
		NOM_DIM_MMHG = 3872,

		// cmH2O  ( centimeter H20 )
		NOM_DIM_CM_H2O = 3904,

		// mBar ( milli-bar )
		NOM_DIM_MILLI_BAR = 3954,

		// J  ( Joules )
		NOM_DIM_X_JOULES = 3968,

		// eV  ( electronvolts )
		NOM_DIM_EVOLT = 4000,

		// W  ( watt )
		NOM_DIM_X_WATT = 4032,

		// mW ( milli-watt )
		NOM_DIM_MILLI_WATT = 4050,

		// nW ( nano-watt )
		NOM_DIM_NANO_WATT = 4052,

		// pW ( pico-watt )
		
		NOM_DIM_PICO_WATT = 4053,

		// Dyn-sec/cm^5 ( dyne second per cm^5 )
		NOM_DIM_X_DYNE_PER_SEC_PER_CM5 = 4128,

		// A  ( ampere )
		NOM_DIM_X_AMPS = 4160,

		// mA  ( milli-ampereused e.g. for the battery indications )
		NOM_DIM_MILLI_AMPS = 4178,

		// C ( coulomb )
		NOM_DIM_X_COULOMB = 4192,

		// µC ( micro-coulomb )
		NOM_DIM_MICRO_COULOMB = 4211,

		// V ( volts )
		NOM_DIM_X_VOLT = 4256,

		// mV  ( milli-volt )
		NOM_DIM_MILLI_VOLT = 4274,

		// µV  ( micro-volt )
		NOM_DIM_MICRO_VOLT = 4275,

		// Ohm ( Ohm )
		NOM_DIM_X_OHM = 4288,

		// kOhm  ( kilo-ohm )
		NOM_DIM_OHM_K = 4291,

		// F ( farad )
		NOM_DIM_X_FARAD = 4352,

		// °K ( kelvin )
		NOM_DIM_KELVIN = 4384,

		// °F ( degree-fahrenheit )
		NOM_DIM_FAHR = 4416,

		// cd  ( candela )
		NOM_DIM_X_CANDELA = 4480,

		// mOsm  ( milli-osmole )
		NOM_DIM_MILLI_OSM = 4530,

		// mol ( mole )
		NOM_DIM_X_MOLE = 4544,

		// mmol  ( milli-mole )
		NOM_DIM_MILLI_MOLE = 4562,

		// mEq ( milli-equivalents )
		NOM_DIM_MILLI_EQUIV = 4594,

		// mOsm/l  ( milli-osmole per liter )
		NOM_DIM_MILLI_OSM_PER_L = 4626,

		// mmol/l  ( used for HB )
		NOM_DIM_MILLI_MOLE_PER_L = 4722,

		// µmol/l  ( micro-mol per liter )
		NOM_DIM_MICRO_MOLE_PER_L = 4723,

		// mEq/l  ( milli-equivalents per liter )
		NOM_DIM_MILLI_EQUIV_PER_L = 4850,

		// mEq/day  ( milli-equivalents per day )
		NOM_DIM_MILLI_EQUIV_PER_DAY = 5202,

		// i.u.  ( international unit )
		NOM_DIM_X_INTL_UNIT = 5472,

		// mi.u.  ( mili-international unit )
		NOM_DIM_MILLI_INTL_UNIT = 5490,

		// i.u./cm3  ( international unit per cubic centimeter )
		NOM_DIM_X_INTL_UNIT_PER_CM_CUBE = 5504,

		// mi.u./cm3 ( mili-international unit per cubic centimeter )
		NOM_DIM_MILLI_INTL_UNIT_PER_CM_CUBE = 5522,

		// i.u./ml  ( international unit per milli-liter )
		
		NOM_DIM_X_INTL_UNIT_PER_ML = 5600,

		// i.u./min  ( international unit per minute )
		NOM_DIM_X_INTL_UNIT_PER_MIN = 5664,

		// mi.u./ml ( milli-international unit per milli-liter )
		NOM_DIM_MILLI_INTL_UNIT_PER_ML = 5618,

		// mi.u./min  ( milli-international unit per minute )
		NOM_DIM_MILLI_INTL_UNIT_PER_MIN = 5682,

		// i.u./hour  ( international unit per hour )
		NOM_DIM_X_INTL_UNIT_PER_HR = 5696,

		// mi.u./hour  ( milli-international unit per hour )
		NOM_DIM_MILLI_INTL_UNIT_PER_HR = 5714,

		// i.u./kg/min  ( international unit per kilo-gram per minute )
		NOM_DIM_X_INTL_UNIT_PER_KG_PER_MIN = 5792,

		// mi.u./kg/min  ( milli-international unit per kilo-gram per minute )
		NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_MIN = 5810,

		// i.u./kg/hour  ( international unit per kilo-gram per hour )
		NOM_DIM_X_INTL_UNIT_PER_KG_PER_HR = 5824,

		// mi.u./kg/hour  ( milli-international unit per kilo-gram per hour )
		NOM_DIM_MILLI_INTL_UNIT_PER_KG_PER_HR = 5842,

		// ml/cmH2O  ( milli-liter per centimeter H2O )
		NOM_DIM_MILLI_L_PER_CM_H2O = 5906,

		// cmH2O/l/sec  ( centimeter H2O per second )
		NOM_DIM_CM_H2O_PER_L_PER_SEC = 5920,

		// ml2/sec  ( milli-liter per second )
		NOM_DIM_MILLI_L_SQ_PER_SEC = 5970,

		// cmH2O/%  ( centimeter H2O per percent )
		NOM_DIM_CM_H2O_PER_PERCENT = 5984,

		// DS*m2/cm5  ( used for SVRI and PVRI )
		NOM_DIM_DYNE_SEC_PER_M_SQ_PER_CM_5 = 6016,

		// °C ( degree-celsius )
		NOM_DIM_DEGC = 6048,

		// cmH2O/l  ( centimeter H2O per liter )
		NOM_DIM_CM_H2O_PER_L = 6144,

		// mmHg/%  ( milli-meter mercury per percent )
		NOM_DIM_MM_HG_PER_PERCENT = 6176,

		// kPa/%  ( kilo-pascal per percent )
		NOM_DIM_KILO_PA_PER_PERCENT = 6211,

		// l/mmHg (liter per mmHg)
		NOM_DIM_X_L_PER_MM_HG = 6272,

		// ml/mmHg (milli-liter per milli-meter Hg)
		NOM_DIM_MILLI_L_PER_MM_HG = 6290,

		// mAh  ( milli-ampere per hour used e.g. for the battery indications )
		NOM_DIM_MILLI_AMP_HR = 6098,

		// ml/dl  ( used for CaO2 CvO2 Ca-vO2 )
		NOM_DIM_MILLI_L_PER_DL = 6418,

		// dB ( decibel )
		NOM_DIM_DECIBEL = 6432,

		// g/mg  ( gram per milli-gram )
		NOM_DIM_X_G_PER_MILLI_G = 6464,

		// mg/mg  ( milli-gram per milli-gram )
		NOM_DIM_MILLI_G_PER_MILLI_G = 6482,

		// bpm/l  ( beats per minute per liter )
		NOM_DIM_BEAT_PER_MIN_PER_X_L = 6496,

		// bpm/ml  ( beats per minute per milli-liter )
		NOM_DIM_BEAT_PER_MIN_PER_MILLI_L = 6514,

		// 1/(min*l)  ( per minute per liter )
		
		NOM_DIM_PER_X_L_PER_MIN = 6528,

		// m/min  ( meter per minute )
		NOM_DIM_X_M_PER_MIN = 6560,

		// cm/min  ( speed for recordings )
		NOM_DIM_CENTI_M_PER_MIN = 6577,

		// pg/ml  ( pico-gram per milli-liter )
		NOM_DIM_PICO_G_PER_ML  = 2165 ,

		// ug/l  ( micro-gram per liter )
		NOM_DIM_MICRO_G_PER_L  = 2067 ,

		// ng/l  ( nano-gram per liter )
		NOM_DIM_NANO_G_PER_L = 2068 ,

		// /mm3( per cubic millimeter )  
		NOM_DIM_PER_CUBIC_MILLI_M  = 1682,
 
		// mm3 ( cubic milli-meter )
		NOM_DIM_CUBIC_MILLI_M  = 1586 ,

		// u/l  ( intl. units per liter )
		NOM_DIM_X_INTL_UNIT_PER_L  = 5568 ,

		// /l  ( 10^6 intl. units per liter )
		NOM_DIM_MEGA_INTL_UNIT_PER_L = 5573,

		// mol/kg  ( mole per kilo-gram )
		NOM_DIM_MILLI_MOL_PER_KG  = 4946 ,

		// mcg/dl  ( micro-gram per deci-liter )
		NOM_DIM_MICRO_G_PER_DL  = 2131 ,

		// mg/l  ( milli-gram per liter )
		NOM_DIM_MILLI_G_PER_L  = 2066 ,

		// /ul  ( micro-liter )
		NOM_DIM_PER_MICRO_L  = 1715 ,

		// complx  ( - )
		NOM_DIM_COMPLEX = 61440,

		// count  ( count as a dimension )
		NOM_DIM_COUNT = 61441,

		// part ( part )
		NOM_DIM_PART = 61442,

		// puls  ( puls )
		NOM_DIM_PULS = 61443,

		// µV p-p  ( micro-volt peak to peak )
		NOM_DIM_UV_PP = 61444,

		// µV2  ( micor-volt square )
		NOM_DIM_UV_SQ = 61445,

		// lumen  ( lumen )
		NOM_DIM_LUMEN = 61447,

		// lb/in2  ( pound per square inch )
		NOM_DIM_LB_PER_INCH_SQ = 61448,

		// mmHg/s  ( milli-meter mercury per second )
		NOM_DIM_MM_HG_PER_SEC = 61449,

		// ml/s ( milli-liter per second )
		NOM_DIM_ML_PER_SEC  = 61450 ,

		// bpm/ml ( beat per minute per milli-liter )
		NOM_DIM_BEAT_PER_MIN_PER_ML_C = 61451,

		// J/day ( joule per day )
		NOM_DIM_X_JOULE_PER_DAY = 61536,

		// kJ/day  ( kilo joule per day )
		NOM_DIM_KILO_JOULE_PER_DAY  = 61539,

		// MJ/day  ( mega joule per day )
		NOM_DIM_MEGA_JOULE_PER_DAY  = 61540,

		// cal  ( calories )
		NOM_DIM_X_CALORIE  = 61568,

		// kcal  ( kilo calories )
		NOM_DIM_KILO_CALORIE  = 61571,

		// 10**6 cal ( million calories )
		NOM_DIM_MEGA_CALORIE = 61572,

		// cal/day ( calories per day )
		NOM_DIM_X_CALORIE_PER_DAY = 61600,

		// kcal/day ( kilo-calories per day )
		NOM_DIM_KILO_CALORIE_PER_DAY = 61603,

		// Mcal/day ( mega calories per day )
		NOM_DIM_MEGA_CALORIE_PER_DAY = 61604,

		// cal/ml ( calories per milli-liter )
		NOM_DIM_X_CALORIE_PER_ML  = 61632,

		// kcal/ml ( kilo calories per ml )
		NOM_DIM_KILO_CALORIE_PER_ML = 61635,

		// J/ml  ( Joule per milli-liter )
		NOM_DIM_X_JOULE_PER_ML = 61664,

		// kJ/ml ( kilo-joules per milli-liter )
		NOM_DIM_KILO_JOULE_PER_ML = 61667,

		// RPM ( revolutions per minute )
		NOM_DIM_X_REV_PER_MIN = 61696,

		// l/(mn*l*kg) ( per minute per liter per kilo )
		NOM_DIM_PER_L_PER_MIN_PER_KG = 61728,

		// l/mbar ( liter per milli-bar )
		NOM_DIM_X_L_PER_MILLI_BAR = 61760,

		// ml/mbar ( milli-liter per milli-bar )
		NOM_DIM_MILLI_L_PER_MILLI_BAR = 61778,

		// l/kg/hr  ( liter per kilo-gram per hour )
		NOM_DIM_X_L_PER_KG_PER_HR = 61792,

		// ml/kg/hr ( milli-liter per kilogram per hour )
		NOM_DIM_MILLI_L_PER_KG_PER_HR = 61810,

		// bar/l/s  ( bar per liter per sec )
		NOM_DIM_X_BAR_PER_LITER_PER_SEC = 61824,

		// mbar/l/s  ( milli-bar per liter per sec )
		NOM_DIM_MILLI_BAR_PER_LITER_PER_SEC = 61842,

		// bar/l  ( bar per liter )
		NOM_DIM_X_BAR_PER_LITER = 61856,

		// mbar/l  ( bar per liter )
		NOM_DIM_MILLI_BAR_PER_LITER = 61874,

		// V/mV  ( volt per milli-volt )
		NOM_DIM_VOLT_PER_MILLI_VOLT = 61888,

		// cmH2O/uV  ( cm H2O per micro-volt )
		NOM_DIM_CM_H2O_PER_MICRO_VOLT = 61920,

		// J/l  ( joule per liter )
		NOM_DIM_X_JOULE_PER_LITER = 61952,

		// l/bar  ( liter per bar )
		NOM_DIM_X_L_PER_BAR = 61984,

		// m/mV  ( meter per milli-volt )
		NOM_DIM_X_M_PER_MILLI_VOLT = 62016,

		// mm/mV  ( milli-meter per milli-volt )
		NOM_DIM_MILLI_M_PER_MILLI_VOLT = 62034,

		// l/min/kg  ( liter per minute per kilo-gram )
		NOM_DIM_X_L_PER_MIN_PER_KG = 62048,

		// ml/min/kg  ( milli-liter per minute per kilo-gram )
		NOM_DIM_MILLI_L_PER_MIN_PER_KG = 62066,

		// Pa/l/s  ( pascal per liter per sec )
		NOM_DIM_X_PASCAL_PER_L_PER_SEC = 62080,

		// hPa/l/s  ( hPa per liter per sec )
		NOM_DIM_HECTO_PASCAL_PER_L_PER_SEC = 62082,

		// kPa/l/s  ( kPa per liter per sec )
		NOM_DIM_KILO_PASCAL_PER_L_PER_SEC = 62083,

		// ml/Pa  ( milli-liter per pascal )
		NOM_DIM_MILLI_L_PER_X_PASCAL = 62112,

		// ml/hPa ( milli-liter per hecto-pascal )
		NOM_DIM_MILLI_L_PER_HECTO_PASCAL = 62114,

		// ml/kPa  ( milli-liter per kilo-pascal )
		NOM_DIM_MILLI_L_PER_KILO_PASCAL = 62115,

		// mmHg/l/s ( mm )
		NOM_DIM_MM_HG_PER_X_L_PER_SEC = 62144,

		// mol/h  ( mole per hour )
		NOM_DIM_X_MOLE_PER_HR = 62176,

		// mmol/h  ( milli-mol per hour )
		NOM_DIM_MILLI_MOLE_PER_HR = 62194,

		// l/beat  ( liter per beat ,)
		NOM_DIM_X_L_PER_BEAT = 62208,
		// ml/beat  ( milli-liter per beat )
		NOM_DIM_MILLI_L_PER_BEAT = 62226,

		// l/beat/m2  ( liter per beat per square meter )
		NOM_DIM_X_L_PER_BEAT_PER_M_SQ = 62240,

		// ml/beat/m2  ( milli-liter per beat per square meter )
		NOM_DIM_MILLI_L_PER_BEAT_PER_M_SQ = 62258,

		// bar/s  ( bar per second )
		NOM_DIM_X_BAR_PER_SEC = 62272,

		// mbar/s  ( milli-bar per second )
		NOM_DIM_MILLI_BAR_PER_SEC = 62290,

		// pascal/l  ( pascal per liter )
		NOM_DIM_X_PASCAL_PER_L = 62304,

		// kpascal/l  ( kilo pascal per liter )
		NOM_DIM_KILO_PASCAL_PER_L = 62307,

		// mmHg/l  ( mmHg per liter )
		NOM_DIM_MM_HG_PER_L = 62336,

		// vol%/l  ( volume percent per liter )
		NOM_DIM_VOL_PERCENT_PER_L = 62368,

	};
	enum physicalIdentifiersOfInterest
	{
		//Heart rate
		NLS_NOM_ECG_CARD_BEAT_RATE	= 0x00024182,
		//Arterial Oxigen Saturation
		NLS_NOM_PULS_OXIM_SAT_O2	= 0x00024BB8,
		//Arterial Blood Pressure (ABP)
		NLS_NOM_PRESS_BLD_ART_ABP	= 0x00024A14,
		//Arterial Blood Pressure (ART)
		NLS_NOM_PRESS_BLD_ART		= 0x00024A10,
		//Central Venous Pressure (CVP)
		NLS_NOM_PRESS_BLD_VEN_CENT	= 0x00024A44,
		//CCO Continuous Cardiac Output
		NLS_NOM_OUTPUT_CARD_CTS		= 0x00024BDC,
		//Stroke Volume
		NLS_NOM_VOL_BLD_STROKE		= 0x00024B84,
		//Cardiac Output
		NLS_NOM_OUTPUT_CARD			= 0x00024B04
	};
	enum attributeIdentifiers
	{
		NOM_ATTR_TIME_PD_POLL = 61758,
		NOM_ATTR_POLL_OBJ_PRIO_NUM = 61992,
		NOM_POLL_PROFILE_SUPPORT = 1,
		NOM_ATTR_POLL_PROFILE_EXT = 61441,
		NOM_ATTR_ID_HANDLE =2337,
		NOM_ATTR_ID_TYPE =2351,
		NOM_ATTR_NU_VAL_OBS =2384, 
		NOM_ATTR_NU_CMPD_VAL_OBS =2379,
		NOM_ATTR_TIME_STAMP_ABS =2448,
		NOM_ATTR_TIME_STAMP_REL =2449,
		NOM_ATTR_ID_LABEL =2340,
		NOM_ATTR_ID_LABEL_STRING =2343,
		NOM_ATTR_COLOR =2321,
		NOM_ATTR_METRIC_SPECN =2367,
		NOM_ATTR_SA_SPECN =2413,
		NOM_ATTR_SA_FIXED_VAL_SPECN =2582,
		NOM_ATTR_TIME_PD_SAMP =2445,
		NOM_ATTR_METRIC_STAT =2368,
		NOM_ATTR_UNIT_CODE =2454,
		NOM_ATTR_MODE_MSMT =2373,
		NOM_ATTR_METRIC_INFO_LABEL =2364,
		NOM_ATTR_METRIC_INFO_LABEL_STR =2365,
		NOM_ATTR_SCALE_SPECN_I16 =2415,
		NOM_ATTR_SA_RANGE_PHYS_I16 =2410,
		NOM_ATTR_SA_VAL_OBS =2414,
		NOM_ATTR_SA_CMPD_VAL_OBS =2407,
		NOM_ATTR_SA_CALIB_I16 = 2404,
		NOM_ATTR_PCOL_SUPPORT =61697,
		NOM_ATTR_NET_ADDR_INFO =61696,
		NOM_ATTR_TIME_ABS=2439,
		NOM_ATTR_POLL_RTSA_PRIO_LIST=62010,
		NOM_ATTR_POLL_NU_PRIO_LIST=62009
	};
	enum attributeGroups
	{
		//All groups:
		ALL_Groups=0,

		//Handle, Type, Metric Specification, Sample Array
		//Specification, Sample Array Fixed Value Specification,
		//Sample Period:
		NOM_ATTR_GRP_VMO_STATIC = 2065,

		//Label, Label String, Metric State, Unit Code,
		//Color, Measure Mode, Metric Info Label, Metric Info
		//Label String, Scale and Range Specification,
		//Sample Array Physiological Range, Visual Grid,
		//Sample Array Calibration Specification:
		NOM_ATTR_GRP_VMO_DYN = 2064,

		//Sample Array Observed Value, Compound Sample Array
		//Observed Value: 
		NOM_ATTR_GRP_METRIC_VAL_OBS = 2051
	};
private: 
	OIDType ID;
	quint16 length;
    PollDataReqPeriod *poll_data_req_period;
    quint16 number_of_prioritized_objects;
    PollProfileSupport *poll_profile_support;
    PollProfileExt *poll_profile_ext;
	PollMdibDataReply* poll_mdib_data_reply;
	PollMdibDataReqExt* poll_mdib_data_req_ext;
	PollMdibDataReplyExt * poll_mdib_data_reply_ext;
    //Numeric Object Attributes
    Handle handle;
    TYPE *type;
    NuObsValue *nu_obs_value;
    NuObsValueCmp *nu_obs_val_cmp;
    AbsoluteTime *absolute_time;
    RelativeTime relative_time;
    TextId text_id;
    String *string;
    SimpleColour simple_colour;
	TextIdList* text_id_list;
	SaCalData16* sa_cal_data_16;

    //Wave objects
    MetricSpec *metric_spec;
    SaSpec *sa_spec;
    SaFixedValSpec16 *sa_fixed_val_spec16;
    MetricState metric_state;
    OIDType oid_type;
    MeasureMode measure_mode;
    ScaleRangeSpec16 *scale_range_spec16;
    ScaledRange16 *scaled_range_16;
    SaObsValue *sa_obs_value;
    SaObsValueCmp *sa_obs_value_cmp;
    ProtoSupport *proto_support;
    IpAddressInfo * ip_address_info;
};

class AVAType{
private:
	OIDType attribute_id;
    quint16 length;
	Object *object;
    //}attribute_val;

    //quint16 attribute_val;
public:
	AVAType()
	{
		attribute_id=-1;
		length=0;
		object=new Object();
	};
	AVAType(QDataStream &converter, int &size)
	{
		converter >> attribute_id >> length;
		object= new Object(attribute_id, length, converter);
	}
	//template <typename Type>
	AVAType(OIDType attribute_id, quint16 length, Object& object)
	{
		//void* pt=(void*)&object;
		this->attribute_id=attribute_id;
		this->length=length;
		this->object=new Object(/*attribute_id, length, */object);
		/*if(attribute_id==1)
			object->print();
		*/
	}
	~AVAType(){};
	QByteArray getAVAType()
	{
		QByteArray byteArray;
		byteArray = appendData(byteArray, attribute_id);
		byteArray = appendData(byteArray, length);
		byteArray = appendData(byteArray, object->getObject());

		return byteArray;
	}
	void print(std::string title="---------Start AVAType---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		qDebug() << "OIDType attribute_id: " << attribute_id;
		qDebug() << "quint16 length: " << length;
		object->print();

		qDebug() << "---------End AVAType---------";
	};
	int getSize()
	{
		QByteArray byteArray = getAVAType();
		return byteArray.size();

	}
	
	//void * getAttribute();
	void* getObject(){return object->getAttribute();}
	OIDType getAttributeID(){return attribute_id;};

};




class GetResult {
public:
	GetResult(ManagedObjectId& mngd_obj, AttributeList& attr_list)
	{
		this->managed_object=new ManagedObjectId(mngd_obj);
		this->attribute_list=new AttributeList (attr_list);
	};
	GetResult(QDataStream &converter, int &size)
	{
		managed_object = new ManagedObjectId(converter, size);
		attribute_list = new AttributeList(converter, size);
	};
	~GetResult()
	{
		/*
		delete managed_object;
		delete attribute_list;
		*/
	};
	QByteArray getGetResult(){
		QByteArray datagram;
		appendData(datagram, managed_object->getManagedObjectId());
		appendData(datagram, attribute_list->getAttributeList());
		return datagram;
	};
	void print(std::string title="---------Start GetResult---------")
	{
		qDebug() << QString::fromUtf8(title.c_str(), title.size());
		managed_object->print();
		attribute_list->print();
		qDebug() << "---------End GetResult---------";

	}
    ManagedObjectId *managed_object;
    AttributeList *attribute_list;
};

class AttributeModEntry{
public:
	AttributeModEntry(ModifyOperator modify_operator, AVAType& attr)
	{
		this->modify_operator=modify_operator;
		this->attribute = new AVAType(attr);
	};
	AttributeModEntry(QDataStream &converter, int &size)
	{
		converter >> modify_operator;
		attribute = new AVAType(converter, size);

	};
	AttributeModEntry()
	{
		//delete attribute;
	};
	~AttributeModEntry()
	{
		//delete attribute;
	};
	QByteArray getAttributeModEntry(){
		QByteArray datagram;
		appendData(datagram, modify_operator);
		appendData(datagram, attribute->getAVAType());
		return datagram;
	};
	int getSize()
	{
		QByteArray datagram=getAttributeModEntry();
		/*
		int size=sizeof(ModifyOperator);
		size+=attribute->getSize();
		*/
		return datagram.size();

	}
    ModifyOperator modify_operator;
    AVAType *attribute;
};

class ModificationList{
public: 
	//ModificationList();
	ModificationList(quint16 count, quint16 length, AttributeModEntry *ADEvalue);
	ModificationList(QDataStream &converter, int &size);
	~ModificationList();
	QByteArray getModificationList();

    quint16 count;
    quint16 length;
    AttributeModEntry **value;
};

//Included attribute IDs

//#endif// UDPSTRUCTURES_H


