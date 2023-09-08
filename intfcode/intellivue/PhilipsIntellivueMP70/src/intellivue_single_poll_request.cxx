/**
 * @file intellivue_single_poll_request.cxx
 *
 * @brief Defines class which creates a single poll request
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

#include "intellivue_single_poll_request.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <climits>
#include <cstring>
#include <arpa/inet.h>
#include "intellivue.h"
#include "PhilipsIntellivueMP70ReturnCodes.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueSinglePollRequest::IntellivueSinglePollRequest() { }

IntellivueSinglePollRequest::~IntellivueSinglePollRequest() { }

DicesRcPhilipsIntellivueMP70 IntellivueSinglePollRequest::
CreateSinglePollRequest(
  uint8_t* single_poll_request_buffer,
  unsigned int size_of_buffer,
  unsigned int* size_of_request,
  SinglePollRequestType poll_type,
  uint16_t* poll_number)
{
  static const char* sfn = "IntellivueSinglePollRequest::"
    "CreateSinglePollRequest() ";
  if (!single_poll_request_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "single_poll_request_buffer is a null pointer");
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

  const int ksize_of_single_poll_req = 36;
  if (size_of_buffer < ksize_of_single_poll_req)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Single data poll request buffer "
      "length (" << size_of_buffer << ") is too small to contain request "
      "size (" << ksize_of_single_poll_req << ")");
    return DicesRcPhilipsIntellivueMP70::BUFFER_SIZE_TOO_SMALL;
  }

  static unsigned short poll_number_counter = 0;

  // Setting values to all structure in an single poll data request.

  intellivue::SPpdu sppdu = {
    0xE100, // session_id
    2 // p_context_id
  };

  // ROapdus
  intellivue::ROapdus roapdus = {
    ROIV_APDU, // ro_type
    28 // length
  };

  uint16_t invokeid = static_cast<int>(poll_type);

  // ROIVapdu
  intellivue::ROIVapdu roivapdu = {
    invokeid, // invoke_id (originally = 1?)
    CMD_CONFIRMED_ACTION, // command_type
    22 // length
  };

  // ActionArgument
  intellivue::ActionArgument action_argument = {
    NOM_MOC_VMS_MDS, // managed_object.m_obj_class
    0, // managed_object.m_obj_inst.context_id
    0, // managed_object.m_obj_inst.handle
    0, // scope
    NOM_ACT_POLL_MDIB_DATA, // action_type
    8 // length
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
    case SinglePollRequestType::SINGLE_MDS_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_VMS_MDS;
      poll_mdib_data_req.polled_attr_grp = 0; // all groups
      break;
    case SinglePollRequestType::SINGLE_PATIENT_DEMOGRAPHICS_REQUEST:
      poll_mdib_data_req.polled_obj_type.code = NOM_MOC_PT_DEMOG;
      poll_mdib_data_req.polled_attr_grp = 0; // all groups
      break;
    default:
      LOG4CPLUS_ERROR(root_logger, sfn << "Unknown SinglePollRequestType "
        "enumerator " << static_cast<int>(poll_type));
      return DicesRcPhilipsIntellivueMP70::UNKNOWN_SINGLE_POLL_REQUEST_TYPE;
      break;
  }

  uint16_t new_short = htons(sppdu.session_id);
  uint8_t* pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(sppdu.p_context_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roapdus.ro_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roapdus.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.invoke_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.command_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(roivapdu.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_class);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_inst.context_id);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.managed_object.m_obj_inst.handle);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  int new_int = htonl(static_cast<int>(action_argument.scope));
  uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_int,
    sizeof(new_int));
  *size_of_request += sizeof(new_int);

  new_short = htons(action_argument.action_type);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(action_argument.length);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.poll_number);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_obj_type.partition);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_obj_type.code);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  new_short = htons(poll_mdib_data_req.polled_attr_grp);
  pnew_short = reinterpret_cast<uint8_t*>(&new_short);

  memmove(
    &single_poll_request_buffer[*size_of_request],
    pnew_short,
    sizeof(new_short));
  *size_of_request += sizeof(new_short);

  return DicesRcPhilipsIntellivueMP70::OK;
}
