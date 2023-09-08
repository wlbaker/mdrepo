/**
 * @file intellivue_connect_indication_message.cxx
 *
 * @brief Defines a class which parses connect indication message from
 * intellivue.
 *
 * @author M Szwaja
 */
//=============================================================================
#include "intellivue_connect_indication_message.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "intellivue.h"
#include "mds.h"
#include "dices_rc_driver.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

IntellivueConnectIndicationMessage::IntellivueConnectIndicationMessage() { }

IntellivueConnectIndicationMessage::~IntellivueConnectIndicationMessage() { }

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::IsConnectIndicationMessage(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "IsConnectIndicationMessage() ";

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

  if (numbytes < 1) return DicesRcPhilipsIntellivueMP70::OK;

  switch (buffer[0])
  {
    case 0xE1: return DicesRcPhilipsIntellivueMP70::OK;
      break; // Data Export Command Protocol
    case CN_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break; // Association Response types
    case AC_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break;
    case RF_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break;
    case FN_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break;
    case DN_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break;
    case AB_SPDU_SI: return DicesRcPhilipsIntellivueMP70::OK;
      break;
    default:
      *is_msg = true;
      break;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::
ParseConnectIndicationMessage(
  ConnectIndication* connect_indication,
  uint8_t* buffer,
  unsigned int length)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "ParseConnectIndicationMessage() ";

  if (!connect_indication)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "connect_indication is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (length < (sizeof(intellivue::Nomenclature) +
    sizeof(intellivue::ROapdus)))
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Failed to parse Nomenclature and "
      "ROapdus because there are not enough bytes in buffer. length: "
      << length);
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  uint8_t nom[4] = { 0 };
  int iindex = 0;

  // Nomenclature
  connect_indication->nomenclature =
    ntohl(*(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;

  // Convert nomenclature into four byte array
  int new_int = htonl(static_cast<int>(connect_indication->nomenclature));
  uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
  memmove(&nom[0], pnew_int, sizeof(new_int));

  // ROapdus
  connect_indication->roapdus.ro_type =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->roapdus.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((length - iindex) < connect_indication->roapdus.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt connect indication message. "
      "ROapdus length is greater than message length");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }
  if ((length - iindex) < sizeof(intellivue::ROIVapdu))
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Failed to parse ROIVapdu ("
                    << sizeof(intellivue::ROIVapdu)
                    << " bytes) because there are not enough bytes left in buffer ("
                    << (length - iindex) << " bytes)");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // ROIVapdu
  connect_indication->roivapdu.invoke_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->roivapdu.command_type =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->roivapdu.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((length - iindex) < connect_indication->roivapdu.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt connect indication message. "
      "ROIVapdu length is greater than message length");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }
  if ((length - iindex) < sizeof(intellivue::EventReportArgument))
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Failed to parse EventReportArgument ("
                    << sizeof(intellivue::EventReportArgument)
                    << " bytes) because there are not enough bytes left in buffer ("
                    << (length - iindex) << " bytes)");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // EventReportArgument
  connect_indication->eventreparg.managed_object.m_obj_class =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->eventreparg.managed_object.m_obj_inst.context_id =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->eventreparg.managed_object.m_obj_inst.handle =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->eventreparg.event_time =
    ntohl(*(reinterpret_cast<uint32_t*>(&buffer[iindex])));
  iindex += 4;
  connect_indication->eventreparg.event_type =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->eventreparg.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((length - iindex) < connect_indication->eventreparg.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt connect indication message. "
      "EventReportArgument length is greater than message length");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }
  const int kconnect_ind_info_count_and_len_bytes =
      sizeof(intellivue::ConnectIndInfo::count)
      + sizeof(intellivue::ConnectIndInfo::length);
  if ((length - iindex) < kconnect_ind_info_count_and_len_bytes)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
                    << "Failed to parse ConnectIndInfo count and length ("
                    << kconnect_ind_info_count_and_len_bytes
                    << " bytes) because there are not enough bytes left in buffer ("
                    << (length - iindex) << " bytes)");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  // ConnectIndInfo
  // Attribute list
  connect_indication->conninfo.count =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;
  connect_indication->conninfo.length =
    ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
  iindex += 2;

  if ((length - iindex) < connect_indication->conninfo.length)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt connect indication message. "
      "ConnectIndInfo length is greater than message length");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  connect_indication->conninfo.value = new (std::nothrow) intellivue::AVAType[
    connect_indication->conninfo.count]();
  if (!connect_indication->conninfo.value)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory for "
      "ConnectIndInfo AVAType list.");
    return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
  }

  const int kava_type_id_and_len_bytes =
      sizeof(intellivue::AVAType::attribute_id)
      + sizeof(intellivue::AVAType::length);

  for (int ix = 0; ix < connect_indication->conninfo.count; ix++)
  {
    if ((length - iindex) < kava_type_id_and_len_bytes)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
                      << "Failed to parse ConnectIndInfo AVAType attribute_id and length ("
                      << kava_type_id_and_len_bytes
                      << " bytes) because there are not enough bytes left in buffer ("
                      << (length - iindex) << " bytes)");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    connect_indication->conninfo.value[ix].attribute_id =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;
    connect_indication->conninfo.value[ix].length =
      ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
    iindex += 2;

    if ((length - iindex) < connect_indication->conninfo.value[ix].length)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt connect indication "
        "message. ConnectIndInfo attribute length is greater than message "
        "length");
      return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
    }

    bool is_valid = false;
    DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
      IsValidConnectIndicationAttribute(
      connect_indication->conninfo.value[ix].attribute_id,
      &is_valid);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed on IntellivueUtils::"
        "IsValidConnectIndicationAttribute(). "
        << DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
    if (is_valid)
    {
      status = IntellivueUtils::ParseAttribute(
        &connect_indication->conninfo.value[ix],
        buffer,
        iindex);
      if (status != DicesRcPhilipsIntellivueMP70::OK)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed on IntellivueUtils::"
          "ParseAttribute(). "
          << DicesRcPhilipsIntellivueMP70StatusMessage::
          DicesRcPhilipsIntellivueMP70ToString(status));
        return status;
      }
    }

    iindex += connect_indication->conninfo.value[ix].length;
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::
DeleteConnectIndicationMessage(
  ConnectIndication* connect_indication)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "DeleteConnectIndicationMessage() ";
  if (!connect_indication)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "connect_indication is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  for (int ix = 0; ix < connect_indication->conninfo.count; ix++)
  {
    if (!connect_indication->conninfo.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "ConnectIndInfo AVAType list is a "
        "null pointer");
      break;
    }

    DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::DeleteAttribute(
      &connect_indication->conninfo.value[ix]);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << "Failed on IntellivueUtils::"
        "DeleteAttribute(). "
        << DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  delete [] connect_indication->conninfo.value;
  connect_indication->conninfo.value = nullptr;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::
SetMDSWithConnectIndicationMessage(
  std::pair<DicesRcDriver, ice::MDS*>* instance_pair,
  const ConnectIndication& connect_indication)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "SetMDSWithConnectIndicationMessage() ";

  if (!instance_pair)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "instance_pair is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!instance_pair->second)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "ice::MDS in instance_pair is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  for (int ix = 0; ix < connect_indication.conninfo.count; ix++)
  {
    if (!connect_indication.conninfo.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "ConnectIndInfo AVAType list is a "
        "null pointer");
      break;
    }

    intellivue::OIDType attribute_id = connect_indication.conninfo.value[ix].
      attribute_id;
    switch (attribute_id)
    {
      case NOM_ATTR_SYS_TYPE:
      {
        intellivue::TYPE* ptype = reinterpret_cast<intellivue::TYPE*>(
          connect_indication.conninfo.value[ix].attribute_val);
        if (!ptype)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
            "attribute_val into TYPE. attribute_id: "
            << static_cast<int>(attribute_id));
          break;
        }

        ice::NomPartition dices_partition = ice::nom_part_unspec;
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
          ConvertIntellivueNomPartitionToDicesNomPartition(
          &dices_partition,
          ptype->partition);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Failed on IntellivueUtils::"
            "ConvertIntellivueNomPartitionToDicesNomPartition(). "
            << DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }

        if (instance_pair->second->system_type.partition != dices_partition)
        {
          instance_pair->second->system_type.partition = dices_partition;
          instance_pair->first = DicesRcDriver::OK;
        }
        if (instance_pair->second->system_type.code != ptype->code)
        {
          instance_pair->second->system_type.code = ptype->code;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
      case NOM_ATTR_ID_PROD_SPECN:
      {
        intellivue::ProductionSpec* ppspec =
          reinterpret_cast<intellivue::ProductionSpec*>(
          connect_indication.conninfo.value[ix].attribute_val);
        if (!ppspec)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast "
            "attribute_val into ProductionSpec. attribute_id: "
            << static_cast<int>(attribute_id));
          break;
        }

        if (!ppspec->value)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Unable to parse ProdSpecEntry "
            "list, because there is no memory allocated for value. "
            "attribute_id: " << static_cast<int>(attribute_id));
          break;
        }

        int new_count = ppspec->count;
        if (ppspec->count > instance_pair->second->production_specification.
          maximum())
        {
          LOG4CPLUS_WARN(root_logger, sfn << "The count of ProdSpecEntry "
            "from intellivue (" << static_cast<int>(ppspec->count) << ") "
            "exceeds the maximum DDS sequence size for ice::ProductionSpec "
            "( " << instance_pair->second->production_specification.
            maximum() << ")");
          // Set count to maximum so we can still continue parsing.
          new_count = instance_pair->second->production_specification.
            maximum();
        }
        if (instance_pair->second->production_specification.length()
          != new_count)
        {
          // If length changes, then there exists a new production
          // specification
          instance_pair->first = DicesRcDriver::OK;
        }

        if (!instance_pair->second->production_specification.ensure_length(
          new_count,
          new_count))
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Unable to ensure production "
            "specification length " << new_count << ". attribute_id: "
            << static_cast<int>(attribute_id));
          break;
        }

        for (int iy = 0; iy < new_count; iy++)
        {
          if (instance_pair->second->production_specification[iy].component_id
              != ppspec->value[iy].component_id)
          {
            instance_pair->second->production_specification[iy].component_id =
              ppspec->value[iy].component_id;
            instance_pair->first = DicesRcDriver::OK;
          }

          ice::ProdSpecType dices_spec_type = ice::unspecified;
          DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
            ConvertIntellivueProdSpecTypeToDicesProdSpecType(
            &dices_spec_type,
            ppspec->value[iy].spec_type);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn << "Failed on IntellivueUtils::"
              "ConvertIntellivueProdSpecTypeToDicesProdSpecType(). "
              << DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }

          if (instance_pair->second->production_specification[iy].spec_type
            != dices_spec_type)
          {
            instance_pair->second->production_specification[iy].spec_type =
              dices_spec_type;
            instance_pair->first = DicesRcDriver::OK;
          }
          if (ppspec->value[iy].prod_spec.value)
          {
            if (strncmp(
              instance_pair->second->production_specification[iy].prod_spec,
              reinterpret_cast<const char*>(ppspec->value[iy].prod_spec.value),
              ice::LONG_STRING_LEN))
            {
              strncpy(
                instance_pair->second->production_specification[iy].prod_spec,
                reinterpret_cast<const char*>(ppspec->value[iy].prod_spec.
                value),
                ice::LONG_STRING_LEN);
              instance_pair->second->production_specification[iy].prod_spec[
                ice::LONG_STRING_LEN] = '\0';
              instance_pair->first = DicesRcDriver::OK;
            }
          }
          else
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Unable to set ProdSpecEntry "
              "value, because there is no memory allocated for value. "
              "attribute_id: " << static_cast<int>(attribute_id));
          }
        }
      }
        break;
      case NOM_ATTR_ID_MODEL:
      {
        intellivue::SystemModel* psm =
          reinterpret_cast<intellivue::SystemModel*>(
          connect_indication.conninfo.value[ix].attribute_val);
        if (!psm)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into SystemModel. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (psm->manufacturer.value)
        {
          if (strncmp(
            instance_pair->second->system_model.manufacturer,
            reinterpret_cast<const char*>(psm->manufacturer.value),
            ice::MEDIUM_STRING_LEN))
          {
            strncpy(
              instance_pair->second->system_model.manufacturer,
              reinterpret_cast<const char*>(psm->manufacturer.value),
              ice::MEDIUM_STRING_LEN);
            instance_pair->second->system_model.manufacturer[
              ice::MEDIUM_STRING_LEN] = '\0';
            instance_pair->first = DicesRcDriver::OK;
          }
        }
        else
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Unable to set SystemModel "
            "manufacturer, because there is no memory allocated for value. "
            "attribute_id: " << static_cast<int>(attribute_id));
        }

        if (psm->model_number.value)
        {
          if (strncmp(
            instance_pair->second->system_model.model_number,
            reinterpret_cast<const char*>(psm->model_number.value),
            ice::MEDIUM_STRING_LEN))
          {
            strncpy(
              instance_pair->second->system_model.model_number,
              reinterpret_cast<const char*>(psm->model_number.value),
              ice::MEDIUM_STRING_LEN);
            instance_pair->second->system_model.model_number[
              ice::MEDIUM_STRING_LEN] = '\0';
            instance_pair->first = DicesRcDriver::OK;
          }
        }
        else
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Unable to set SystemModel "
            "model_number, because there is no memory allocated for value. "
            "attribute_id: " << static_cast<int>(attribute_id));
        }
      }
        break;
    }
  }

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::GetIPAddressString(
  std::string* ip_address,
  const ConnectIndication& connect_indication)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "GetConnectIndicationIPAddress() ";
  if (!ip_address)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument ip_address is "
      "a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *ip_address = "";
  std::stringstream ss;

  for (int ix = 0; ix < connect_indication.conninfo.count; ix++)
  {
    if (!connect_indication.conninfo.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "ConnectIndInfo AVAType list is a "
        "null pointer");
      break;
    }
    if (connect_indication.conninfo.value[ix].attribute_id != NOM_ATTR_NET_ADDR_INFO) continue;

    intellivue::IpAddressInfo* addr_info =
      reinterpret_cast<intellivue::IpAddressInfo*>(
      connect_indication.conninfo.value[ix].attribute_val);
    if (!addr_info)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
        "into IpAddressInfo.");
      continue;
    }

    // Convert ip address array to string
    ss << static_cast<int>(addr_info->ip_address.value[0]) << "."
      << static_cast<int>(addr_info->ip_address.value[1]) << "."
      << static_cast<int>(addr_info->ip_address.value[2]) << "."
      << static_cast<int>(addr_info->ip_address.value[3]);
    *ip_address = ss.str();
    return DicesRcPhilipsIntellivueMP70::OK;
  }
  return DicesRcPhilipsIntellivueMP70::GET_IP_ADDRESS_INFO_FAILURE;
}

DicesRcPhilipsIntellivueMP70 IntellivueConnectIndicationMessage::
GetDataExportProtocolPortNumber(
  int* port_number,
  const ConnectIndication& connect_indication)
{
  static const char* sfn = "IntellivueConnectIndicationMessage::"
    "GetDataExportProtocolPortNumber() ";
  if (!port_number)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument port_number is "
      "a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *port_number = 0;
  std::stringstream ss;

  for (int ix = 0; ix < connect_indication.conninfo.count; ix++)
  {
    if (!connect_indication.conninfo.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "ConnectIndInfo AVAType list is a "
        "null pointer");
      break;
    }
    if (connect_indication.conninfo.value[ix].attribute_id != NOM_ATTR_PCOL_SUPPORT) continue;

    intellivue::ProtoSupport* proto_support =
      reinterpret_cast<intellivue::ProtoSupport*>(
      connect_indication.conninfo.value[ix].attribute_val);
    if (!proto_support)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
        "into ProtoSupport.");
      continue;
    }

    if (!proto_support->value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "ProtoSupportEntry list is a "
        "null pointer");
      continue;
    }

    for (int iy = 0; iy < proto_support->count; iy++)
    {
      if (proto_support->value[iy].appl_proto == AP_ID_DATA_OUT)
      {
        *port_number = static_cast<int>(proto_support->value[iy].port_number);
        return DicesRcPhilipsIntellivueMP70::OK;
      }
    }
  }
  return DicesRcPhilipsIntellivueMP70::GET_DATA_EXPORT_PORT_NUMBER_FAILURE;
}
