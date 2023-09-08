/**
 * @file intellivue_error_response.cxx
 *
 * @brief Defines class which parses error responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_error_response.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "intellivue.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueErrorResponse::IntellivueErrorResponse() { }

IntellivueErrorResponse::~IntellivueErrorResponse() { }

DicesRcPhilipsIntellivueMP70 IntellivueErrorResponse::
IsRemoteOperationErrorResponse(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueErrorResponse::"
    "IsRemoteOperationErrorResponse() ";

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

  if (numbytes < 6) return DicesRcPhilipsIntellivueMP70::OK;

  if (buffer[0] != 0xE1) return DicesRcPhilipsIntellivueMP70::OK;

  uint16_t ro_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[4])));
  if (ro_type != ROER_APDU) return DicesRcPhilipsIntellivueMP70::OK;

  *is_msg = true;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueErrorResponse::
ParseRemoteOperationErrorResponse(
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueErrorResponse::"
    "ParseRemoteOperationErrorResponse() ";
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (numbytes < 8)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse SPpdu and ROapdus "
      "because there are not enough bytes in buffer. numbytes: " << numbytes);
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  intellivue::SPpdu sppdu = { 0 };
  intellivue::ROapdus roapdus = { 0 };
  intellivue::ROERapdu roerapdu = { 0 };
  int iindex = 0;

  // SPpdu
  sppdu.session_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  sppdu.p_context_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  // ROapdus
  roapdus.ro_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  roapdus.length = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if (roapdus.ro_type != ROER_APDU)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse message which has "
      "unknown ROapdus ro_type (" << static_cast<int>(roapdus.ro_type)
      << "), expected ROER_APDU");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  if ((numbytes - iindex) < roapdus.length)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Corrupt remote operation error. "
      "ROapdus length is greater than the number of bytes in the "
      "message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // ROERapdu
  roerapdu.invoke_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  roerapdu.error_value = ntohs(*(reinterpret_cast<uint16_t*>(
    &buffer[iindex])));
  iindex += 2;
  roerapdu.length = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex) < roerapdu.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt remote operation error. "
      "ROERapdu length is greater than the number of bytes in the "
      "message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  std::stringstream ss;
  switch (roerapdu.error_value)
  {
    case NO_SUCH_OBJECT_CLASS:
    {
      intellivue::OIDType oid_type = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value "
        "NO_SUCH_OBJECT_CLASS. An OIDType with class ID ("
        << static_cast<int>(oid_type) << ") is attached";
    }
      break;
    case ACCESS_DENIED:
    {
      ss << "Received remote operation error with error value ACCESS_DENIED. "
        "No data is appended.";
    }
      break;
    case GET_LIST_ERROR:
    {
      intellivue::GetListError get_list_error = { 0 };
      get_list_error.managed_object.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      get_list_error.managed_object.m_obj_inst.context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      get_list_error.managed_object.m_obj_inst.handle = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      get_list_error.getInfoList.count = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;
      get_list_error.getInfoList.length = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value GET_LIST_ERROR. "
        "GetListError is appended. ManagedObjectId m_obj_class: "
        << static_cast<int>(get_list_error.managed_object.m_obj_class)
        << " m_obj_inst.context_id: " << static_cast<int>(get_list_error.
        managed_object.m_obj_inst.context_id) << " m_obj_inst.handle: "
        << static_cast<int>(get_list_error.managed_object.m_obj_inst.handle)
        << " getInfoList count: " << static_cast<int>(get_list_error.
        getInfoList.count) << " length: " << static_cast<int>(get_list_error.
        getInfoList.length);

      if ((numbytes - iindex) < get_list_error.getInfoList.length)
      {
        // Log a piece of the error
        LOG4CPLUS_WARN(root_logger, sfn << ss.str());
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt remote operation error. "
          "getInfoList length is greater than the number of bytes in the "
          "message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      for (int ix = 0; ix < get_list_error.getInfoList.count; ix++)
      {
        intellivue::ErrorStatus err_status = ntohs(
          *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;
        intellivue::OIDType attr_id = ntohs(
          *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;

        ss << " GetError errorStatus: " << static_cast<int>(err_status)
          << " attributeId: " << static_cast<int>(attr_id);
      }
    }
      break;
    case SET_LIST_ERROR:
    {
      intellivue::SetListError set_list_error = { 0 };
      set_list_error.managed_object.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      set_list_error.managed_object.m_obj_inst.context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      set_list_error.managed_object.m_obj_inst.handle = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      set_list_error.setInfoList.count = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;
      set_list_error.setInfoList.length = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value SET_LIST_ERROR. "
        "SetListError is appended. ManagedObjectId m_obj_class: "
        << static_cast<int>(set_list_error.managed_object.m_obj_class)
        << " m_obj_inst.context_id: " << static_cast<int>(set_list_error.
        managed_object.m_obj_inst.context_id) << " m_obj_inst.handle: "
        << static_cast<int>(set_list_error.managed_object.m_obj_inst.handle)
        << " setInfoList count: " << static_cast<int>(set_list_error.
        setInfoList.count) << " length: " << static_cast<int>(set_list_error.
        setInfoList.length);

      if ((numbytes - iindex) < set_list_error.setInfoList.length)
      {
        // Log a piece of the error
        LOG4CPLUS_WARN(root_logger, sfn << ss.str());
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt remote operation error. "
          "setInfoList length is greater than the number of bytes in the "
          "message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      for (int ix = 0; ix < set_list_error.setInfoList.count; ix++)
      {
        intellivue::ErrorStatus err_status = ntohs(
          *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;
        intellivue::ModifyOperator modify_operator = ntohs(
          *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;
        intellivue::OIDType attr_id = ntohs(
          *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;

        ss << " SetError errorStatus: " << static_cast<int>(err_status)
          << " modifyOperator: " << static_cast<int>(modify_operator)
          << " attributeId: " << static_cast<int>(attr_id);
      }
    }
      break;
    case PROCESSING_FAILURE:
    {
      intellivue::ProcessingFailure proc_fail = { 0 };

      proc_fail.error_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      proc_fail.length = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value "
        "PROCESSING_FAILURE. ProcessingFailure is appended. error_id: "
        << static_cast<int>(proc_fail.error_id) << " length: "
        << static_cast<int>(proc_fail.length);

      if ((numbytes - iindex) < proc_fail.length)
      {
        // Log a piece of the error
        LOG4CPLUS_WARN(root_logger, sfn << ss.str());
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt remote operation error. "
          "ProcessingFailure length is greater than the number of bytes in the "
          "message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      std::string appended_data;
      for (int ix = 0; ix < proc_fail.length; ix++)
      {
        appended_data += static_cast<char>(buffer[iindex]);
        iindex++;
      }
      ss << " Appended data: " << appended_data;
    }
      break;
    case NO_SUCH_ACTION:
    {
      intellivue::OIDType obj_class_id = 0;
      intellivue::OIDType action_type = 0;

      obj_class_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      action_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value NO_SUCH_ACTION. "
        "Object class id and action type appended. obj class id: "
        << static_cast<int>(obj_class_id) << " action type: "
        << static_cast<int>(action_type);
    }
      break;
    case INVALID_ARGUMENT_VALUE:
    {
      intellivue::ActionResult action_result = { 0 };

      action_result.managed_object.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      action_result.managed_object.m_obj_inst.context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      action_result.managed_object.m_obj_inst.handle = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      action_result.action_type = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      action_result.length = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value "
        "INVALID_ARGUMENT_VALUE. ActionResult is appended. ManagedObjectId "
        "m_obj_class: " << static_cast<int>(action_result.managed_object.
        m_obj_class) << " m_obj_inst.context_id: " << static_cast<int>(
        action_result.managed_object.m_obj_inst.context_id)
        << " m_obj_inst.handle: " << static_cast<int>(action_result.
        managed_object.m_obj_inst.handle) << " action_type: "
        << static_cast<int>(action_result.action_type) << " length: "
        << static_cast<int>(action_result.length);

      if ((numbytes - iindex) < action_result.length)
      {
        // Log a piece of the error
        LOG4CPLUS_WARN(root_logger, sfn << ss.str());
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt remote operation error. "
          "ActionResult length is greater than the number of bytes in "
          "the message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }
    }
      break;
    case INVALID_SCOPE:
    {
      uint32_t scope = ntohl(*(reinterpret_cast<uint32_t*>(&buffer[iindex])));
      iindex += 4;

      ss << "Received remote operation error with error value INVALID_SCOPE. "
        "scope is appended. scope: " << static_cast<int>(scope);
    }
      break;
    case NO_SUCH_OBJECT_INSTANCE:
    {
      intellivue::ManagedObjectId managed_obj_id = { 0 };

      managed_obj_id.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      managed_obj_id.m_obj_inst.context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      managed_obj_id.m_obj_inst.handle = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with "
        "error value NO_SUCH_OBJECT_INSTANCE. ManagedObjectId is appended. "
        "m_obj_class: " << static_cast<int>(managed_obj_id.m_obj_class)
        << " m_obj_inst.context_id: " << static_cast<int>(
        managed_obj_id.m_obj_inst.context_id) << " m_obj_inst.handle: "
        << static_cast<int>(managed_obj_id.m_obj_inst.handle);
    }
      break;
    case INVALID_OBJECT_INSTANCE:
    {
      intellivue::ManagedObjectId managed_obj_id = { 0 };

      managed_obj_id.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      managed_obj_id.m_obj_inst.context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      managed_obj_id.m_obj_inst.handle = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      ss << "Received remote operation error with error value "
        "INVALID_OBJECT_INSTANCE. ManagedObjectId is appended. m_obj_class: "
        << static_cast<int>(managed_obj_id.m_obj_class)
        << " m_obj_inst.context_id: " << static_cast<int>(managed_obj_id.
        m_obj_inst.context_id) << " m_obj_inst.handle: " << static_cast<int>(
        managed_obj_id.m_obj_inst.handle);
    }
      break;
    default:
      ss << "Received remote operation error with unknown error value ("
        << static_cast<int>(roerapdu.error_value) << ")";
      break;
  }
  LOG4CPLUS_WARN(root_logger, sfn << ss.str());

  return DicesRcPhilipsIntellivueMP70::OK;
}
