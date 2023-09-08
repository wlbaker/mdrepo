#pragma once

#include "UDPStructures.h"





quint8 bcdToDec(quint8 val)
{
  return ( (val/16*10) + (val%16) );
}

quint8 decToBcd(quint8 val)
{
  return ( (val/10*16) + (val%10) );
}

float FLOATTypeToFloat(FLOATType val)
{
	qint8 exponent = (val >> 24) & 0xff;
	/*
	qint8 mantissaBytes[3] ={
		(val >> (8*2)) & 0xff, 
		(val >> (8*1)) & 0xff,
		(val >> (8*0)) & 0xff};

	int mantissa = ((int)mantissaBytes[0]) << 16;
	mantissa |= ((int)mantissaBytes[1]) << 8;
	mantissa |= mantissaBytes[2];
	*/
	int mantissa=((val >> 16) & 0xff) << 16;
	mantissa |= ((val >> 8) & 0xff) << 8;
	mantissa |= val & 0xff;
	
	if(mantissa==0x7fffff)
		qDebug() << "Error in FLOAT conversion: NaN";
	else if(mantissa==0x800000)
		qDebug() << "Error in FLOAT conversion: NRes";
	else if(mantissa==0x7ffffe || mantissa==0x800002)
		qDebug() << "Error in FLOAT conversion: Inf";

	float result=(float)mantissa*pow(10.0,exponent);
	//qDebug() << "FLOATType: " << result;
	return result;
}

QByteArray appendData(QByteArray & datagram, quint32 data)
{
	QByteArray qba;
	QDataStream converter(&qba, QIODevice::ReadWrite);
	converter << data;
	datagram.append(qba);
	return datagram;
};
QByteArray appendData(QByteArray & datagram, quint16 data)
{
	QByteArray qba;
	QDataStream converter(&qba, QIODevice::ReadWrite);
	converter << data;
	datagram.append(qba);
	return datagram;
};
QByteArray appendData(QByteArray & datagram, quint8 data)
{
	QByteArray qba;
	QDataStream converter(&qba, QIODevice::ReadWrite);
	converter << data;
	datagram.append(qba);
	return datagram;
};

QByteArray appendData(QByteArray & datagram, QByteArray data)
{
	datagram.append(data);
	return datagram;
};

ManagedObjectId::ManagedObjectId(OIDType m_obj_class, GlbHandle& m_obj_inst)
{
	this->m_obj_class = m_obj_class;
	this->m_obj_inst = new GlbHandle(m_obj_inst);
};
ManagedObjectId::ManagedObjectId(QDataStream &converter, int &size)
{
	size-=2;
	converter >> m_obj_class;// >> s->m_obj_inst.context_id >> s->m_obj_inst.handle;
	m_obj_inst = new GlbHandle(converter, size);
};
QByteArray ManagedObjectId::getManagedObjectId()
{
	QByteArray datagram;
	appendData(datagram, m_obj_class);
	appendData(datagram, m_obj_inst->getGlbHandle());
	return datagram;
};

ManagedObjectId::~ManagedObjectId()
{
	//delete m_obj_inst;
};

ROLRSapdu::ROLRSapdu(RorlsId& Rorls_Id, quint16 invoke_id, CMDType command_type, quint16 length)
{
	this->linked_id=new RorlsId(Rorls_Id);
	this->invoke_id=invoke_id;
	this->command_type=command_type;
	this->length=length;
}

ROLRSapdu::ROLRSapdu(QDataStream &converter, int &size)
{
	linked_id=new RorlsId(converter, size);
	converter >> invoke_id >> command_type >> length;
}

getInfoList::getInfoList(quint16 count, quint16 length, GetError* error_value)
{
	this->count=count;
	this->length=length;
	value=new GetError*[count];
	for(int i=0;i<count;i++)
		value[i]=new GetError(error_value[i]);
}
getInfoList::getInfoList(QDataStream &converter, int &size)
{
	
	converter >> count >> length;
	value = new GetError*[count];
	for(int i=0; i<count;i++)
		value[i]=new GetError(converter, size);

}

GetListError::GetListError(ManagedObjectId& mngd_obj_id, getInfoList &info_list)
{
	this->managed_object=new ManagedObjectId(mngd_obj_id);
	this->get_info_list= new getInfoList(info_list);
}
GetListError::GetListError(QDataStream &converter, int &size)
{
	get_info_list = new getInfoList(converter, size);
	managed_object=new ManagedObjectId(converter, size);
}

setInfoList::setInfoList(quint16 count, quint16 length, SetError *error_values)
{
	this->count=count;
	this->length=length;
	value= new SetError*[count];
	for(int i=0; i<count; i++)
		value[i]=new SetError(error_values[i]);
}
setInfoList::setInfoList(QDataStream &converter, int &size)
{
	converter >> count >> length;
	value= new SetError*[count];
	for(int i=0; i<count; i++)
		value[i]=new SetError(converter, size);
}

SetListError::SetListError(ManagedObjectId &mngd_obj, setInfoList &info_list)
{
	this->managed_object = new ManagedObjectId(mngd_obj);
	this->set_info_list = new setInfoList(info_list);
}
SetListError::SetListError(QDataStream &converter, int &size)
{
	this->managed_object = new ManagedObjectId(converter, size);
	this->set_info_list = new setInfoList(converter, size);
}

EventReportArgument::EventReportArgument()
{
	this->managed_object = new ManagedObjectId();
	this->event_time=0;
	this->event_type=0;
	this->length=0;
}

EventReportArgument::EventReportArgument(ManagedObjectId& mngd_obj, RelativeTime event_time, OIDType event_type, quint16 length)
{
	this->managed_object = new ManagedObjectId(mngd_obj);
	this->event_time=event_time;
	this->event_type=event_type;
	this->length=length;
}
EventReportArgument::EventReportArgument(QDataStream &converter, int &size)
{
	
	managed_object = new ManagedObjectId(converter, size);
	converter >> event_time >> event_type >> length;
	size-=8;
	//qDebug() << "size: " << size;
	//qDebug() << "length: " << length;
}

EventReportResult::EventReportResult(ManagedObjectId& mngd_obj, RelativeTime current_time, OIDType event_type, quint16 length)
{
	this->managed_object = new ManagedObjectId(mngd_obj);
	this->current_time=current_time;
	this->event_type=event_type;
	this->length=length;
}
EventReportResult::EventReportResult(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	converter >> current_time >> event_type >> length;
}

ActionArgument::ActionArgument(ManagedObjectId &mngd_obj, quint32 scope, OIDType action_type, quint16 length)
{
	this->managed_object= new ManagedObjectId(mngd_obj);
	this->scope=scope;
	this->action_type=action_type;
	this->length=length;
}
ActionArgument::ActionArgument(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	converter >> scope >> action_type >> length;
}

ActionResult::ActionResult(ManagedObjectId& mngd_obj, OIDType action_type, quint16 length)
{
	this->managed_object=new ManagedObjectId(mngd_obj);
	this->action_type=action_type;
	this->length=length;
}
ActionResult::ActionResult(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	converter >> action_type >> length;
	
	//processOIDType(action_type, converter);
}

void ActionResult::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	managed_object->print();
	qDebug() << "OIDType action_type: " << action_type;
	qDebug() << "quint16 length: " << length;
	qDebug() << "---------End ActionResult---------";
}

AttributeIdList::AttributeIdList(quint16 count, quint16 length, OIDType *oidt_value)
{
	this->count=count;
	this->length=length;
	this->value = new OIDType[count];
	for(int i=0; i<count; i++)
		value[i]=oidt_value[i];
}
AttributeIdList::AttributeIdList(QDataStream &converter, int &size)
{
	converter >> count >> length;
	value= new OIDType[count];

	for(int i=0; i<count; i++)
		converter >> value[i];
}

GetArgument::GetArgument(ManagedObjectId &mngd_obj, quint32 scope, AttributeIdList &attr_id_list)
{
	managed_object=new ManagedObjectId(mngd_obj);
	this->scope=scope;
	attribute_id_list=new AttributeIdList(attr_id_list);
}
GetArgument::GetArgument(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	converter >> scope;
	attribute_id_list = new AttributeIdList(converter, size);
}

SetResult::SetResult(ManagedObjectId &mngd_obj, AttributeList& attr_list)
{
	this->managed_object= new ManagedObjectId(mngd_obj);
	this->attribute_list = new AttributeList(attr_list);
}
SetResult::SetResult(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	attribute_list = new AttributeList(converter, size);
}
SetResult::~SetResult()
{
	delete managed_object;
	delete attribute_list;
}
QByteArray SetResult::getSetResult()
{
	QByteArray datagram;
	appendData(datagram, managed_object->getManagedObjectId());
	appendData(datagram, attribute_list->getAttributeList());
	return datagram;
}
PollProfileSupport::PollProfileSupport()
{
	poll_profile_revision=0;
	min_poll_period=0;
	max_mtu_rx=0;
	max_mtu_tx=0;
	max_bw_tx=0;
	options=0;
	optional_packages=new AttributeList();
};
PollProfileSupport::PollProfileSupport(
	PollProfileRevision poll_profile_revision, 
	RelativeTime min_poll_period, 
	quint32 max_mtu_rx,
	quint32 max_mtu_tx,
	quint32 max_bw_tx,
	PollProfileOptions options,
	AttributeList &opt_packages)
{
	this->poll_profile_revision=poll_profile_revision;
	this->min_poll_period=min_poll_period;
	this->max_mtu_rx=max_mtu_rx;
	this->max_mtu_tx=max_mtu_tx;
	this->max_bw_tx=max_bw_tx;
	this->options=options;
	optional_packages=new AttributeList(opt_packages);
}
PollProfileSupport::PollProfileSupport (QDataStream &converter, int &size)
{
	
	converter >> poll_profile_revision
		>> min_poll_period
		>> max_mtu_rx
		>> max_mtu_tx
		>> max_bw_tx
		>> options;
	size-=(sizeof(poll_profile_revision)+sizeof(min_poll_period)+sizeof(max_mtu_rx)+sizeof(max_mtu_tx)+sizeof(max_bw_tx)+sizeof(options));

	optional_packages = new AttributeList(converter, size);
}
PollProfileSupport::~PollProfileSupport()
{
	delete optional_packages;
}
QByteArray PollProfileSupport::getPollProfileSupport(){
	QByteArray datagram;
	appendData(datagram, poll_profile_revision);
	appendData(datagram, min_poll_period);
	appendData(datagram, max_mtu_rx);
	appendData(datagram, max_mtu_tx);
	appendData(datagram, max_bw_tx);
	appendData(datagram, options);
	appendData(datagram, optional_packages->getAttributeList());
	return datagram;
}
NuObsValueCmp::NuObsValueCmp(quint16 count, quint16 length, NuObsValue *nu_obs_value)
{
	this->count=count;
	this->length=length;
	this->value=new NuObsValue*[count];
	for(int i=0;i<count; i++)
		this->value[i]= new NuObsValue(nu_obs_value[i]);
}
NuObsValueCmp::NuObsValueCmp(QDataStream &converter, int &size)
{
	converter >> count >> length;
	value= new NuObsValue*[count];

	for(int i =0; i < count; i++)
		value[i]=new NuObsValue(converter, size);
}

PollProfileExt::PollProfileExt(PollProfileExtOptions options, AttributeList& ext_attr)
{
	this->options=options;
	this->ext_attribute= new AttributeList(ext_attr);
}
PollProfileExt::PollProfileExt(QDataStream &converter, int &size)
{
	converter >> options;
	ext_attribute = new AttributeList(converter, size);
}
PollProfileExt::~PollProfileExt()
{
	delete ext_attribute;
}
QByteArray PollProfileExt::getPollProfileExt(){
	QByteArray datagram;
	appendData(datagram, options);
	appendData(datagram, ext_attribute->getAttributeList());
	return datagram;
};

ModificationList::ModificationList(quint16 count, quint16 length, AttributeModEntry *ADEvalue)
{
	this->count=count;
	this->length=length;
	this->value= new AttributeModEntry*[count];
	for(int i=0;i<count; i++)
	{
		this->value[i]=new AttributeModEntry(ADEvalue[i]);
	}
};
	
ModificationList::ModificationList(QDataStream &converter, int &size)
{
	converter >> count >> length;
	value= new AttributeModEntry*[count];

	for(int i =0;i<count; i++)
		value[i]=new AttributeModEntry(converter, size);
		
};

ModificationList::~ModificationList()
{
	/*
	for(int i=0;i<count; i++)
		delete value[i];

	delete[] value;
	*/
};

QByteArray ModificationList::getModificationList(){
	QByteArray datagram;
	appendData(datagram, count);
	appendData(datagram, length);

	for(int i =0;i<count; i++)
		appendData(datagram, value[i]->getAttributeModEntry());
    
	return datagram;
};

SetArgument::SetArgument(ManagedObjectId& mngd_obj, quint32 scope, ModificationList& mod_list)
{
	this->managed_object=new ManagedObjectId (mngd_obj);
	this->scope=scope;
	this->modification_list = new ModificationList (mod_list);
};

SetArgument::SetArgument(QDataStream &converter, int &size)
{
	managed_object = new ManagedObjectId(converter, size);
	converter >> scope;
	modification_list = new ModificationList(converter, size);
};

SetArgument::~SetArgument()
{
	delete managed_object;
	delete modification_list;
};

QByteArray SetArgument::getSetArgument(){
	QByteArray datagram;
	appendData(datagram, managed_object->getManagedObjectId());
	appendData(datagram, scope);
	appendData(datagram, modification_list->getModificationList());
	return datagram;
};
int SetArgument::getSize()
{
	QByteArray byteArray = getSetArgument();
	return byteArray.size();

}
AttributeList::AttributeList(std::string name)
{
	this->name=name;
	this->count=0;
	this->length=0;
	this->value= new AVAType*[this->count];
};

AttributeList::AttributeList(quint16 c, quint16 l, AVAType *avat_value, std::string name)
{
	this->name=name;
	this->count=c;
	this->length=l;

	this->value=new AVAType*[count];

	for(int i=0;i<count; i++)
	{
		this->value[i]=new AVAType(avat_value[i]);
	}

};



AttributeList::AttributeList(QDataStream &converter, int & size)
{
	this->name="deafult-converter";
	size-=4;
	//qDebug() << "size: " << size;
	converter >> count >> length;
	//qDebug() << "length: " << length;

	value = new AVAType*[count];
	for(int i =0;i<count; i++)
		value[i]= new AVAType(converter, size);
};
AttributeList::~AttributeList()
{
	/*
	qDebug() << "deleting: " <<QString::fromStdString(name);
	
	for(int i=0;i<count; i++)
		delete value[i];

	delete[] value;
	*/
};
QByteArray AttributeList::getAttributeList()
{
	QByteArray datagram;
	appendData(datagram, this->count);
	appendData(datagram, length);
	int size1= datagram.size();
	
	for(int i =0;i<count; i++)
	{
		appendData(datagram, value[i]->getAVAType());
		//qDebug() << datagram.toHex();
	}
    
	int size2= datagram.size();

	return datagram;
};

void* AttributeList::getAttribute(OIDType id)
{
	for(int i=0; i<count; i++)
		if(value[i]->getAttributeID()==id)
		{
			return value[i]->getObject();
		}

	return NULL;
};


void AttributeList::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() << "quint16 count: " << count;
	qDebug() << "quint16 length: " << length;


	for(int i=0; i< count; i++)
	{
		qDebug() << "AVAType **value: " << i << ": ";
		value[i]->print();
	}
    
   //AVAType **value;
	qDebug() << "---------End AttributeList---------";
}

std::vector<OIDType> AttributeList::getOIDTypeList()
{
	std::vector<OIDType> OIDTypes;
	for(int i=0; i<count;i++)
		OIDTypes.push_back(value[i]->getAttributeID());
	
	return OIDTypes;
}


Object::Object(OIDType attribute_id, quint16 length, void* attribute)
{
	this->length=length;
	PollDataReqPeriod*  pdrp;
	PollProfileSupport* pps;
	PollProfileExt* ppe;
	NuObsValue* nov;
	NuObsValueCmp* novc;
	TYPE* t;
	AbsoluteTime* at;
	String* s1;
	MetricSpec* ms;
	SaSpec* ss;
	ScaledRange16* sr16;
	ScaleRangeSpec16* srs16;
	SaFixedValSpec16* sfvs16;
	SaObsValue* sov;
	SaObsValueCmp* sovc;
	ProtoSupport* ps;
	IpAddressInfo* ipai;
	PollMdibDataReply* pmdr;
	PollMdibDataReplyExt* pmdre;
	TextIdList* til;
	SaCalData16* scd16;

	poll_data_req_period = new PollDataReqPeriod();
	poll_profile_support = new PollProfileSupport();
	poll_profile_ext = new PollProfileExt();
	nu_obs_value = new NuObsValue();
	nu_obs_val_cmp = new NuObsValueCmp();
	absolute_time = new AbsoluteTime();
	string = new String();
	metric_spec = new MetricSpec();
	sa_spec = new SaSpec();
	sa_fixed_val_spec16 = new SaFixedValSpec16();
	scale_range_spec16 = new ScaleRangeSpec16();
	scaled_range_16 = new ScaledRange16();
	sa_obs_value = new SaObsValue();
	ip_address_info = new IpAddressInfo();
	proto_support = new ProtoSupport();
	sa_obs_value_cmp = new SaObsValueCmp();
	poll_mdib_data_reply=new PollMdibDataReply();
	poll_mdib_data_reply_ext = new PollMdibDataReplyExt();
	text_id_list= new TextIdList();
	sa_cal_data_16 = new SaCalData16();
	

	this->ID=attribute_id;
	//qDebug() << typeid(attribute).name();
	switch(attribute_id){
	case (NOM_ATTR_TIME_PD_POLL):
		//qDebug() << "NOM_ATTR_TIME_PD_POLL";
		pdrp=static_cast<PollDataReqPeriod*> (attribute);
		poll_data_req_period = new PollDataReqPeriod(*pdrp);
		break;
	case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
		//qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
		//quint16* s=static_cast<quint16*> (attribute);
		number_of_prioritized_objects = (uintptr_t) attribute;
		//init u16
		break;
	case(NOM_POLL_PROFILE_SUPPORT):
		//qDebug() << "NOM_POLL_PROFILE_SUPPORT";
		
		pps=static_cast<PollProfileSupport*> (attribute);
		poll_profile_support = new PollProfileSupport(*pps);
		break;
	case(NOM_ATTR_POLL_PROFILE_EXT):
		//qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
		ppe=static_cast<PollProfileExt*> (attribute);
		poll_profile_ext = new PollProfileExt(*ppe);
		break;
	case(NOM_ATTR_ID_HANDLE):
		//qDebug() << "NOM_ATTR_ID_HANDLE";
		handle = (Handle)(uintptr_t)attribute;// = initHandle(datagram);
		break;
	case(NOM_ATTR_ID_TYPE):
		//qDebug() << "NOM_ATTR_ID_TYPE";
		t=static_cast<TYPE*> (attribute);
		type = new TYPE(*t);
		break;
	case(NOM_ATTR_NU_VAL_OBS):
		//qDebug() << "NOM_ATTR_NU_VAL_OBS";
		nov=static_cast<NuObsValue*> (attribute);
		nu_obs_value = new NuObsValue(*nov);
		break;
	case(NOM_ATTR_NU_CMPD_VAL_OBS):
		//qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
		novc=static_cast<NuObsValueCmp*> (attribute);
		nu_obs_val_cmp = new NuObsValueCmp(*novc);
		break;
	case(NOM_ATTR_TIME_STAMP_ABS):
		//qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
		at=static_cast<AbsoluteTime*> (attribute);
		absolute_time = new AbsoluteTime(*at);
		break;
	case(NOM_ATTR_TIME_STAMP_REL):
		//qDebug() << "NOM_ATTR_TIME_STAMP_REL";
		relative_time=(RelativeTime)(uintptr_t)attribute;// = initRelativeTime(datagram);
		break;
	case(NOM_ATTR_ID_LABEL):
		//qDebug() << "NOM_ATTR_ID_LABEL";
		text_id=(TextId)(uintptr_t)attribute;// = initTextId(datagram);
		break;
	case(NOM_ATTR_ID_LABEL_STRING):
		//qDebug() << "NOM_ATTR_ID_LABEL_STRING";
		s1=static_cast<String*> (attribute);
		string = new String(*s1);
		break;
	case(NOM_ATTR_COLOR):
		//qDebug() << "NOM_ATTR_COLOR";
		simple_colour=(SimpleColour)(uintptr_t)attribute;// = initSimpleColour(datagram);
		break;
	case(NOM_ATTR_METRIC_SPECN):
		//qDebug() << "NOM_ATTR_METRIC_SPECN";
		ms=static_cast<MetricSpec*> (attribute);
		metric_spec = new MetricSpec(*ms);
		break;
	case(NOM_ATTR_SA_SPECN):
		//qDebug() << "NOM_ATTR_SA_SPECN";
		ss=static_cast<SaSpec*> (attribute);
		sa_spec = new SaSpec(*ss);
		break;
	case(NOM_ATTR_SA_FIXED_VAL_SPECN):
		//qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
		sfvs16=static_cast<SaFixedValSpec16*> (attribute);
		sa_fixed_val_spec16 = new SaFixedValSpec16(*sfvs16);
		break;
	case(NOM_ATTR_TIME_PD_SAMP):
		//qDebug() << "NOM_ATTR_TIME_PD_SAMP";
		relative_time=(RelativeTime)(uintptr_t)attribute;// = initRelativeTime(datagram);
		break;
	case(NOM_ATTR_METRIC_STAT):
		//qDebug() << "NOM_ATTR_METRIC_STAT";
		metric_state=(MetricState)(uintptr_t)attribute;// = initMetricState(datagram);
		break;
	case(NOM_ATTR_UNIT_CODE):
		//qDebug() << "NOM_ATTR_UNIT_CODE";
		oid_type=(OIDType)(uintptr_t)attribute;// = initOIDType(datagram);
		break;
	case(NOM_ATTR_MODE_MSMT):
		//qDebug() << "NOM_ATTR_MODE_MSMT";
		measure_mode=(MeasureMode)(uintptr_t)attribute;// = initMeasureMode(datagram);
		break;
	case(NOM_ATTR_METRIC_INFO_LABEL):
		//qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
		text_id=(TextId)(uintptr_t)attribute;// = initTextId(datagram);
		break;
	case(NOM_ATTR_METRIC_INFO_LABEL_STR):
		//qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
		s1=static_cast<String*> (attribute);
		string = new String(*s1);
		break;
	case(NOM_ATTR_SCALE_SPECN_I16):
		//qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
		srs16=static_cast<ScaleRangeSpec16*> (attribute);
		scale_range_spec16 = new ScaleRangeSpec16(*srs16);
		break;
	case(NOM_ATTR_SA_RANGE_PHYS_I16):
		//qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
		sr16=static_cast<ScaledRange16*> (attribute);
		scaled_range_16 = new ScaledRange16(*sr16);
		break;
	case(NOM_ATTR_SA_VAL_OBS):
		//qDebug() << "NOM_ATTR_SA_VAL_OBS";
		sov=static_cast<SaObsValue*> (attribute);
		sa_obs_value = new SaObsValue(*sov);
		break;
	case(NOM_ATTR_SA_CMPD_VAL_OBS):
		//qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
		sovc=static_cast<SaObsValueCmp*> (attribute);
		sa_obs_value_cmp = new SaObsValueCmp(*sovc);
		break;
	case(NOM_ATTR_PCOL_SUPPORT):
		//qDebug() << "NOM_ATTR_PCOL_SUPPORT";
		ps=static_cast<ProtoSupport*> (attribute);
		proto_support = new ProtoSupport(*ps);
		break;
	case(NOM_ATTR_NET_ADDR_INFO):
		//qDebug() << "NOM_ATTR_NET_ADDR_INFO";
		ipai=static_cast<IpAddressInfo*> (attribute);
		ip_address_info = new IpAddressInfo(*ipai);
		break;
	case(NOM_ATTR_TIME_ABS):
		//qDebug() << "NOM_ATTR_TIME_ABS";
		at=static_cast<AbsoluteTime*> (attribute);
		absolute_time = new AbsoluteTime(*at);
		break;
	case(NOM_ACT_POLL_MDIB_DATA):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA";
		pmdr=static_cast<PollMdibDataReply*> (attribute);
		poll_mdib_data_reply = new PollMdibDataReply(*pmdr);
		break;
	case(NOM_ACT_POLL_MDIB_DATA_EXT):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA_EXT";
		pmdre=static_cast<PollMdibDataReplyExt*> (attribute);
		poll_mdib_data_reply_ext = new PollMdibDataReplyExt(*pmdre);
		break;
	case(NOM_ATTR_POLL_NU_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_NU_PRIO_LIST";
	case(NOM_ATTR_POLL_RTSA_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_RTSA_PRIO_LIST";
		til=static_cast<TextIdList*> (attribute);
		text_id_list = new TextIdList(*til);
		break;
	case(NOM_ATTR_SA_CALIB_I16):
		//qDebug() << "NOM_ATTR_SA_CALIB_I16";
		scd16=static_cast<SaCalData16*> (attribute);
		sa_cal_data_16 = new SaCalData16(*scd16);
		break;
	default:
		break;
		//qDebug() << "NO MATCHING ID: " << ID;
	}
};
/*
Object::~Object()
{
	//qDebug() << "Deleting: ";
	
	delete poll_data_req_period;
	delete poll_profile_support;
	delete poll_profile_ext;
	delete nu_obs_value;
	delete type;
	delete nu_obs_val_cmp;
	delete absolute_time;
	delete string;
	delete metric_spec;
	delete sa_spec;
	delete sa_fixed_val_spec16;
	delete scale_range_spec16;
	delete scaled_range_16;
	delete sa_obs_value;
	delete sa_obs_value_cmp;
	delete proto_support;
	delete ip_address_info;
	
	
	switch(attribute_id){
	case (NOM_ATTR_TIME_PD_POLL):
		qDebug() << "NOM_ATTR_TIME_PD_POLL";
		delete poll_data_req_period;
		break;
	case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
		//init u16
		break;
	case(NOM_POLL_PROFILE_SUPPORT):
		qDebug() << "NOM_POLL_PROFILE_SUPPORT";
		delete poll_profile_support;
		break;
	case(NOM_ATTR_POLL_PROFILE_EXT):
		qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
		delete poll_profile_ext;
		break;
	case(NOM_ATTR_ID_HANDLE):
		break;
	case(NOM_ATTR_ID_TYPE):
		qDebug() << "NOM_ATTR_ID_TYPE";
		delete type;
		break;
	case(NOM_ATTR_NU_VAL_OBS):
		qDebug() << "NOM_ATTR_NU_VAL_OBS";
		delete nu_obs_value;
		break;
	case(NOM_ATTR_NU_CMPD_VAL_OBS):
		qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
		delete nu_obs_val_cmp;
		break;
	case(NOM_ATTR_TIME_STAMP_ABS):
		qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
		delete absolute_time;
		break;
	case(NOM_ATTR_TIME_STAMP_REL):
		break;
	case(NOM_ATTR_ID_LABEL):
		qDebug() << "NOM_ATTR_ID_LABEL";
		break;
	case(NOM_ATTR_ID_LABEL_STRING):
		qDebug() << "NOM_ATTR_ID_LABEL_STRING";
		delete string;
		break;
	case(NOM_ATTR_COLOR):
		qDebug() << "NOM_ATTR_COLOR";
		break;
	case(NOM_ATTR_METRIC_SPECN):
		qDebug() << "NOM_ATTR_METRIC_SPECN";
		delete metric_spec;
		break;
	case(NOM_ATTR_SA_SPECN):
		qDebug() << "NOM_ATTR_SA_SPECN";
		delete sa_spec;
		break;
	case(NOM_ATTR_SA_FIXED_VAL_SPECN):
		qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
		delete sa_fixed_val_spec16;
		break;
	case(NOM_ATTR_TIME_PD_SAMP):
		break;
	case(NOM_ATTR_METRIC_STAT):
		break;
	case(NOM_ATTR_UNIT_CODE):
		break;
	case(NOM_ATTR_MODE_MSMT):
		break;
	case(NOM_ATTR_METRIC_INFO_LABEL):
		break;
	case(NOM_ATTR_METRIC_INFO_LABEL_STR):
		qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
		delete string;
		break;
	case(NOM_ATTR_SCALE_SPECN_I16):
		qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
		delete scale_range_spec16;
		break;
	case(NOM_ATTR_SA_RANGE_PHYS_I16):
		qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
		delete scaled_range_16;
		break;
	case(NOM_ATTR_SA_VAL_OBS):
		qDebug() << "NOM_ATTR_SA_VAL_OBS";
		delete sa_obs_value;
		break;
	case(NOM_ATTR_SA_CMPD_VAL_OBS):
		qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
		delete sa_obs_value_cmp;
		break;
	case(NOM_ATTR_PCOL_SUPPORT):
		qDebug() << "NOM_ATTR_PCOL_SUPPORT";
		delete proto_support;
		break;
	case(NOM_ATTR_NET_ADDR_INFO):
		qDebug() << "NOM_ATTR_NET_ADDR_INFO";
		delete ip_address_info;
		break;
	default:
		qDebug() << "NO MATCHING ID";
	}
	
	
};
*/
Object::Object(OIDType attribute_id, quint16 length, QDataStream &converter)
{

	ID=attribute_id;

	int size=0;
	this->length=length;
    quint8 byte;
    switch(attribute_id){
    case (NOM_ATTR_TIME_PD_POLL):
        //qDebug() << "NOM_ATTR_TIME_PD_POLL";
        poll_data_req_period = new PollDataReqPeriod(converter, size);
		//poll_data_req_period->print();
        break;
    case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
        //qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
		size-=2;
        converter >> number_of_prioritized_objects;
        //init u16
        break;
    case(NOM_POLL_PROFILE_SUPPORT):
        //qDebug() << "NOM_POLL_PROFILE_SUPPORT";
        poll_profile_support = new PollProfileSupport(converter, size);
        break;
    case(NOM_ATTR_POLL_PROFILE_EXT):
        //qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
        poll_profile_ext = new PollProfileExt(converter, size);
        break;
    case(NOM_ATTR_ID_HANDLE):
        //qDebug() << "NOM_ATTR_ID_HANDLE";
        converter >> handle;// = initHandle(datagram);
        break;
    case(NOM_ATTR_ID_TYPE):
        //qDebug() << "NOM_ATTR_ID_TYPE";
        type = new TYPE(converter);
        break;
    case(NOM_ATTR_NU_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_VAL_OBS";
        nu_obs_value = new NuObsValue(converter, size);
        break;
    case(NOM_ATTR_NU_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
        nu_obs_val_cmp = new NuObsValueCmp(converter, size);
		//nu_obs_val_cmp->print();
		break;
    case(NOM_ATTR_TIME_STAMP_ABS):
        //qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
        absolute_time = new AbsoluteTime(converter, size);
        break;
    case(NOM_ATTR_TIME_STAMP_REL):
        //qDebug() << "NOM_ATTR_TIME_STAMP_REL";
        converter >> relative_time;// = initRelativeTime(datagram);

        break;
    case(NOM_ATTR_ID_LABEL):
        //qDebug() << "NOM_ATTR_ID_LABEL";
        converter >> text_id;// = initTextId(datagram);
        break;
    case(NOM_ATTR_ID_LABEL_STRING):
        //qDebug() << "NOM_ATTR_ID_LABEL_STRING";
        string = new String(converter, size);
        break;
    case(NOM_ATTR_COLOR):
        //qDebug() << "NOM_ATTR_COLOR";
        converter >> simple_colour;// = initSimpleColour(datagram);
        break;
    case(NOM_ATTR_METRIC_SPECN):
        //qDebug() << "NOM_ATTR_METRIC_SPECN";
        metric_spec = new MetricSpec(converter, size);
        break;
    case(NOM_ATTR_SA_SPECN):
        //qDebug() << "NOM_ATTR_SA_SPECN";
        sa_spec = new SaSpec(converter, size);
        break;
    case(NOM_ATTR_SA_FIXED_VAL_SPECN):
        //qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
        sa_fixed_val_spec16 = new SaFixedValSpec16(converter, size);
        break;
    case(NOM_ATTR_TIME_PD_SAMP):
        //qDebug() << "NOM_ATTR_TIME_PD_SAMP";
        converter >> relative_time;// = initRelativeTime(datagram);
        break;
    case(NOM_ATTR_METRIC_STAT):
        //qDebug() << "NOM_ATTR_METRIC_STAT";
        converter >> metric_state;// = initMetricState(datagram);
        break;
    case(NOM_ATTR_UNIT_CODE):
        //qDebug() << "NOM_ATTR_UNIT_CODE";
        converter >> oid_type;// = initOIDType(datagram);
        break;
    case(NOM_ATTR_MODE_MSMT):
        //qDebug() << "NOM_ATTR_MODE_MSMT";
        converter >> measure_mode;// = initMeasureMode(datagram);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL):
        //qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
        converter >> text_id;// = initTextId(datagram);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL_STR):
        //qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
        string = new String(converter, size);
        break;
    case(NOM_ATTR_SCALE_SPECN_I16):
        //qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
        scale_range_spec16 = new ScaleRangeSpec16(converter, size);
        break;
    case(NOM_ATTR_SA_RANGE_PHYS_I16):
        //qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
        scaled_range_16 = new ScaledRange16(converter, size);
        break;
    case(NOM_ATTR_SA_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_VAL_OBS";
        sa_obs_value = new SaObsValue(converter, size);
        break;
    case(NOM_ATTR_SA_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
        sa_obs_value_cmp = new SaObsValueCmp(converter, size);
        break;
    case(NOM_ATTR_PCOL_SUPPORT):
        //qDebug() << "NOM_ATTR_PCOL_SUPPORT";
        proto_support = new ProtoSupport(converter, size);
        break;
    case(NOM_ATTR_NET_ADDR_INFO):
        //qDebug() << "NOM_ATTR_NET_ADDR_INFO";
        ip_address_info = new IpAddressInfo(converter, size);
        break;
	case(NOM_ATTR_TIME_ABS):
		//qDebug() << "NOM_ATTR_TIME_ABS";
		absolute_time = new AbsoluteTime(converter, size);
		break;
	case(NOM_ACT_POLL_MDIB_DATA):
		//qDebug()  << "NOM_ACT_POLL_MDIB_DATA";
		poll_mdib_data_reply=new PollMdibDataReply(converter, size);
		break;
	case(NOM_ACT_POLL_MDIB_DATA_EXT):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA_EXT";
		poll_mdib_data_reply_ext = new PollMdibDataReplyExt(converter, size);
		//poll_mdib_data_reply_ext->print();
		break;
	case(NOM_ATTR_POLL_NU_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_NU_PRIO_LIST";
		text_id_list = new TextIdList(converter);
		break;
	case(NOM_ATTR_POLL_RTSA_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_RTSA_PRIO_LIST";
		text_id_list = new TextIdList(converter);
		break;
	case(NOM_ATTR_SA_CALIB_I16):
		//qDebug() << "NOM_ATTR_SA_CALIB_I16";
		sa_cal_data_16 = new SaCalData16(converter);
		break;
    default:
		//qDebug() << "DEFAULT, ID: " << ID;
        for(int i=0; i<length; i++)
		{
			size-=1;
            converter >> byte;
		}
    };
};

QByteArray Object::getObject(){
	QByteArray datagram;

	quint8 byte=0;
    switch(ID){
    case (NOM_ATTR_TIME_PD_POLL):
        //qDebug() << "NOM_ATTR_TIME_PD_POLL";
		appendData(datagram, poll_data_req_period->getPollDataReqPeriod());
        break;
    case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
        //qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
		appendData(datagram, number_of_prioritized_objects);
        break;
    case(NOM_POLL_PROFILE_SUPPORT):
        //qDebug() << "NOM_POLL_PROFILE_SUPPORT";
		appendData(datagram, poll_profile_support->getPollProfileSupport());
        break;
    case(NOM_ATTR_POLL_PROFILE_EXT):
        //qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
		appendData(datagram, poll_profile_ext->getPollProfileExt());
        break;
    case(NOM_ATTR_ID_HANDLE):
        //qDebug() << "NOM_ATTR_ID_HANDLE";
		appendData(datagram, handle);
        break;
    case(NOM_ATTR_ID_TYPE):
        //qDebug() << "NOM_ATTR_ID_TYPE";
        appendData(datagram, type->getTYPE());
        break;
    case(NOM_ATTR_NU_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_VAL_OBS";
		appendData(datagram, nu_obs_value->getNuObsValue());
        break;
    case(NOM_ATTR_NU_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
        appendData(datagram, nu_obs_val_cmp->getNuObsValueCmp());
        break;
    case(NOM_ATTR_TIME_STAMP_ABS):
        //qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
		appendData(datagram, absolute_time->getAbsoluteTime());
        break;
    case(NOM_ATTR_TIME_STAMP_REL):
        //qDebug() << "NOM_ATTR_TIME_STAMP_REL";
		appendData(datagram, relative_time);
        break;
    case(NOM_ATTR_ID_LABEL):
        //qDebug() << "NOM_ATTR_ID_LABEL";
		appendData(datagram, text_id);
        break;
    case(NOM_ATTR_ID_LABEL_STRING):
        //qDebug() << "NOM_ATTR_ID_LABEL_STRING";
        appendData(datagram, string->getString());
        break;
    case(NOM_ATTR_COLOR):
        //qDebug() << "NOM_ATTR_COLOR";
		appendData(datagram, simple_colour);
        break;
    case(NOM_ATTR_METRIC_SPECN):
        //qDebug() << "NOM_ATTR_METRIC_SPECN";
        appendData(datagram, metric_spec->getMetricSpec());
        break;
    case(NOM_ATTR_SA_SPECN):
        //qDebug() << "NOM_ATTR_SA_SPECN";
        appendData(datagram, sa_spec->getSaSpec());
        break;
    case(NOM_ATTR_SA_FIXED_VAL_SPECN):
        //qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
		appendData(datagram, sa_fixed_val_spec16->getSaFixedValSpec16());
        break;
    case(NOM_ATTR_TIME_PD_SAMP):
        //qDebug() << "NOM_ATTR_TIME_PD_SAMP";
		appendData(datagram, relative_time);
        break;
    case(NOM_ATTR_METRIC_STAT):
        //qDebug() << "NOM_ATTR_METRIC_STAT";
		appendData(datagram, metric_state);
        break;
    case(NOM_ATTR_UNIT_CODE):
        //qDebug() << "NOM_ATTR_UNIT_CODE";
		appendData(datagram, oid_type);
        break;
    case(NOM_ATTR_MODE_MSMT):
        //qDebug() << "NOM_ATTR_MODE_MSMT";
		appendData(datagram, measure_mode);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL):
        //qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
		appendData(datagram, text_id);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL_STR):
        //qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
		appendData(datagram, string->getString());
        break;
    case(NOM_ATTR_SCALE_SPECN_I16):
        //qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
        appendData(datagram, scale_range_spec16->getScaleRangeSpec16());
        break;
    case(NOM_ATTR_SA_RANGE_PHYS_I16):
        //qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
		appendData(datagram, scaled_range_16->getScaledRange16());
        break;
    case(NOM_ATTR_SA_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_VAL_OBS";
		appendData(datagram, sa_obs_value->getSaObsValue());
        break;
    case(NOM_ATTR_SA_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
        appendData(datagram, sa_obs_value_cmp->getSaObsValueCmp());
        break;
    case(NOM_ATTR_PCOL_SUPPORT):
        //qDebug() << "NOM_ATTR_PCOL_SUPPORT";
        appendData(datagram, proto_support->getProtoSupport());
        break;
    case(NOM_ATTR_NET_ADDR_INFO):
        //qDebug() << "NOM_ATTR_NET_ADDR_INFO";
        appendData(datagram, ip_address_info->getIpAddressInfo());
        break;
	case(NOM_ACT_POLL_MDIB_DATA_EXT):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA_EXT";
		appendData(datagram, poll_mdib_data_reply_ext->getPollMdibDataReplyExt());
		break;
	case(NOM_ATTR_POLL_NU_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_NU_PRIO_LIST";
	case(NOM_ATTR_POLL_RTSA_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_RTSA_PRIO_LIST";
		appendData(datagram, text_id_list->getTextIdList());
		break;
	case(NOM_ATTR_SA_CALIB_I16):
		//qDebug() << "NOM_ATTR_SA_CALIB_I16";
		appendData(datagram, sa_cal_data_16->getSaCalData16());
		break;
    default:
        //qDebug() << "DEFAULT";
        for(int i=0; i<length; i++)
			appendData(datagram, byte);
    };
	int size2= datagram.size();
	//qDebug() << "AVA size: " << size2-size1;
    return datagram;
};


void * Object::getAttribute(){
	//qDebug() << "Get attribute";
	
    switch(ID){
    case (NOM_ATTR_TIME_PD_POLL):
       //qDebug() << "NOM_ATTR_TIME_PD_POLL";
        return poll_data_req_period;

    case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
        //qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
        return &number_of_prioritized_objects;

    case(NOM_POLL_PROFILE_SUPPORT):
        //qDebug() << "NOM_POLL_PROFILE_SUPPORT";
        return poll_profile_support;

    case(NOM_ATTR_POLL_PROFILE_EXT):
        //qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
        return poll_profile_ext;

    case(NOM_ATTR_ID_HANDLE):
        //qDebug() << "NOM_ATTR_ID_HANDLE";
        return &handle;

    case(NOM_ATTR_ID_TYPE):
        //qDebug() << "NOM_ATTR_ID_TYPE";
        return type;

    case(NOM_ATTR_NU_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_VAL_OBS";
        return nu_obs_value;

    case(NOM_ATTR_NU_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
        return nu_obs_val_cmp;

    case(NOM_ATTR_TIME_STAMP_ABS):
        //qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
        return absolute_time;

    case(NOM_ATTR_TIME_STAMP_REL):
        //qDebug() << "NOM_ATTR_TIME_STAMP_REL";
        return &relative_time;

    case(NOM_ATTR_ID_LABEL):
        //qDebug() << "NOM_ATTR_ID_LABEL";
        return &text_id;

    case(NOM_ATTR_ID_LABEL_STRING):
        //qDebug() << "NOM_ATTR_ID_LABEL_STRING";
        return string;

    case(NOM_ATTR_COLOR):
       // qDebug() << "NOM_ATTR_COLOR";
        return &simple_colour;

    case(NOM_ATTR_METRIC_SPECN):
        //qDebug() << "NOM_ATTR_METRIC_SPECN";
        return metric_spec;

    case(NOM_ATTR_SA_SPECN):
        //qDebug() << "NOM_ATTR_SA_SPECN";
        return sa_spec;

    case(NOM_ATTR_SA_FIXED_VAL_SPECN):
        //qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
        return sa_fixed_val_spec16;

    case(NOM_ATTR_TIME_PD_SAMP):
        //qDebug() << "NOM_ATTR_TIME_PD_SAMP";
        return &relative_time;

    case(NOM_ATTR_METRIC_STAT):
        //qDebug() << "NOM_ATTR_METRIC_STAT";
        return &metric_state;

    case(NOM_ATTR_UNIT_CODE):
        //qDebug() << "NOM_ATTR_UNIT_CODE";
        return &oid_type;// = initOIDType(datagram);

    case(NOM_ATTR_MODE_MSMT):
       // qDebug() << "NOM_ATTR_MODE_MSMT";
        return &measure_mode;

    case(NOM_ATTR_METRIC_INFO_LABEL):
       // qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
        return &text_id;

    case(NOM_ATTR_METRIC_INFO_LABEL_STR):
       // qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
        return string;

    case(NOM_ATTR_SCALE_SPECN_I16):
        //qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
        return scale_range_spec16;

    case(NOM_ATTR_SA_RANGE_PHYS_I16):
       // qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
        return scaled_range_16;

    case(NOM_ATTR_SA_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_VAL_OBS";
        return sa_obs_value;

    case(NOM_ATTR_SA_CMPD_VAL_OBS):
        //qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
        return sa_obs_value_cmp;

    case(NOM_ATTR_PCOL_SUPPORT):
        //qDebug() << "NOM_ATTR_PCOL_SUPPORT";
        return proto_support;

    case(NOM_ATTR_NET_ADDR_INFO):
        //qDebug() << "NOM_ATTR_NET_ADDR_INFO";
        return ip_address_info;
	case(NOM_ACT_POLL_MDIB_DATA):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA";
		return poll_mdib_data_reply;

	case(NOM_ACT_POLL_MDIB_DATA_EXT):
		//qDebug() << "NOM_ACT_POLL_MDIB_DATA_EXT";
		return poll_mdib_data_reply_ext;
	case(NOM_ATTR_POLL_NU_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_NU_PRIO_LIST";
	case(NOM_ATTR_POLL_RTSA_PRIO_LIST):
		//qDebug() << "NOM_ATTR_POLL_RTSA_PRIO_LIST";
		return text_id_list;
	case(NOM_ATTR_SA_CALIB_I16):
		//qDebug() << "NOM_ATTR_SA_CALIB_I16";
		return sa_cal_data_16;
    default:
		//qDebug() << "NO MATCHING ATTRIBUTE: "<<ID;
        return NULL;
    };
	
}

void Object::print(std::string title)
{
	qDebug() << QString::fromUtf8(title.c_str(), title.size());
	qDebug() <<"OIDType attribute_id: " << ID;
	qDebug() <<"quint16 length: " << length;
	switch(ID){
    case (NOM_ATTR_TIME_PD_POLL):
        qDebug() << "NOM_ATTR_TIME_PD_POLL";
        poll_data_req_period->print();
		break;
    case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
        qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
		qDebug() << "quint16 number_of_prioritized_objects: " << number_of_prioritized_objects;
		break;
    case(NOM_POLL_PROFILE_SUPPORT):
        qDebug() << "NOM_POLL_PROFILE_SUPPORT";
        poll_profile_support->print();
		break;
    case(NOM_ATTR_POLL_PROFILE_EXT):
        qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
		poll_profile_ext->print();
		break;
    case(NOM_ATTR_ID_HANDLE):
        qDebug() << "NOM_ATTR_ID_HANDLE";
		qDebug() << "quint16 handle: " << handle;
		break;
    case(NOM_ATTR_ID_TYPE):
        qDebug() << "NOM_ATTR_ID_TYPE";
		type->print();
		break;
    case(NOM_ATTR_NU_VAL_OBS):
        qDebug() << "NOM_ATTR_NU_VAL_OBS";
		nu_obs_value->print();
		break;
    case(NOM_ATTR_NU_CMPD_VAL_OBS):
        qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
		nu_obs_val_cmp->print();
		break;
    case(NOM_ATTR_TIME_STAMP_ABS):
        qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
		absolute_time->print();
		break;
    case(NOM_ATTR_TIME_STAMP_REL):
        qDebug() << "NOM_ATTR_TIME_STAMP_REL";
		qDebug() << "RelativeTime relative_time: " << relative_time;
		break;
    case(NOM_ATTR_ID_LABEL):
        qDebug() << "NOM_ATTR_ID_LABEL";
		qDebug() << "TextId text_id: " << text_id;
		break;
    case(NOM_ATTR_ID_LABEL_STRING):
        qDebug() << "NOM_ATTR_ID_LABEL_STRING";
		string->print();
		break;
    case(NOM_ATTR_COLOR):
        qDebug() << "NOM_ATTR_COLOR";
		qDebug() << "SimpleColour simple_colour: " << simple_colour;
		break;
    case(NOM_ATTR_METRIC_SPECN):
        qDebug() << "NOM_ATTR_METRIC_SPECN";
		metric_spec->print();
		break;
    case(NOM_ATTR_SA_SPECN):
        qDebug() << "NOM_ATTR_SA_SPECN";
		sa_spec->print();
		break;
    case(NOM_ATTR_SA_FIXED_VAL_SPECN):
        qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
		sa_fixed_val_spec16->print();
		break;
    case(NOM_ATTR_TIME_PD_SAMP):
        qDebug() << "NOM_ATTR_TIME_PD_SAMP";
		qDebug() << "RelativeTime relative_time: " << relative_time;
		break;
    case(NOM_ATTR_METRIC_STAT):
        qDebug() << "NOM_ATTR_METRIC_STAT";
		qDebug() << "MetricState metric_state: " << metric_state;
        break;
    case(NOM_ATTR_UNIT_CODE):
        qDebug() << "NOM_ATTR_UNIT_CODE";
		qDebug() << "OIDType oid_type: " << oid_type;
		break;
    case(NOM_ATTR_MODE_MSMT):
        qDebug() << "NOM_ATTR_MODE_MSMT";
		qDebug() << "MeasureMode measure_mode: " << measure_mode;
		break;
    case(NOM_ATTR_METRIC_INFO_LABEL):
        qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
		qDebug() << "TextId text_id: " << text_id;
		break;
    case(NOM_ATTR_METRIC_INFO_LABEL_STR):
        qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
		string->print();
		break;
    case(NOM_ATTR_SCALE_SPECN_I16):
        qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
		scale_range_spec16->print();
		break;
    case(NOM_ATTR_SA_RANGE_PHYS_I16):
        qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
		scaled_range_16->print();
		break;
    case(NOM_ATTR_SA_VAL_OBS):
        qDebug() << "NOM_ATTR_SA_VAL_OBS";
		sa_obs_value->print();
		break;
    case(NOM_ATTR_SA_CMPD_VAL_OBS):
        qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
		sa_obs_value_cmp->print();
		break;
    case(NOM_ATTR_PCOL_SUPPORT):
        qDebug() << "NOM_ATTR_PCOL_SUPPORT";
		proto_support->print();
		break;
    case(NOM_ATTR_NET_ADDR_INFO):
        qDebug() << "NOM_ATTR_NET_ADDR_INFO";
        ip_address_info->print();
		break;
	case(NOM_ACT_POLL_MDIB_DATA):
		qDebug() << "NOM_ACT_POLL_MDIB_DATA";
		poll_mdib_data_reply->print();
		break;
	case(NOM_ACT_POLL_MDIB_DATA_EXT):
		qDebug() << "NOM_ACT_POLL_MDIB_DATA_EXT";
		poll_mdib_data_reply_ext->print();
		break;
	case(NOM_ATTR_POLL_NU_PRIO_LIST):
		qDebug() << "NOM_ATTR_POLL_NU_PRIO_LIST";
	case(NOM_ATTR_POLL_RTSA_PRIO_LIST):
		qDebug() << "NOM_ATTR_POLL_RTSA_PRIO_LIST";
		text_id_list->print();
		break;
	case(NOM_ATTR_SA_CALIB_I16):
		qDebug() << "NOM_ATTR_SA_CALIB_I16";
		sa_cal_data_16->print();
		break;
    default:
		qDebug() << "NO MATCHING ATTRIBUTE: " << ID;
        break;
    };

	qDebug() << "---------End OBJECT---------";
}
OIDType Object::getID()
{
	return ID;
}
/*
void processOIDType(OIDType id, QDataStream &converter)
{
	int size=0;
	PollMdibDataReq poll_mdib_data_req;
	NuObsValue nu_obs_value;
	switch(id)
	{
	case NOM_ATTR_NU_VAL_OBS:
		qDebug() << "NOM_ATTR_NU_VAL_OBS" ;
		nu_obs_value=NuObsValue(converter, size);
		break;
	case NOM_ATTR_NU_CMPD_VAL_OBS:
		qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS" ;
		break;
	case NOM_ATTR_TIME_STAMP_ABS:
		qDebug() << "NOM_ATTR_TIME_STAMP_ABS" ;
		break;
	case NOM_ATTR_TIME_STAMP_REL:
		qDebug() << "NOM_ATTR_TIME_STAMP_REL" ;
		break;
	case NOM_ACT_POLL_MDIB_DATA:
		qDebug() << "NOM_ACT_POLL_MDIB_DATA" ;
		poll_mdib_data_req=PollMdibDataReq(converter, size);
		break;
	default:
		qDebug() << "Not defined ID:" << id;
	}
}
*/