#include "protocolCommands.h"
#include "UDPStructures.h"
#include <QDataStream>
#include <QDebug>

QByteArray extractBytes(QDataStream &conv, int size){
    QByteArray tmp;
    quint8 byte;
    for(int i=0;i<size;i++){
        conv >> byte;
        tmp.append(byte);
    }
    return tmp;
}
/*
AbsoluteTime initAbsoluteTime(QDataStream &converter){
    // = (AbsoluteTime*)malloc(sizeof(AbsoluteTime));
	quint8 century;
    quint8 year;
    quint8 month;
    quint8 day;
    quint8 hour;
    quint8 minute;
    quint8 second;
    quint8 sec_fractions;
    converter >> century >> year >> month >> day >> hour
              >> minute >> second >> sec_fractions;
	AbsoluteTime s(century, year, month, day, hour, minute, second, sec_fractions);
	return s;	
}
*/
/*
TYPE initTYPE(QDataStream &converter){
    ///TYPE * s = (TYPE*)malloc(sizeof(TYPE));
	NomPartition partition;
    OIDType code;
    converter >> partition >> code;
	TYPE s(partition, code);
    return s;
}
*/
/*
GlbHandle initGlbHandle(QDataStream &converter){
    //GlbHandle * s = (GlbHandle*)malloc(sizeof(GlbHandle));
	MdsContext context_id;
    Handle handle;
    converter >> context_id >> handle;
	GlbHandle s(context_id, handle);
    return s;
}
*/
/*
ManagedObjectId initManagedObjectId(QDataStream &converter){
   // ManagedObjectId * s = (ManagedObjectId *)malloc(sizeof(ManagedObjectId));
	OIDType m_obj_class;
    converter >> m_obj_class;// >> s->m_obj_inst.context_id >> s->m_obj_inst.handle;

	GlbHandle m_obj_inst=initGlbHandle(converter);
	ManagedObjectId  s(m_obj_class, m_obj_inst);
    return s;
}
*/
/*
AVAType initAVAType(QDataStream &converter, OIDType, quint16);

AttributeList initAttributeList(QDataStream &converter, quint16 count, quint16 length){
    //AttributeList * s = (AttributeList *)malloc(sizeof(AttributeList));

    AVAType *value;
    value = new AVAType[count];
    OIDType id;
    quint16 AVAlength;
	converter >> id >> AVAlength;
    for(int i =0;i<count; i++)
	{
        value[i]= initAVAType(converter, id, AVAlength);
    }
	AttributeList s(count, length, value);
    return s;
}
*/
/*
String initString(QDataStream &converter, quint16 length){
    //String * s = (String *)malloc(sizeof(String));
	quint16 length;
    quint16 *value = new quint16[length/2];

    for(int i =0;i<length/2; i++)
        converter >> value[i];

	String s(length, value); 
    return s;
}
*/
/*
VariableLabel initVariableLabel(QDataStream &converter, quint16 length){
    //VariableLabel * s = (VariableLabel *)malloc(sizeof(VariableLabel));
	quint16 length;
    quint8 *value = new quint8[length];

    for(int i =0;i<length; i++)
        converter >> value[i];

	VariableLabel s(length, value);
    return s;
}
*/
/*
SPpdu initSPpdu(QDataStream &converter){
    //SPpdu * s = (SPpdu *)malloc(sizeof(SPpdu));
	quint16 session_id;
    quint16 p_context_id; 

    converter >> session_id >> p_context_id;
	SPpdu s(session_id, p_context_id); 
    return s;
}
*/
/*
ROapdus initROapdus(QDataStream &converter){
    //ROapdus * s = (ROapdus *)malloc(sizeof(ROapdus));
	quint16 ro_type;
    quint16 length; 

    converter >> ro_type >> length;
	ROapdus s(ro_type, length);
    return s;
}
*/
/*
ROIVapdu initROIVapdu(QDataStream &converter){
    //ROIVapdu * s = (ROIVapdu *)malloc(sizeof(ROIVapdu));
	quint16 invoke_id;
    CMDType command_type;
    quint16 length;

    converter >> invoke_id >> command_type >> length;
	ROIVapdu s(invoke_id, command_type, length);
    return s;
}
*/
/*
RORSapdu initRORSapdu(QDataStream &converter){
    //RORSapdu * s = (RORSapdu *)malloc(sizeof(RORSapdu));
	quint16 invoke_id;
    CMDType command_type;
    quint16 length;

    converter >> invoke_id >> command_type >> length;
	RORSapdu s(invoke_id, command_type, length);
    return s;
}
*/
/*
RorlsId initRorlsId(QDataStream &converter){
    //RorlsId * s = (RorlsId *)malloc(sizeof(RorlsId));
	quint8 state;
    quint8 count;

    converter >> state >> count;
	RorlsId s(state, count); 
    return s;
}
*/
/*
ROLRSapdu initROLRSapdu(QDataStream &converter){
    //ROLRSapdu * s = (ROLRSapdu *)malloc(sizeof(ROLRSapdu));

	RorlsId linked_id=initRorlsId(converter);
    quint16 invoke_id;
    CMDType command_type;
    quint16 length;
    converter >> invoke_id >> command_type >> length;
	ROLRSapdu s(linked_id, invoke_id, command_type, length);
    return s;
}
*/
/*
ROERapdu initROERapdu(QDataStream &converter){
    //ROERapdu * s = (ROERapdu *)malloc(sizeof(ROERapdu));
	quint16 invoke_id;
    quint16 error_value;
    quint16 length;

    converter >> invoke_id >> error_value >> length;
	ROERapdu s(invoke_id, error_value, length);
    return s;
}
*/
/*
GetError initGetError(QDataStream &converter){
    //GetError * s = (GetError *)malloc(sizeof(GetError));
	ErrorStatus error_status;
    OIDType attribute_id;

    converter >> error_status >> attribute_id;
	GetError s(error_status, attribute_id);
    return s;
}
*/
/*
getInfoList initGetInfoList(QDataStream &converter, quint16 count, quint16 length) 
{
    GetError *value = new GetError[count];

	for(int i=0; i<count;i++)
		value[i]=initGetError(converter);

	getInfoList s(count, length, value);// (count, length, value);
	return s;
}
*/
/*
GetListError initGetListError(QDataStream &converter){
    //GetListError * s = (GetListError *)malloc(sizeof(GetListError));

	quint16 count;
	quint16 length;
	converter >> count >> length;
	getInfoList get_info_list = initGetInfoList(converter, count, length);
    ManagedObjectId *managed_object;

    
    ManagedObjectId managed_object=new ManagedObjectId(;
    managed_object=initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->getInfoList.count >> s->getInfoList.length;

    s->getInfoList.value = new GetError*[s->getInfoList.count];

    for(int i =0;i<s->getInfoList.count; i++){
        s->getInfoList.value[i]=new GetError;
        s->getInfoList.value[i]=initGetError(extractBytes(converter, sizeof(GetError)));
    }
	GetListError s;
    return s;
}
*/
/*
SetError * initSetError(QByteArray datagram){
    SetError * s = (SetError *)malloc(sizeof(SetError));
    QDataStream converter(datagram);
    converter >> s->errorStatus >> s->modifyOperator >> s->attributeId;
    return s;
}
*/
/*
SetListError * initSetListError(QByteArray datagram){
    SetListError * s = (SetListError *)malloc(sizeof(SetListError));
    QDataStream converter(datagram);
    s->managed_object=new ManagedObjectId;
    s->managed_object=initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->setInfoList.count >> s->setInfoList.length;

    s->setInfoList.value = new SetError*[s->setInfoList.count];

    for(int i =0;i<s->setInfoList.count; i++){
        s->setInfoList.value[i]=new SetError;
        s->setInfoList.value[i]=initSetError(extractBytes(converter, sizeof(SetError)));
    }
    return s;
}
*/
/*
ProcessingFailure * initProcessingFailure(QByteArray datagram){
    ProcessingFailure * s = (ProcessingFailure *)malloc(sizeof(ProcessingFailure));
    QDataStream converter(datagram);
    converter >> s->error_id >> s->length;
    return s;
}
*/
/*
EventReportArgument * initEventReportArgument(QByteArray datagram){
    EventReportArgument * s = (EventReportArgument *)malloc(sizeof(EventReportArgument));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->event_time >> s->event_type >> s->length;
    return s;
}
*/
/*
EventReportResult * initEventReportResult(QByteArray datagram){
    EventReportResult * s = (EventReportResult *)malloc(sizeof(EventReportResult));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->current_time >> s->event_type >> s->length;
    return s;
}
*/
/*
ActionArgument * initActionArgument(QByteArray datagram){
    ActionArgument * s = (ActionArgument *)malloc(sizeof(ActionArgument));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->scope >> s->action_type >> s->length;
    return s;
}
*/
/*
ActionResult * initActionResult(QByteArray datagram){
    ActionResult * s = (ActionResult *)malloc(sizeof(ActionResult));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->action_type >> s->length;
    return s;
}
*/
/*
AttributeIdList * initAttributeIdList(QByteArray datagram, quint16 count, quint16 length){
    AttributeIdList * s = (AttributeIdList *)malloc(sizeof(AttributeIdList));
    QDataStream converter(datagram);
    s->count = count;
    s->length = length;
    s->value= new OIDType[s->count];

    for(int i=0; i<s->count; i++)
        converter >> s->value[i];
    return s;
}
*/
/*
GetArgument * initGetArgument(QByteArray datagram){
    GetArgument * s = (GetArgument *)malloc(sizeof(GetArgument));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->scope;
    s->attribute_id_list = new AttributeIdList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->attribute_id_list = initAttributeIdList(extractBytes(converter, length), count, length);
    return s;
}
*/
/*
GetResult * initGetResult(QByteArray datagram){
    GetResult * s = (GetResult *)malloc(sizeof(GetResult));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));

    s->attribute_list = new AttributeList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->attribute_list = initAttributeList(extractBytes(converter, length), count, length);
    return s;
}
*/
/*
AttributeModEntry * initAttributeModEntry(QByteArray datagram, ModifyOperator MO, OIDType id, quint16 length){
    AttributeModEntry * s = (AttributeModEntry *)malloc(sizeof(AttributeModEntry));
    QDataStream converter(datagram);
    s->modify_operator = MO;
    s->attribute = new AVAType;
    s->attribute = initAVAType(extractBytes(converter, length), id, length);
    return s;
}
*/
/*
ModificationList * initModificationList(QByteArray datagram, quint16 count, quint16 length){
    ModificationList * s = (ModificationList *)malloc(sizeof(ModificationList));
    QDataStream converter(datagram);
    s->count = count;
    s->length = length;

    s->value= new AttributeModEntry*[s->count];

    ModifyOperator tmpMO;
    OIDType tmpID;
    quint16 tmpLength;
    converter >> tmpMO >> tmpID >> tmpLength;

    for(int i =0;i<s->count; i++){
        s->value[i]=new AttributeModEntry;
        s->value[i]=initAttributeModEntry(extractBytes(converter, length), tmpMO, tmpID, tmpLength);
    }
    return s;
}
*/
/*
SetArgument * initSetArgument(QByteArray datagram){
    SetArgument * s = (SetArgument *)malloc(sizeof(SetArgument));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    converter >> s->scope;
    s->modification_list = new ModificationList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->modification_list = initModificationList(extractBytes(converter, length), count, length);
    return s;
}
*/
/*
SetResult * initSetResult(QByteArray datagram){
    SetResult * s = (SetResult *)malloc(sizeof(SetResult));
    QDataStream converter(datagram);
    s->managed_object = new ManagedObjectId;
    s->managed_object = initManagedObjectId(extractBytes(converter, sizeof(ManagedObjectId)));
    s->attribute_list = new AttributeList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->attribute_list = initAttributeList(extractBytes(converter, length), count, length);
    return s;
}
*/

ConnectIndication * initConnectIndication(QByteArray datagram){
    ConnectIndication * s = (ConnectIndication *)malloc(sizeof(ConnectIndication));
    QDataStream converter(datagram);
	/*
    converter >> s->nomenclature;

    s->ro_apdus=new ROapdus;
    s->roiv_apdu=new ROIVapdu;
    s->event_report_argument=new EventReportArgument;
    s->connect_ind_info=new ConnectIndInfo;

    s->ro_apdus =               initROapdus(extractBytes(converter, sizeof(ROapdus)));
    s->roiv_apdu =              initROIVapdu(extractBytes(converter, sizeof(ROIVapdu)));
    s->event_report_argument =  initEventReportArgument(extractBytes(converter, EVENT_REPORT_ARGUMENT_SIZE));

    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->connect_ind_info =       initAttributeList(extractBytes(converter, length), count, length);
	*/
    return s;
}
/*
PollDataReqPeriod * initPollDataReqPeriod(QByteArray datagram){
    PollDataReqPeriod * s =(PollDataReqPeriod *)malloc(sizeof(PollDataReqPeriod));
    QDataStream converter(datagram);
    converter >> s->active_period;
    return s;
}
*/
/*
PollProfileSupport * initPollProfileSupport(QByteArray datagram){
    PollProfileSupport * s =(PollProfileSupport *)malloc(sizeof(PollProfileSupport));
    QDataStream converter(datagram);
    converter >> s->poll_profile_revision;
    converter >> s->min_poll_period;
    converter >> s->max_mtu_rx;
    converter >> s->max_mtu_tx;
    converter >> s->max_bw_tx;
    converter >> s->options;
    s->optional_packages = new AttributeList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->optional_packages = initAttributeList(extractBytes(converter, length), count, length);
    return s;
}
*/
/*
PollProfileExt * initPollProfileExt(QByteArray datagram){
    PollProfileExt * s =(PollProfileExt *)malloc(sizeof(PollProfileExt));
    QDataStream converter(datagram);
    converter >> s->options;
    s->ext_attr = new AttributeList;
    quint16 count;
    quint16 length;
    converter >> count >> length;
    s->ext_attr = initAttributeList(extractBytes(converter, length), count, length);
    return s;
}
*/
/*
NuObsValue * initNuObsValue(QByteArray datagram){
    NuObsValue * s =(NuObsValue *)malloc(sizeof(NuObsValue));
    QDataStream converter(datagram);
    converter >> s->physio_id;
    converter >> s->state;
    converter >> s->unit_code;
    converter >> s->value;
    return s;
}
*/
/*
NuObsValueCmp * initNuObsValueCmp(QByteArray datagram, quint16 count, quint16 length){
    NuObsValueCmp * s = (NuObsValueCmp *)malloc(sizeof(NuObsValueCmp));
    QDataStream converter(datagram);

    s->count = count;
    s->length = length;

    s->value= new NuObsValue*[s->count];

    for(int i =0; i < s->count; i++){
        s->value[i]=new NuObsValue;
        s->value[i]=initNuObsValue(extractBytes(converter, sizeof(NuObsValue)));
    }
    return s;
}
*/
/*
MetricStructure * initMetricStructure(QByteArray datagram){
    MetricStructure * s =(MetricStructure *)malloc(sizeof(MetricStructure));
    QDataStream converter(datagram);
    converter >> s->ms_struct;
    converter >> s->ms_comp_no;
    return s;
}
*/
/*
MetricSpec * initMetricSpec(QByteArray datagram){
    MetricSpec * s =(MetricSpec *)malloc(sizeof(MetricSpec));
    QDataStream converter(datagram);
    converter >> s->update_period;
    converter >> s->category;
    converter >> s->access;
    s->structure = new MetricStructure;
    s->structure = initMetricStructure(extractBytes(converter, sizeof(MetricStructure)));
    converter >> s->relevance;
    return s;
}
*/
/*
SampleType * initSampleType(QByteArray datagram){
    SampleType * s =(SampleType *)malloc(sizeof(SampleType));
    QDataStream converter(datagram);
    converter >> s->sample_size;
    converter >> s->significant_bits;
    return s;
}
*/
/*
SaSpec * initSaSpec(QByteArray datagram){
    SaSpec * s =(SaSpec *)malloc(sizeof(SaSpec));
    QDataStream converter(datagram);
    converter >> s->array_size;
    s->sample_type = new SampleType;
    s->sample_type = initSampleType(extractBytes(converter, sizeof(SampleType)));
    converter >> s->flags;
    return s;
}
*/
/*
SaFixedValSpecEntry16 * initSaFixedValSpecEntry16(QByteArray datagram){
    SaFixedValSpecEntry16 * s =(SaFixedValSpecEntry16 *)malloc(sizeof(SaFixedValSpecEntry16));
    QDataStream converter(datagram);
    converter >> s->sa_fixed_val_id;
    converter >> s->sa_fixed_val;
    return s;
}
*/
/*
SaFixedValSpec16 * initSaFixedValSpec16(QByteArray datagram, quint16 count, quint16 length){
    SaFixedValSpec16 * s = (SaFixedValSpec16 *)malloc(sizeof(SaFixedValSpec16));
    QDataStream converter(datagram);
    s->count = count;
    s->length = length;

    s->value= new SaFixedValSpecEntry16*[s->count];

    for(int i =0; i < s->count; i++){
        s->value[i]=new SaFixedValSpecEntry16;
        s->value[i]=initSaFixedValSpecEntry16(extractBytes(converter, sizeof(SaFixedValSpecEntry16)));
    }
    return s;
}
*/
/*
ScaleRangeSpec16 * initScaleRangeSpec16(QByteArray datagram){
    ScaleRangeSpec16 * s =(ScaleRangeSpec16 *)malloc(sizeof(ScaleRangeSpec16));
    QDataStream converter(datagram);
    converter >> s->lower_absolute_value;
    converter >> s->upper_absolute_value;
    converter >> s->lower_scaled_value;
    converter >> s->upper_scaled_value;
    return s;
}
*/
/*
ScaledRange16 * initScaledRange16(QByteArray datagram){
    ScaledRange16 * s =(ScaledRange16 *)malloc(sizeof(ScaledRange16));
    QDataStream converter(datagram);
    converter >> s->lower_scaled_value;
    converter >> s->upper_scaled_value;
    return s;
}
*/
/*
SaObsValue * initSaObsValue(QByteArray datagram, OIDType phyID, MeasurementState st, quint16 length){
    SaObsValue * s =(SaObsValue *)malloc(sizeof(SaObsValue));
    QDataStream converter(datagram);
    s->physio_id = phyID;
    s->state = st;
    s->sampleArray.length = length;
    s->sampleArray.value = new quint8[s->sampleArray.length];
    for(int i=0; i<s->sampleArray.length; i++)
        converter >> s->sampleArray.value[i];
    return s;
}
*/
/*
SaObsValueCmp * initSaObsValueCmp(QByteArray datagram, quint16 count, quint16 length){
    SaObsValueCmp * s = (SaObsValueCmp *)malloc(sizeof(SaObsValueCmp));
    QDataStream converter(datagram);
    s->count = count;
    s->length = length;

    s->value= new SaObsValue*[s->count];

    OIDType phyID;
    MeasurementState st;
    quint16 tmpLength;

    for(int i =0; i < s->count; i++){
        converter >> phyID >> st >> tmpLength;
        s->value[i]=new SaObsValue;
        s->value[i]=initSaObsValue(extractBytes(converter, length), phyID, st, tmpLength);
    }
    return s;
}
*/
/*
ProtoSupportEntry * initProtoSupportEntry(QByteArray datagram){
    ProtoSupportEntry * s =(ProtoSupportEntry *)malloc(sizeof(ProtoSupportEntry));
    QDataStream converter(datagram);
    converter >> s->appl_proto;
    converter >> s->trans_proto;
    converter >> s->port_number;
    converter >> s->options;
    return s;
}
*/
/*
MACAddress * initMACAddress(QByteArray datagram){
    MACAddress * s = (MACAddress *)malloc(sizeof(MACAddress));
    QDataStream converter(datagram);

    for(int i=0;i<6;i++)
        converter >> s->value[i];
    return s;
}
*/
/*
IPAddress * initIPAddress(QByteArray datagram){
    IPAddress * s = (IPAddress *)malloc(sizeof(IPAddress));
    QDataStream converter(datagram);

    for(int i=0;i<4;i++)
        converter >> s->value[i];
    return s;
}
*/
/*
ProtoSupport * initProtoSupport(QByteArray datagram, quint16 count, quint16 length){
    ProtoSupport * s = (ProtoSupport *)malloc(sizeof(ProtoSupport));
    QDataStream converter(datagram);
    s->count = count;
    s->length = length;

    s->proto_support_entry= new ProtoSupportEntry*[s->count];

    for(int i =0; i < s->count; i++){
        s->proto_support_entry[i]=new ProtoSupportEntry;
        s->proto_support_entry[i]=initProtoSupportEntry(extractBytes(converter, sizeof(ProtoSupportEntry)));
    }
    return s;
}
*/
/*
IpAddressInfo * initIpAddressInfo(QByteArray datagram){
    IpAddressInfo * s = (IpAddressInfo *)malloc(sizeof(IpAddressInfo));
    QDataStream converter(datagram);

    s->mac_address = new MACAddress;
    s->ip_address = new IPAddress;
    s->subnet_mask = new IPAddress;

    s->mac_address = initMACAddress(extractBytes(converter, sizeof(MACAddress)));
    s->ip_address = initIPAddress(extractBytes(converter, sizeof(IPAddress)));
    s->subnet_mask = initIPAddress(extractBytes(converter, sizeof(IPAddress)));

    return s;
}
*/
/*
AVAType initAVAType(QByteArray datagram, OIDType id, quint16 length){
    AVAType s = (AVAType*)malloc(sizeof(AVAType));
    QDataStream converter(datagram);
    s->attribute_id = id;
    s->length = length;
    //converter >> s->attribute_id >> s->length;
    //qDebug() << s->length;
    quint16 tmpCount;
    quint16 tmpLength;
    quint8 byte;
    switch(s->attribute_id){
    case (NOM_ATTR_TIME_PD_POLL):
        qDebug() << "NOM_ATTR_TIME_PD_POLL";
        s->poll_data_req_period = new PollDataReqPeriod;
        s->poll_data_req_period=initPollDataReqPeriod(datagram);
        break;
    case(NOM_ATTR_POLL_OBJ_PRIO_NUM):
        qDebug() << "NOM_ATTR_POLL_OBJ_PRIO_NUM";
        converter >> s->number_of_prioritized_objects;
        //init u16
        break;
    case(NOM_POLL_PROFILE_SUPPORT):
        qDebug() << "NOM_POLL_PROFILE_SUPPORT";
        s->poll_profile_support = new PollProfileSupport;
        s->poll_profile_support = initPollProfileSupport(datagram);
        break;
    case(NOM_ATTR_POLL_PROFILE_EXT):
        qDebug() << "NOM_ATTR_POLL_PROFILE_EXT";
        s->poll_profile_ext = new PollProfileExt;
        s->poll_profile_ext = initPollProfileExt(datagram);
        break;
    case(NOM_ATTR_ID_HANDLE):
        qDebug() << "NOM_ATTR_ID_HANDLE";
        converter >> s->handle;// = initHandle(datagram);
        break;
    case(NOM_ATTR_ID_TYPE):
        qDebug() << "NOM_ATTR_ID_TYPE";
        s->type = new TYPE;
        s->type = initTYPE(datagram);
        break;
    case(NOM_ATTR_NU_VAL_OBS):
        qDebug() << "NOM_ATTR_NU_VAL_OBS";
        s->nu_obs_value = new NuObsValue;
        s->nu_obs_value = initNuObsValue(datagram);
        break;
    case(NOM_ATTR_NU_CMPD_VAL_OBS):
        qDebug() << "NOM_ATTR_NU_CMPD_VAL_OBS";
        converter >> tmpCount >> tmpLength;
        s->nu_obs_val_cmp = new NuObsValueCmp;
        s->nu_obs_val_cmp = initNuObsValueCmp(extractBytes(converter,tmpLength), tmpCount, tmpLength);
        break;
    case(NOM_ATTR_TIME_STAMP_ABS):
        qDebug() << "NOM_ATTR_TIME_STAMP_ABS";
        s->absolute_time = new AbsoluteTime;
        s->absolute_time = initAbsoluteTime(datagram);
        break;
    case(NOM_ATTR_TIME_STAMP_REL):
        qDebug() << "NOM_ATTR_TIME_STAMP_REL";
        converter >> s->relative_time;// = initRelativeTime(datagram);
        break;
    case(NOM_ATTR_ID_LABEL):
        qDebug() << "NOM_ATTR_ID_LABEL";
        converter >> s->text_id;// = initTextId(datagram);
        break;
    case(NOM_ATTR_ID_LABEL_STRING):
        qDebug() << "NOM_ATTR_ID_LABEL_STRING";
        converter >> tmpLength;
        s->string = new String;
        s->string = initString(extractBytes(converter,tmpLength), tmpLength);
        break;
    case(NOM_ATTR_COLOR):
        qDebug() << "NOM_ATTR_COLOR";
        converter >> s->simple_colour;// = initSimpleColour(datagram);
        break;
    case(NOM_ATTR_METRIC_SPECN):
        qDebug() << "NOM_ATTR_METRIC_SPECN";
        s->metric_spec = new MetricSpec;
        s->metric_spec = initMetricSpec(datagram);
        break;
    case(NOM_ATTR_SA_SPECN):
        qDebug() << "NOM_ATTR_SA_SPECN";
        s->sa_spec = new SaSpec;
        s->sa_spec = initSaSpec(datagram);
        break;
    case(NOM_ATTR_SA_FIXED_VAL_SPECN):
        qDebug() << "NOM_ATTR_SA_FIXED_VAL_SPECN";
        converter >> tmpCount >> tmpLength;
        s->sa_fixed_val_spec16 = new SaFixedValSpec16;
        s->sa_fixed_val_spec16 = initSaFixedValSpec16(extractBytes(converter,tmpLength), tmpCount, tmpLength);
        break;
    case(NOM_ATTR_TIME_PD_SAMP):
        qDebug() << "NOM_ATTR_TIME_PD_SAMP";
        converter >> s->relative_time;// = initRelativeTime(datagram);
        break;
    case(NOM_ATTR_METRIC_STAT):
        qDebug() << "NOM_ATTR_METRIC_STAT";
        converter >> s->metric_state;// = initMetricState(datagram);
        break;
    case(NOM_ATTR_UNIT_CODE):
        qDebug() << "NOM_ATTR_UNIT_CODE";
        converter >> s->oid_type;// = initOIDType(datagram);
        break;
    case(NOM_ATTR_MODE_MSMT):
        qDebug() << "NOM_ATTR_MODE_MSMT";
        converter >> s->measure_mode;// = initMeasureMode(datagram);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL):
        qDebug() << "NOM_ATTR_METRIC_INFO_LABEL";
        converter >> s->text_id;// = initTextId(datagram);
        break;
    case(NOM_ATTR_METRIC_INFO_LABEL_STR):
        qDebug() << "NOM_ATTR_METRIC_INFO_LABEL_STR";
        converter >> tmpLength;
        s->string = new String;
        s->string = initString(extractBytes(converter,tmpLength), tmpLength);
        break;
    case(NOM_ATTR_SCALE_SPECN_I16):
        qDebug() << "NOM_ATTR_SCALE_SPECN_I16";
        s->scale_range_spec16 = new ScaleRangeSpec16;
        s->scale_range_spec16= initScaleRangeSpec16(datagram);
        break;
    case(NOM_ATTR_SA_RANGE_PHYS_I16):
        qDebug() << "NOM_ATTR_SA_RANGE_PHYS_I16";
        s->scaled_range_16 = new ScaledRange16;
        s->scaled_range_16 = initScaledRange16(datagram);
        break;
    case(NOM_ATTR_SA_VAL_OBS):
        qDebug() << "NOM_ATTR_SA_VAL_OBS";
        OIDType phyID;
        MeasurementState st;
        quint16 l;
        converter >> phyID >> st >> l;
        s->sa_obs_value = new SaObsValue;
        s->sa_obs_value = initSaObsValue(extractBytes(converter,l), phyID, st, l);
        break;
    case(NOM_ATTR_SA_CMPD_VAL_OBS):
        qDebug() << "NOM_ATTR_SA_CMPD_VAL_OBS";
        converter >> tmpCount >> tmpLength;
        s->sa_obs_value_cmp = new SaObsValueCmp;
        s->sa_obs_value_cmp = initSaObsValueCmp(extractBytes(converter,tmpLength), tmpCount, tmpLength);
        break;
    case(NOM_ATTR_PCOL_SUPPORT):
        qDebug() << "NOM_ATTR_PCOL_SUPPORT";
        converter >> tmpCount >> tmpLength;
        s->proto_support = new ProtoSupport;
        s->proto_support = initProtoSupport(extractBytes(converter,tmpLength), tmpCount, tmpLength);
        break;
    case(NOM_ATTR_NET_ADDR_INFO):
        qDebug() << "NOM_ATTR_NET_ADDR_INFO";
        s->ip_address_info = new IpAddressInfo;
        s->ip_address_info = initIpAddressInfo(datagram);
        break;
    default:
        qDebug() << "DEFAULT";
        for(int i=0; i<s->length; i++)
            converter >> byte;
    }
    return s;
}
*/