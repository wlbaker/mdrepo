#include "protocolCommands.h"


bool findByteSequence(QDataStream & converter, unsigned char *bytes, uint size)
{
	quint8 byte;
	int i=0;
	char* read_bytes=new char[size];
	converter.readRawData(read_bytes, size);
	std::deque<unsigned char> currentBytes;
	currentBytes.assign(&read_bytes[0], &read_bytes[0]+size);
	while(!converter.atEnd())
	{
		for(i=0; i<size; i++)
		{
			if(currentBytes[i]!=bytes[i])
				break;
			else if(i==size-1)
				return 1;
		}
		converter>>byte;
		currentBytes.pop_front();
		currentBytes.push_back(byte);
		
	}
	return 0;
}

ConnectIndication::ConnectIndication(QDataStream &converter, int &size)
{
	//this->nomenclature=nomenclature;// >> s->m_obj_inst.context_id >> s->m_obj_inst.handle;
	size-=4;
	ro_apdus = new ROapdus(converter, size);
	roiv_apdu = new ROIVapdu(converter, size);
	event_report_argument = new EventReportArgument(converter, size);
	connect_ind_info = new ConnectIndInfo(converter, size);
};
QByteArray ConnectIndication::getConnectIndication()
{
	QByteArray datagram;
	//qDebug() <<"Nomenclature";
	appendData(datagram, nomenclature);
	//qDebug() << datagram.toHex();
	//qDebug() <<"ROapdus";
	appendData(datagram, this->ro_apdus->getROapdus());
	//qDebug() << datagram.toHex();
	//qDebug() <<"ROIVapdu";
	appendData(datagram, this->roiv_apdu->getROIVapdu());
	//qDebug() << datagram.toHex();
	//qDebug() <<"Event ReportArgument";
	appendData(datagram, this->event_report_argument->getEventReportArgument());
	//qDebug() << datagram.toHex();
	//qDebug() <<"Attribute list";
	appendData(datagram, this->connect_ind_info->getAttributeList());
	//qDebug() << datagram.toHex();
	
	return datagram;
};

int ConnectIndication::getIndicationPort()
{
	qDebug() <<"Indication port: ";
	int port=0;
	ProtoSupport * proto_support = (ProtoSupport *)connect_ind_info->getAttribute(Object::NOM_ATTR_PCOL_SUPPORT);
	port = proto_support->getProtoSupportEntry(AP_ID_DATA_OUT)->getPortNumber();
	qDebug() << port <<endl;
	return port;
	/*
	//for(int i=0; i<connect_ind_info->count; i++)
		//if(connect_ind_info->value[i]->getAttributeID()==NOM_ATTR_PCOL_SUPPORT)
			for(int j=0; j<connect_ind_info->value[i]->proto_support->count; j++)
				if(connect_ind_info->value[i]->proto_support->proto_support_entry[j]->appl_proto==AP_ID_DATA_OUT)
					return connect_ind_info->value[i]->proto_support->proto_support_entry[j]->port_number;
					*/
	//return -1;
};
MDSCreateInfo::MDSCreateInfo(QDataStream & converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	attribute_list = new AttributeList(converter, size);
}
ManagedObjectId MDSCreateInfo::getManagedObject()
	{
		return *managed_object;
	}

MDSCreateInfo::MDSCreateInfo()
{

};

MDSCreateInfo::~MDSCreateInfo()
{

};
void MDSCreateInfo::print(std::string title)
{
	
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	managed_object->print();
	attribute_list->print();

	qDebug() << "---------End MDSCreateInfo---------";
};

quint16 MDSCreateEventReport::getInvokeId()
{
	return ro_apdus->getRoType();
}

MDSCreateEventResult::MDSCreateEventResult()
{
	sp_pdu = new SPpdu();
	ro_apdus = new ROapdus();
	rors_apdu = new RORSapdu();
	event_report_result = new EventReportResult();
};
MDSCreateEventResult::MDSCreateEventResult(SPpdu &sp_pdu,  ROapdus &ro_apdus, RORSapdu& rors_apdu, EventReportResult& event_report_result)
{
	this->sp_pdu = new SPpdu(sp_pdu);
	this->ro_apdus = new ROapdus(ro_apdus);
	this->rors_apdu = new RORSapdu(rors_apdu);
	this->event_report_result = new EventReportResult(event_report_result);
};
MDSCreateEventResult::~MDSCreateEventResult()
{

}

QByteArray MDSCreateEventResult::getMDSCreateEventResult()
{
	QByteArray byteArray;
	appendData(byteArray, sp_pdu->getSPpdu());
	appendData(byteArray, ro_apdus->getROapdus());
	appendData(byteArray, rors_apdu->getRORSapdu());
	appendData(byteArray, event_report_result->getEventReportResult());
	return byteArray;
};
void MDSCreateEventResult::print(std::string title="---------Start MDSCreateEventResult---------")
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	sp_pdu->print();
	ro_apdus->print();
	rors_apdu->print();
	event_report_result->print();
	qDebug() <<"---------End MDSCreateEventResult---------";
};



PollMdibDataReq::PollMdibDataReq(){};
PollMdibDataReq::PollMdibDataReq(QDataStream &converter)
{
	converter >> poll_number;
	polled_obj_type= new TYPE(converter);
	//polled_obj_type->print();
	converter >>polled_attr_grp;
};
PollMdibDataReq::PollMdibDataReq(quint16 poll_number, TYPE &polled_obj_type, OIDType polled_attr_grp)
{
	this->poll_number=poll_number;
	this->polled_obj_type= new TYPE(polled_obj_type);
	this->polled_attr_grp=polled_attr_grp;
};
QByteArray PollMdibDataReq::getPollMdibDataReq()
{
	QByteArray byteArray;
	byteArray = appendData(byteArray, poll_number);
	byteArray = appendData(byteArray, polled_obj_type->getTYPE());
	byteArray = appendData(byteArray, polled_attr_grp);
	return byteArray;

};
PollMdibDataReq::~PollMdibDataReq(){};

ObservationPoll::ObservationPoll()
	{
		obj_handle=-1;
		attributes= new AttributeList();
	};
ObservationPoll::ObservationPoll(QDataStream &converter)
	{
		int size=0;
		converter >> obj_handle;
		attributes=new AttributeList(converter,size);

	};
ObservationPoll::~ObservationPoll(){};


void ObservationPoll::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	attributes->print();
	qDebug() <<"---------End ObservationPoll---------";
}

QByteArray ObservationPoll::getObservationPoll()
{
	QByteArray byteArray;
	appendData(byteArray, obj_handle);
	appendData(byteArray, attributes->getAttributeList());
	return byteArray;
}

PollMdibDataReply::PollMdibDataReply()
{
	poll_number=0;	
	rel_time_stamp=0;
	abs_time_stamp=new AbsoluteTime();
	polled_obj_type=new TYPE();
	polled_attr_grp=-1;
	poll_info_list=new PollInfoList();
};
PollMdibDataReply::PollMdibDataReply(
	quint16 poll_number, 
	RelativeTime rel_time_stamp, 
	AbsoluteTime &abs_time_stamp,
	TYPE& polled_obj_type,
	OIDType polled_attr_grp,
	PollInfoList& poll_info_list)
{
	this->poll_number=poll_number;
	this->rel_time_stamp=rel_time_stamp;
	this->abs_time_stamp=new AbsoluteTime(abs_time_stamp);
	this->polled_obj_type=new TYPE(polled_obj_type);
	this->polled_attr_grp=polled_attr_grp;
	this->poll_info_list= new PollInfoList(poll_info_list);
};
PollMdibDataReply::PollMdibDataReply(QDataStream &converter, int &size)
{
	converter >> poll_number >> rel_time_stamp;
	abs_time_stamp=new AbsoluteTime(converter,size);
	polled_obj_type=new TYPE(converter);
	converter >> polled_attr_grp;
	poll_info_list= new PollInfoList(converter);


};

PollMdibDataReply::~PollMdibDataReply(){};
void PollMdibDataReply::print()
{
	qDebug() << poll_number;
	qDebug() << rel_time_stamp;
	abs_time_stamp->print();
	polled_obj_type->print();
	qDebug() << polled_attr_grp;
	qDebug() << poll_info_list;

};

PollMdibDataReplyExt::PollMdibDataReplyExt(){};

QByteArray PollMdibDataReplyExt::getPollMdibDataReplyExt()
{
	QByteArray byteArray;
	appendData(byteArray, poll_number);
	appendData(byteArray, sequence_no);
	appendData(byteArray, rel_time_stamp);
	appendData(byteArray, abs_time_stamp->getAbsoluteTime());
	appendData(byteArray, polled_obj_type->getTYPE());
	appendData(byteArray, polled_attr_grp);
	appendData(byteArray, poll_info_list->getPollInfoList());
	return byteArray;

}

PollMdibDataReplyExt::PollMdibDataReplyExt(
	quint16 poll_number,
	quint16 sequence_no,
	RelativeTime rel_time_stamp,
	AbsoluteTime& abs_time_stamp,
	TYPE& polled_obj_type,
	OIDType polled_attr_grp,
	PollInfoList& poll_info_list
	)
{
	this->poll_number=poll_number;
	this->sequence_no=sequence_no;
	this->rel_time_stamp=rel_time_stamp;
	this->abs_time_stamp=new AbsoluteTime(abs_time_stamp);
	this->polled_obj_type= new TYPE(polled_obj_type);
	this->polled_attr_grp= polled_attr_grp;
	this->poll_info_list= new PollInfoList(poll_info_list);
};
PollMdibDataReplyExt::PollMdibDataReplyExt(QDataStream & converter, int &size)
{	converter >> poll_number >> sequence_no >> rel_time_stamp;
	this->abs_time_stamp=new AbsoluteTime(converter, size);
	this->polled_obj_type= new TYPE(converter);
	converter >> polled_attr_grp;
	this->poll_info_list= new PollInfoList(converter);


};
void PollMdibDataReplyExt::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() <<  "quint16 poll_number :" << poll_number;
	qDebug() <<  "quint16 sequence_no :" << sequence_no;
	qDebug() <<  "RelativeTime rel_time_stamp :" << rel_time_stamp;
	abs_time_stamp->print();
	polled_obj_type->print();
	qDebug() <<  "OIDType polled_attr_grp :" << polled_attr_grp;
	poll_info_list->print();
	qDebug() <<"---------End PollMdibDataReplyExt---------";
}

PollInfoList::PollInfoList()
{
	count=0;
	length=0;
	value=NULL;
};
PollInfoList::PollInfoList(QDataStream &converter)
{
	converter>> count >>length;
	value=new SingleContextPoll*[count];
	for(int i=0; i< count; i++)
		value[i]=new SingleContextPoll(converter);
};
QByteArray PollInfoList::getPollInfoList()
{
	QByteArray byteArray;
	appendData(byteArray, count);
	appendData(byteArray, length);
	for(int i=0; i< count; i++)
		appendData(byteArray, value[i]->getSingleContextPoll());

	return byteArray;

}
void PollInfoList::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() <<  "quint16 count :" << count;
	qDebug() <<  "quint16 length :" << length;
	for(int i=0; i< count; i++)
	{
		qDebug() <<  "SingleContextPoll** value: " << i;
		value[i]->print();
	}
	qDebug() <<"---------End PollInfoList---------";
}
PollInfoList::~PollInfoList(){};


SingleContextPoll::SingleContextPoll()
{
	context_id=0;
	poll_info.count=0;
	poll_info.length=0;
};
SingleContextPoll::SingleContextPoll(QDataStream & converter)
{
	converter >> 
		context_id >> 
		poll_info.count >> 
		poll_info.length;
	poll_info.value=new ObservationPoll*[poll_info.count];
	for(int i=0; i<poll_info.count; i++)
		poll_info.value[i] = new ObservationPoll(converter);
};
void SingleContextPoll::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() <<  "MdsContext context_id:" << context_id;
	qDebug() <<  "quint16 poll_info.count:" << poll_info.count;
	qDebug() <<  "quint16 poll_info.length:" << poll_info.length;
	for(int i=0; i< poll_info.count; i++)
	{
		qDebug() <<  "ObservationPoll **poll_info.value: " << i;
		poll_info.value[i]->print();
	}
	qDebug() <<"---------End SingleContextPoll---------";
}
QByteArray SingleContextPoll::getSingleContextPoll()
{
	QByteArray byteArray;
	appendData(byteArray, context_id);
	appendData(byteArray, poll_info.count);
	appendData(byteArray, poll_info.length);
	for(int i=0;i<poll_info.count;i++)
		appendData(byteArray, poll_info.value[i]->getObservationPoll());
	return byteArray;
}

SingleContextPoll::~SingleContextPoll(){};


MDSEUserInfoStd::MDSEUserInfoStd(ProtocolVersion protocol_version, 
	NomenclatureVersion nomenclature_version,
	FunctionalUnits functional_units,
	SystemType system_type,
	StartupMode startup_mode,
	AttributeList &ol,
	AttributeList &sa)
{
	this->protocol_version=protocol_version;
	this->nomenclature_version=nomenclature_version;
	this->functional_units=functional_units;
	this->system_type=system_type;
	this->startup_mode=startup_mode;
	this->option_list=new AttributeList(ol);
	this->supported_aprofiles=new AttributeList(sa);
};
	MDSEUserInfoStd::MDSEUserInfoStd(QDataStream & converter, int size)
{
	converter >> protocol_version;
	converter >> nomenclature_version;
	converter >> functional_units;
	converter >> system_type;
	converter >> startup_mode;
	this->option_list=new AttributeList(converter, size);
	this->supported_aprofiles=new AttributeList(converter, size);
};
MDSEUserInfoStd::~MDSEUserInfoStd()
{
	delete option_list;
	delete supported_aprofiles;
}

QByteArray MDSEUserInfoStd::getMDSEUserInfoStd()
{
	QByteArray datagram;
	datagram.resize(0);
	appendData(datagram, protocol_version);
	appendData(datagram, nomenclature_version);
	appendData(datagram, functional_units);
	appendData(datagram, system_type);
	appendData(datagram, startup_mode);
	appendData(datagram, option_list->getAttributeList());
	appendData(datagram, supported_aprofiles->getAttributeList());
	//qDebug() << datagram.toHex();
	return datagram;
}
void MDSEUserInfoStd::print()
{
	std::cout << "protocol_version: " << protocol_version << std::endl;
	std::cout << "nomenclature_version: " << nomenclature_version << std::endl;
	std::cout << "functional_units: " << functional_units << std::endl;
	std::cout << "system_type: " << system_type << std::endl;
	std::cout << "startup_mode: " << startup_mode << std::endl;
	std::cout << "option_list: " << std::endl;
		option_list->print();
	std::cout << "supported_aprofiles: " << std::endl;
		supported_aprofiles->print();

}


PollMdibDataReqExt::PollMdibDataReqExt(){};
PollMdibDataReqExt::PollMdibDataReqExt(quint16 poll_number, TYPE & polled_obj_type, OIDType polled_attr_grp, AttributeList& poll_ext_attr)
{
	this->poll_number = poll_number;
	this->polled_obj_type = new TYPE(polled_obj_type);
	this->polled_attr_grp = polled_attr_grp;
	this->poll_ext_attr = new AttributeList(poll_ext_attr);
	
};
PollMdibDataReqExt::~PollMdibDataReqExt(){};
QByteArray PollMdibDataReqExt::getPollMdibDataReqExt()
{
	QByteArray byteArray;
	byteArray=appendData(byteArray, poll_number);
	byteArray=appendData(byteArray, polled_obj_type->getTYPE());
	byteArray=appendData(byteArray, polled_attr_grp);
	byteArray=appendData(byteArray, poll_ext_attr->getAttributeList());
	return byteArray;
}

void PollMdibDataReqExt::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() << "quint16 poll_number" << poll_number;
	polled_obj_type->print();
	qDebug() << "OIDType polled_attr_grp" << polled_attr_grp;
	poll_ext_attr->print();

	qDebug() <<  "---------End PollMdibDataReqExt---------";
}

MDSGetPriorityList::MDSGetPriorityList()
{
};

MDSGetPriorityList::MDSGetPriorityList(
	SPpdu& sp_pdu,
	ROapdus& ro_apdus,
	ROIVapdu& roiv_apdu, 
	GetArgument& get_argument)
{
	this->sp_pdu=new SPpdu(sp_pdu);
	this->ro_apdus=new ROapdus(ro_apdus);
	this->roiv_apdu=new ROIVapdu(roiv_apdu);
	this->get_argument=new GetArgument(get_argument);
}
QByteArray MDSGetPriorityList::getMDSGetPriorityList()
{
	QByteArray byteArray;
	appendData(byteArray,this->sp_pdu->getSPpdu());
	appendData(byteArray, this->ro_apdus->getROapdus());
	appendData(byteArray, this->roiv_apdu->getROIVapdu());
	appendData(byteArray, this->get_argument->getGetArgument());
	return byteArray;
}
MDSGetPriorityList::~MDSGetPriorityList()
{
};

MDSSetPriorityList::MDSSetPriorityList(){};
MDSSetPriorityList::MDSSetPriorityList(
	SPpdu& sp_pdu,
	ROapdus& ro_apdus,
	ROIVapdu& roiv_apdu,
	SetArgument& set_argument)
{
	this->sp_pdu=new SPpdu(sp_pdu);
	this->ro_apdus=new ROapdus(ro_apdus);
	this->roiv_apdu=new ROIVapdu(roiv_apdu);
	this->set_argument=new SetArgument(set_argument);
}
QByteArray MDSSetPriorityList::getMDSSetPriorityList()
{
	QByteArray byteArray;
	appendData(byteArray, sp_pdu->getSPpdu());
	appendData(byteArray, ro_apdus->getROapdus());
	appendData(byteArray, roiv_apdu->getROIVapdu());
	appendData(byteArray, set_argument->getSetArgument());
	return byteArray;
}

MDSSetPriorityList::~MDSSetPriorityList(){};

AssociationResponse::AssociationResponse(QDataStream &converter, int size)
{

	
	unsigned char searchSequence[]=
    {
        0xBE, 0x80, 0x28, 0x80
	};

	unsigned char searchSequence1[]=
    {
        0x81
	};

	unsigned char searchSequence2[]=
    {
        0x02, 0x01, 0x02, 0x81
	};
	
	uint length=4;
	uint length1=1;
	uint length2=4;
	quint8 byte;
	bool found = 0;
	while(!found && !converter.atEnd())
	{
		found = findByteSequence(converter, searchSequence, length);
		converter>>byte;
		if(byte==searchSequence1[0])
			break;//search successfull
		else if(byte==searchSequence2[0])
		{
			int i=1;
			for(i;i<4;i++)
			{
				converter>>byte;
				if(byte!=searchSequence2[i])
					break;//continue search
			}
			if((i==4) && (byte==searchSequence2[3]))
			{
				found=1;//search successfull
				break;
			}
		}
		found=0;
	}
	std::cout << "sequence finder: " << found << std::endl;
	assoc_resp_user_data=new AssocRespUserData(converter, size);
	

}

AssocRespUserData::AssocRespUserData(QDataStream &converter, int size)
{
	quint8 testLength;
	int numberOfAppendedBytes;
	converter >>testLength;
	asn_length=0;
	if(testLength<127)
	{
		asn_length=testLength;
	}
 	else
	{
		numberOfAppendedBytes=testLength-128;
		quint8 *bytes=new quint8[numberOfAppendedBytes];

		for(int i=0; i<numberOfAppendedBytes;i++)
			converter >>  bytes[i];
		
		for(int i=numberOfAppendedBytes-1;i>=0;i--)
			asn_length=(asn_length << 8) +bytes[i];
	}

	
	mdse_user_info_std=new MDSEUserInfoStd(converter, size);


}