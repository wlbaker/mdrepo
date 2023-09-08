/**
 * @file intellivue_error_response.cxx
 *
 * @brief Defines class which parses set responses from intellivue
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_set_response.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "intellivue.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueSetResponse::IntellivueSetResponse() { }

IntellivueSetResponse::~IntellivueSetResponse() { }

DicesRcPhilipsIntellivueMP70 IntellivueSetResponse::IsSetResponse(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueSetResponse::IsSetResponse() ";

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
  {
    return DicesRcPhilipsIntellivueMP70::OK;
  }

  int iindex = 10;
  if (ro_type == ROLRS_APDU) iindex += 2;

  uint16_t command_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  if ((int)command_type != (int)CMD_CONFIRMED_SET) return DicesRcPhilipsIntellivueMP70::OK;

  *is_msg = true;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueSetResponse::ParseSetResponse(
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueSetResponse::ParseSetResponse() ";
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
  intellivue::RORSapdu rorsapdu = { 0 };
  intellivue::ROLRSapdu rolrsapdu = { 0 };
  intellivue::SetResult setresult = { 0 };
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

  if ((numbytes - iindex) < roapdus.length)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Corrupt remote operation error. "
      "ROapdus length is greater than the number of bytes in the "
      "message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  switch (roapdus.ro_type)
  {
    case RORS_APDU:
    {
      // RORSapdu
      rorsapdu.invoke_id =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      rorsapdu.command_type =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;
      rorsapdu.length =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < rorsapdu.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt set result response. "
          "RORSapdu length is greater than the number of bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }
    }
      break;
    case ROLRS_APDU:
    {
      // ROLRSapdu
      rolrsapdu.linked_id.state = buffer[iindex];
      iindex++;
      rolrsapdu.linked_id.count = buffer[iindex];
      iindex++;
      rolrsapdu.invoke_id = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;
      rolrsapdu.command_type = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;
      rolrsapdu.length = ntohs(*(reinterpret_cast<uint16_t*>(
        &buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < rolrsapdu.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt set result response. "
          "ROLRSapdu length is greater than the number of bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }
    }
      break;
    default:
      LOG4CPLUS_WARN(root_logger, sfn << "Received unknown ROapdus ro_type ("
        << static_cast<int>(roapdus.ro_type) << ")");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      break;
  }

  // SetResult
  setresult.managed_object.m_obj_class =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  setresult.managed_object.m_obj_inst.context_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  setresult.managed_object.m_obj_inst.handle =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  setresult.attributeList.count =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  setresult.attributeList.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((numbytes - iindex) < setresult.attributeList.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt set result response. "
      "attribute list length is greater than the number of bytes in message.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  setresult.attributeList.value = new (std::nothrow) intellivue::AVAType[
    setresult.attributeList.count]();
  if (!setresult.attributeList.value)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
      "AVAType list");
    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
  }

  for (
    int ix = 0;
    ix < setresult.attributeList.count;
    ix++)
  {
    setresult.attributeList.value[ix].attribute_id =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;
    setresult.attributeList.value[ix].length =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    if ((numbytes - iindex) < setresult.attributeList.value[ix].length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt set result response. "
        "Attribute length is greater than the number of bytes in message.");
      delete [] setresult.attributeList.value;
      setresult.attributeList.value = nullptr;
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    bool is_valid = false;
    status = IntellivueUtils::IsValidSetResultAttribute(
      setresult.attributeList.value[ix].attribute_id,
      &is_valid);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      delete [] setresult.attributeList.value;
      setresult.attributeList.value = nullptr;
      return status;
    }
    if (is_valid)
    {
      status = IntellivueUtils::ParseAttribute(
        &setresult.attributeList.value[ix],
        buffer,
        iindex);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        delete [] setresult.attributeList.value;
        setresult.attributeList.value = nullptr;
        return status;
      }

      // We only set waveform priority list. Might as well just print it here.
      if (setresult.attributeList.value[ix].attribute_id
        == NOM_ATTR_POLL_RTSA_PRIO_LIST)
      {
        LOG4CPLUS_INFO(root_logger, sfn << "NOM_ATTR_POLL_RTSA_PRIO_LIST");
        intellivue::TextIdList* ptext_id_list =
          reinterpret_cast<intellivue::TextIdList *>(
          setresult.attributeList.value[ix].attribute_val);
        if (!ptext_id_list)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "to TextIdList. attribute_id: " << static_cast<int>(
            setresult.attributeList.value[ix].attribute_id));
        }
        else
        {
          LOG4CPLUS_INFO(root_logger, sfn << "count: " << ptext_id_list->count);
          for (int iy = 0; iy < ptext_id_list->count; iy++)
          {
            if (!ptext_id_list->value)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "TextId list is an null "
                "pointer. attribute_id: " << static_cast<int>(
                setresult.attributeList.value[ix].attribute_id));
              break;
            }
            LOG4CPLUS_INFO(root_logger, sfn << "TextId: "
              << ptext_id_list->value[iy]);
          }
        }
      }
      status = IntellivueUtils::DeleteAttribute(
        &setresult.attributeList.value[ix]);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn <<
          DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        delete [] setresult.attributeList.value;
        setresult.attributeList.value = nullptr;
        return status;
      }
    }

    iindex += setresult.attributeList.value[ix].length;
  }

  delete [] setresult.attributeList.value;
  setresult.attributeList.value = nullptr;

  return DicesRcPhilipsIntellivueMP70::OK;
}
