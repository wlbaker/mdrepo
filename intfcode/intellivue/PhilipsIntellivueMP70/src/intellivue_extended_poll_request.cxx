/**
 * @file intellivue_extended_poll_request.cxx
 *
 * @brief Defines class which creates extended poll request
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author M Szwaja
 */
//=============================================================================

#include "intellivue_extended_poll_request.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <climits>
#include "intellivue_utils.h"
#include "ini_parser.h"
#include "ini_association_request_parser.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueExtendedPollRequest::IntellivueExtendedPollRequest() { }

IntellivueExtendedPollRequest::~IntellivueExtendedPollRequest() { }

DicesRcPhilipsIntellivueMP70 IntellivueExtendedPollRequest::
CreateExtendedPollRequest(
  uint8_t* ext_poll_request_buffer,
  unsigned int size_of_buffer,
  unsigned int* size_of_request,
  ExtendedPollRequestType poll_type,
  unsigned int poll_period,
  uint16_t* poll_number)
{
  static const char* sfn = "IntellivueExtendedPollRequest::"
    "CreateExtendedPollRequest() ";
  if (!ext_poll_request_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "ext_poll_request_buffer is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!size_of_request)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument size_of_request is "
      "a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *size_of_request = 0;

  if (!poll_number)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument poll_number is "
      "a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *poll_number = 0;

  static unsigned short poll_number_counter = 0;

  const int ksize_of_ext_poll_req = 54;
  if (size_of_buffer < ksize_of_ext_poll_req)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Extended data poll request buffer "
      "length (" << size_of_buffer << ") is too small to contain request "
      "size (" << ksize_of_ext_poll_req << ")");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  // Setting values to all structure in an extended poll data request.

  intellivue::SPpdu sppdu = {
    0xE100, // session_id
    2 // p_context_id
  };

  // ROapdus
  intellivue::ROapdus roapdus = {
    ROIV_APDU, // ro_type
    46 // length
  };

  uint16_t invokeid = static_cast<int>(poll_type);

  // ROIVapdu
  intellivue::ROIVapdu roivapdu = {
    invokeid, // invoke_id (originally = 1?)
    CMD_CONFIRMED_ACTION, // command_type
    40 // length
  };

  // ActionArgument
  intellivue::ActionArgument action_argument = {
    NOM_MOC_VMS_MDS, // managed_object.m_obj_class
    0, // managed_object.m_obj_inst.context_id
    0, // managed_object.m_obj_inst.handle
    0, // scope
    NOM_ACT_POLL_MDIB_DATA_EXT, // action_type
    26 // length
  };

  // avoid unsigned short overflow
  if (poll_number_counter == USHRT_MAX) poll_number_counter = 0;
  *poll_number = poll_number_counter;

  // PollMdibDataReq
  intellivue::PollMdibDataReq poll_mdib_data_req = { 0 };
  poll_mdib_data_req.poll_number = poll_number_counter++;
  poll_mdib_data_req.polled_obj_type.partition = NOM_PART_OBJ;

  switch (poll_type)
  {
    case ExtendedPollRequestType::EXTENDED_ALARM_STATIC_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_AL_MON;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_STATIC;
      break;
    case ExtendedPollRequestType::EXTENDED_ALARM_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_AL_MON;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_AL_MON;
      break;
    case ExtendedPollRequestType::EXTENDED_NUMERIC_STATIC_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_NU;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_STATIC;
      break;
    case ExtendedPollRequestType::EXTENDED_NUMERIC_DYNAMIC_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_NU;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_DYN;
      break;
    case ExtendedPollRequestType::EXTENDED_NUMERIC_ALL_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_NU;
      poll_mdib_data_req.polled_attr_grp = 0; // all groups
      break;
    case ExtendedPollRequestType::EXTENDED_WAVEFORM_STATIC_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_SA_RT;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_STATIC;
      break;
    case ExtendedPollRequestType::EXTENDED_WAVEFORM_DYNAMIC_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_SA_RT;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_DYN;
      break;
    case ExtendedPollRequestType::EXTENDED_WAVEFORM_ALL_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_SA_RT;
      poll_mdib_data_req.polled_attr_grp = 0; // all groups
      break;
    case ExtendedPollRequestType::EXTENDED_ENUM_STATIC_REQUEST:
      // TODO: Note that NOM_MOC_VMO_METRIC_ENUM is not listed as a supported
      // object in the manual (IntellivueDataExportInterfaceProgrammingGuide
      // _Rel_H.0_2013.pdf) and I'm not sure if this request will work.
      // Also the value NOM_MOC_VMO_METRIC_ENUM was taken from an older
      // manual (IntelliVue_m8000-9305c_Data_Export_Interface_Programming_
      // Guide.pdf) because it no longer exists in most recent manual.
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_ENUM;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_STATIC;
      break;
    case ExtendedPollRequestType::EXTENDED_ENUM_DYNAMIC_REQUEST:
      // TODO: Note that NOM_MOC_VMO_METRIC_ENUM is not listed as a supported
      // object in the manual (IntellivueDataExportInterfaceProgrammingGuide
      // _Rel_H.0_2013.pdf) and I'm not sure if this request will work.
      // Also the value NOM_MOC_VMO_METRIC_ENUM was taken from an older
      // manual (IntelliVue_m8000-9305c_Data_Export_Interface_Programming_
      // Guide.pdf) because it no longer exists in most recent manual.
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_ENUM;
      poll_mdib_data_req.polled_attr_grp = NOM_ATTR_GRP_VMO_DYN;
      break;
    case ExtendedPollRequestType::EXTENDED_ENUM_ALL_REQUEST:
      // TODO: Note that NOM_MOC_VMO_METRIC_ENUM is not listed as a supported
      // object in the manual (IntellivueDataExportInterfaceProgrammingGuide
      // _Rel_H.0_2013.pdf) and I'm not sure if this request will work.
      // Also the value NOM_MOC_VMO_METRIC_ENUM was taken from an older
      // manual (IntelliVue_m8000-9305c_Data_Export_Interface_Programming_
      // Guide.pdf) because it no longer exists in most recent manual.
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMO_METRIC_ENUM;
      poll_mdib_data_req.polled_attr_grp = 0; // all groups
      break;
    default:
      LOG4CPLUS_ERROR(root_logger, sfn << "Unknown ExtendedPollRequestType "
        "enumerator " << static_cast<int>(poll_type));
      return DicesRcPhilipsIntellivueMP70::UNKNOWN_EXTENDED_POLL_REQUEST_TYPE;
      break;
  }

  uint8_t attl [] = { 0x00, 0x02, // count = 2
    0x00, 0x0E, // length = 14
    0xF1, 0x3E, // NOM_ATTR_TIME_PD_POLL
    0x00, 0x04, // length of att = 4
    0x00, 0x08, 0x00, 0x00, // time
    0xF2, 0x28, // NOM_ATTR_POLL_OBJ_PRIO_NUM
    0x00, 0x02, // length of att = 2
    0xFF, 0xFF };

  uint16_t new_short = htons(sppdu.session_id);
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(sppdu.p_context_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roapdus.ro_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roapdus.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.invoke_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.command_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_class);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_inst.context_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_inst.handle);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  int new_int = htonl(static_cast<int>(action_argument.scope));
  uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_short = htons(action_argument.action_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.poll_number);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_obj_type.partition);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_obj_type.code);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_attr_grp);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  // TODO Does 0 work?
  new_int = htonl(static_cast<int>(poll_period));
  pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(&attl[8], pnew_int, sizeof(new_int));

  memmove(
    &ext_poll_request_buffer[*size_of_request],
    attl,
    sizeof(attl));
  *size_of_request += sizeof(attl);

  return DicesRcPhilipsIntellivueMP70::OK;
}
