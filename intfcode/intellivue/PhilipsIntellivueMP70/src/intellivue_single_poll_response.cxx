/**
 * @file intellivue_single_poll_response.cxx
 *
 * @brief Defines class which parses single poll responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_single_poll_response.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "intellivue.h"
#include "dd_philips_intellivue_mp70_parser.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueSinglePollResponse::IntellivueSinglePollResponse() { }

IntellivueSinglePollResponse::~IntellivueSinglePollResponse() { }

DicesRcPhilipsIntellivueMP70 IntellivueSinglePollResponse::
IsSinglePollResponse(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueSinglePollResponse::"
    "IsSinglePollResponse() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  if (!is_msg)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument is_msg is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  *is_msg = false;

  if (numbytes < 21) return DicesRcPhilipsIntellivueMP70::OK;

  if (buffer[0] != 0xE1) return DicesRcPhilipsIntellivueMP70::OK;

  uint16_t ro_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[4])));

  if (ro_type != RORS_APDU && ro_type != ROLRS_APDU)
    return DicesRcPhilipsIntellivueMP70::OK;

  int iindex = 10;
  if (ro_type == ROLRS_APDU) iindex += 2;

  uint16_t command_type = ntohs(*(reinterpret_cast<uint16_t*>(
    &buffer[iindex])));

  if (command_type != CMD_CONFIRMED_ACTION)
    return DicesRcPhilipsIntellivueMP70::OK;

  iindex += 10;

  uint16_t action_type = ntohs(*(reinterpret_cast<uint16_t*>(
    &buffer[iindex])));

  if (action_type != NOM_ACT_POLL_MDIB_DATA)
    return DicesRcPhilipsIntellivueMP70::OK;

  *is_msg = true;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueSinglePollResponse::
ParseSinglePollResponse(
  SinglePollResponse* single_poll_response,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueSinglePollResponse::"
    "ParseSinglePollResponse() ";

  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  if (!single_poll_response)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "single_poll_response is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (numbytes < (sizeof(intellivue::SPpdu) + sizeof(intellivue::ROapdus)))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to parse SPpdu and ROapdus "
      "from response.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  int iindex = 0;

  // SPpdu
  single_poll_response->sppdu.session_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->sppdu.p_context_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  // ROapdus
  single_poll_response->roapdus.ro_type =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->roapdus.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex) < single_poll_response->roapdus.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
      "response. ROapdus length is greater than the "
      "number of bytes in message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  switch (single_poll_response->roapdus.ro_type)
  {
    case RORS_APDU:
    {
      // RORSapdu
      single_poll_response->rorsapdu.invoke_id =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      single_poll_response->rorsapdu.command_type =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      single_poll_response->rorsapdu.length =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < single_poll_response->rorsapdu.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
          "response. RORSapdu length is greater than the "
          "number of bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }
    }
      break;
    case ROLRS_APDU:
    {
      // ROLRSapdu
      single_poll_response->rolrs.linked_id.state = buffer[iindex];
      iindex++;
      single_poll_response->rolrs.linked_id.count = buffer[iindex];
      iindex++;

      single_poll_response->rolrs.invoke_id =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      single_poll_response->rolrs.command_type =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      single_poll_response->rolrs.length =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < single_poll_response->rolrs.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
          "response. RORSapdu length is greater than the "
          "number of bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }
    }
      break;
  }

  // ActionResult
  single_poll_response->actionresult.managed_object.m_obj_class =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->actionresult.managed_object.m_obj_inst.context_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->actionresult.managed_object.m_obj_inst.handle =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->actionresult.action_type =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->actionresult.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex) < single_poll_response->actionresult.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
      "response. ActionResult length is greater than the "
      "number of bytes in message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // PollMdibDataReply
  single_poll_response->pollReply.poll_number =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->pollReply.rel_time_stamp =
    ntohl(*(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // Absolute time stamp
  single_poll_response->pollReply.abs_time_stamp.century = buffer[iindex];
  single_poll_response->pollReply.abs_time_stamp.year = buffer[iindex + 1];
  single_poll_response->pollReply.abs_time_stamp.month = buffer[iindex + 2];
  single_poll_response->pollReply.abs_time_stamp.day = buffer[iindex + 3];
  single_poll_response->pollReply.abs_time_stamp.hour = buffer[iindex + 4];
  single_poll_response->pollReply.abs_time_stamp.minute = buffer[iindex + 5];
  single_poll_response->pollReply.abs_time_stamp.second = buffer[iindex + 6];
  single_poll_response->pollReply.abs_time_stamp.sec_fractions = buffer[iindex + 7];
  iindex += 8;

  // Type
  single_poll_response->pollReply.polled_obj_type.partition =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->pollReply.polled_obj_type.code =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->pollReply.polled_attr_grp =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->pollReply.poll_info_list.count =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  single_poll_response->pollReply.poll_info_list.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex)
    < single_poll_response->pollReply.poll_info_list.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
      "response. PollInfoList length is greater than the "
      "number of bytes in message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  single_poll_response->pollReply.poll_info_list.value =
    new (std::nothrow) intellivue::SingleContextPoll[
    single_poll_response->pollReply.poll_info_list.count]();
  if (!single_poll_response->pollReply.poll_info_list.value)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
      "SingleContextPoll list");
    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
  }

  for (
    int ix = 0;
    ix < single_poll_response->pollReply.poll_info_list.count;
    ix++)
  {
    single_poll_response->pollReply.poll_info_list.value[ix].context_id =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    single_poll_response->pollReply.poll_info_list.value[ix].poll_info.count =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    single_poll_response->pollReply.poll_info_list.value[ix].poll_info.length =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    if ((numbytes - iindex)
      < single_poll_response->pollReply.poll_info_list.value[ix].
      poll_info.length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
        "response. PollInfo length is greater than the "
        "number of bytes in message.");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    single_poll_response->pollReply.poll_info_list.value[ix].poll_info.value =
      new (std::nothrow) intellivue::ObservationPoll[
      single_poll_response->pollReply.poll_info_list.value[ix].poll_info.count]();
    if (!single_poll_response->pollReply.poll_info_list.value[ix].poll_info.value)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
        "ObservationPoll list");
      return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
    }

    for (
      int iy = 0;
      iy < single_poll_response->pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      single_poll_response->pollReply.poll_info_list.value[ix].poll_info.
        value[iy].obj_handle = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      single_poll_response->pollReply.poll_info_list.value[ix].poll_info.
        value[iy].attributes.count = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      single_poll_response->pollReply.poll_info_list.value[ix].poll_info.
        value[iy].attributes.length = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex)
        < single_poll_response->pollReply.poll_info_list.value[ix].poll_info.
        value[iy].attributes.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
          "response. AttributeList length is greater than the "
          "number of bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.value =
        new (std::nothrow) intellivue::AVAType[
        single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count]();
      if (!single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.value)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
          "AVAType list");
        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
      }

      for (
        int iz = 0;
        iz < single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz].attribute_id =
          ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;
        single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz].length =
          ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;

        if ((numbytes - iindex)
          < single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz].length)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt single data poll "
            "response. Attribute length is greater than the "
            "number of bytes in message.");
          return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
        }

        bool is_valid = false;
        status = IntellivueUtils::IsValidAttribute(
          single_poll_response->pollReply.polled_obj_type.code,
          single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz].attribute_id,
          &is_valid);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }
        if (is_valid)
        {
          status = IntellivueUtils::ParseAttribute(
            &single_poll_response->pollReply.poll_info_list.value[ix].
            poll_info.value[iy].attributes.value[iz],
            buffer,
            iindex);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }
        }
        iindex += single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz].length;
      }
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueSinglePollResponse::
DeleteSinglePollResponse(
  SinglePollResponse* single_poll_response)
{
  static const char* sfn = "IntellivueSinglePollResponse::"
    "DeleteSinglePollResponse() ";
  if (!single_poll_response)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "single_poll_response is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  for (
    int ix = 0;
    ix < single_poll_response->pollReply.poll_info_list.count;
    ix++)
  {
    if (!single_poll_response->pollReply.poll_info_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "SingleContextPoll list is a null "
        "pointer.");
      break;
    }
    for (
      int iy = 0;
      iy < single_poll_response->pollReply.poll_info_list.value[ix].
      poll_info.count;
      iy++)
    {
      if (!single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value)
      {
        LOG4CPLUS_WARN(root_logger, sfn << "ObservationPoll list is a null "
          "pointer.");
        break;
      }
      for (
        int iz = 0;
        iz < single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.count;
        iz++)
      {
        if (!single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "AVAType list is a null "
            "pointer.");
          break;
        }
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::DeleteAttribute(
          &single_poll_response->pollReply.poll_info_list.value[ix].
          poll_info.value[iy].attributes.value[iz]);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }
      }
      delete [] single_poll_response->pollReply.poll_info_list.value[ix].
        poll_info.value[iy].attributes.value;
      single_poll_response->pollReply.poll_info_list.value[ix].poll_info.
        value[iy].attributes.value = nullptr;
    }
    delete [] single_poll_response->pollReply.poll_info_list.value[ix].
      poll_info.value;
    single_poll_response->pollReply.poll_info_list.value[ix].poll_info.value =
      nullptr;
  }
  delete [] single_poll_response->pollReply.poll_info_list.value;
  single_poll_response->pollReply.poll_info_list.value = nullptr;

  return DicesRcPhilipsIntellivueMP70::OK;
}
