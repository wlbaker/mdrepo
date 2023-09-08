/**
 * @file intellivue_mds_create_event_report.cxx
 *
 * @brief Defines a class which parses MDS create event report response.
 *
 * @author M Szwaja
 */
//=============================================================================

#include "intellivue_mds_create_event_report.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <ndds/ndds_namespace_cpp.h>
#include "PhilipsIntellivueMP70ReturnCodes.h"
#include "intellivue_utils.h"
#include "mds.h"
#include "vmd.h"
#include "dices_rc_driver.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventReport::
IsMDSCreateEventReport(
  bool* is_msg,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueMDSCreateEventReport::"
    "IsMDSCreateEventReport() ";

  if (!is_msg)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Function argument is_msg is a null "
      "pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }
  *is_msg = false;

  if (!buffer)
  {
    LOG4CPLUS_WARN(root_logger, sfn << "Function argument buffer is a null "
      "pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (numbytes < 11)
    return DicesRcPhilipsIntellivueMP70::OK;

  if (buffer[0] != 0xE1)
    return DicesRcPhilipsIntellivueMP70::OK;

  uint16_t ro_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[4])));

  if (ro_type != ROIV_APDU)
    return DicesRcPhilipsIntellivueMP70::OK;

  uint16_t command_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[10])));

  if (command_type != CMD_CONFIRMED_EVENT_REPORT)
    return DicesRcPhilipsIntellivueMP70::OK;

  *is_msg = true;
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventReport::
ParseMDSCreateEventReport(
  MDSCreateEventReport* mds_create_event_report,
  uint8_t* buffer,
  unsigned int numbytes)
{
  static const char* sfn = "IntellivueMDSCreateEventReport::"
    "ParseMDSCreateEventReport() ";

  if (!mds_create_event_report)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "mds_create_event_report is a null pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument buffer is a null "
      "pointer");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (numbytes < (sizeof(intellivue::SPpdu) + sizeof(intellivue::ROapdus)))
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to parse SPpdu and ROapdus "
      "from response. Not enough bytes in buffer.");
    return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
  }

  int iindex = 0;
  uint16_t ro_type = 0;
  DicesRcPhilipsIntellivueMP70 status = DicesRcPhilipsIntellivueMP70::OK;

  ro_type = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[4])));

  switch (ro_type)
  {
    case ROIV_APDU:
    {
      // Sppdu
      mds_create_event_report->sppdu.session_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->sppdu.p_context_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      // ROapdus
      mds_create_event_report->roapdus.ro_type = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->roapdus.length = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < mds_create_event_report->roapdus.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt MDS create event "
          "report. ROapdus length is greater than the number of bytes in "
          "message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      // ROIVapdu
      mds_create_event_report->roivapdu.invoke_id = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->roivapdu.command_type = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->roivapdu.length = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < mds_create_event_report->roivapdu.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt MDS create event "
          "report. ROIVapdu length is greater than the number of bytes in "
          "message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      // EventReportArgument
      mds_create_event_report->eventArg.managed_object.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->eventArg.managed_object.m_obj_inst.
        context_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->eventArg.managed_object.m_obj_inst.handle =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->eventArg.event_time = ntohl(
        *(reinterpret_cast<uint32_t*>(&buffer[iindex])));
      iindex += 4;

      mds_create_event_report->eventArg.event_type = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->eventArg.length = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex) < mds_create_event_report->eventArg.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt MDS create event "
          "report. EventReportArgument length is greater than the number of "
          "bytes in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      // MdsCreateInfo
      mds_create_event_report->createInfo.managed_object.m_obj_class = ntohs(
        *(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->createInfo.managed_object.m_obj_inst.
        context_id = ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->createInfo.managed_object.m_obj_inst.handle =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      // AttributeList
      mds_create_event_report->createInfo.attribute_list.count =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      mds_create_event_report->createInfo.attribute_list.length =
        ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
      iindex += 2;

      if ((numbytes - iindex)
        < mds_create_event_report->createInfo.attribute_list.length)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt MDS create event "
          "report. AttributeList length is greater than the number of bytes "
          "in message.");
        return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
      }

      mds_create_event_report->createInfo.attribute_list.value =
        new (std::nothrow) intellivue::AVAType[
        mds_create_event_report->createInfo.attribute_list.count]();
      if (!mds_create_event_report->createInfo.attribute_list.value)
      {
        LOG4CPLUS_ERROR(root_logger, sfn << "Failed to allocate memory "
          "for MDSCreateInfo AttributeList");
        return DicesRcPhilipsIntellivueMP70::MEMORY_ALLOCATION_FAILURE;
      }

      // Attribute IDs and values
      for (
        int ix = 0;
        ix < mds_create_event_report->createInfo.attribute_list.count;
        ix++)
      {
        mds_create_event_report->createInfo.attribute_list.value[ix].
          attribute_id = ntohs(*(reinterpret_cast<uint16_t*>(
          &buffer[iindex])));
        iindex += 2;

        mds_create_event_report->createInfo.attribute_list.value[ix].length =
          ntohs(*(reinterpret_cast<uint16_t*>(&buffer[iindex])));
        iindex += 2;

        if ((numbytes - iindex)
          < mds_create_event_report->createInfo.attribute_list.value[ix].length)
        {
          LOG4CPLUS_ERROR(root_logger, sfn << "Corrupt MDS create event "
            "report. AttributeList attribute length is greater than the "
            "number of bytes in message.");
          return DicesRcPhilipsIntellivueMP70::PARSE_RESPONSE_FAILURE;
        }

        bool is_valid = false;
        status = IntellivueUtils::IsValidMDSCreateEventReportAttribute(
          mds_create_event_report->createInfo.attribute_list.value[ix].
          attribute_id,
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
            &mds_create_event_report->createInfo.attribute_list.value[ix],
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

        iindex += mds_create_event_report->createInfo.attribute_list.value[ix].
          length;
      }
    }
      break;
    default:
      LOG4CPLUS_WARN(root_logger, sfn << "Received unexpected ro_type ("
        << static_cast<int>(ro_type) << ") for a MDS Create Event Report");
      break; // Do nothing
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventReport::
DeleteMDSCreateEventReport(
  MDSCreateEventReport* mds_create_event_report)
{
  static const char* sfn = "IntellivueMDSCreateEventReport::"
    "DeleteMDSCreateEventReport() ";
  if (!mds_create_event_report)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "mds_create_event_report is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  for (
    int ix = 0;
    ix < mds_create_event_report->createInfo.attribute_list.count;
    ix++)
  {
    if (!mds_create_event_report->createInfo.attribute_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "AVAType list is a null pointer.");
      break;
    }
    DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::DeleteAttribute(
      &mds_create_event_report->createInfo.attribute_list.value[ix]);
    if (status != DicesRcPhilipsIntellivueMP70::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn <<
        DicesRcPhilipsIntellivueMP70StatusMessage::
        DicesRcPhilipsIntellivueMP70ToString(status));
      return status;
    }
  }
  delete [] mds_create_event_report->createInfo.attribute_list.value;
  mds_create_event_report->createInfo.attribute_list.value = nullptr;

  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventReport::
SetMDSWithMDSCreateEventReport(
  std::pair<DicesRcDriver, ice::MDS*>* instance_pair,
  const MDSCreateEventReport& mds_create_event_report)
{
  static const char* sfn = "IntellivueMDSCreateEventReport::"
    "SetMDSWithMDSCreateEventReport() ";

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

  for (
    int ix = 0;
    ix < mds_create_event_report.createInfo.attribute_list.count;
    ix++)
  {
    if (!mds_create_event_report.createInfo.attribute_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "attribute list AVAType list is a "
        "null pointer.");
      break;
    }
    intellivue::OIDType attribute_id = mds_create_event_report.createInfo.
      attribute_list.value[ix].attribute_id;
    switch (attribute_id)
    {
      case NOM_ATTR_ID_HANDLE:
      {
        intellivue::Handle* phandle =
          reinterpret_cast<intellivue::Handle*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!phandle)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into Handle. attribute_id: " << static_cast<int>(attribute_id));
          break;
        }

        if (instance_pair->second->handle != *phandle)
        {
          instance_pair->second->handle = *phandle;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
      case NOM_ATTR_SYS_TYPE:
      {
        intellivue::TYPE* ptype =
          reinterpret_cast<intellivue::TYPE*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!ptype)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into TYPE. attribute_id: " << static_cast<int>(attribute_id));
          break;
        }
        ice::NomPartition dices_partition = ice::nom_part_unspec;
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
          ConvertIntellivueNomPartitionToDicesNomPartition(
          &dices_partition,
          ptype->partition);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
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
      case NOM_ATTR_ID_MODEL:
      {
        intellivue::SystemModel* psm =
          reinterpret_cast<intellivue::SystemModel*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
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
      case NOM_ATTR_NOM_VERS:
      {
        uint32_t* pnom_vers = reinterpret_cast<uint32_t*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!pnom_vers)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into uint32_t. attribute_id: " << static_cast<int>(attribute_id));
          break;
        }

        int new_int = htonl(static_cast<int>(*pnom_vers));
        uint8_t* pnew_int = reinterpret_cast<uint8_t*>(&new_int);
        uint16_t major = ntohs(*(reinterpret_cast<uint16_t*>(&pnew_int[0])));
        uint16_t minor = ntohs(*(reinterpret_cast<uint16_t*>(&pnew_int[2])));

        instance_pair->second->nomenclature_version.nom_major_version = major;
        instance_pair->second->nomenclature_version.nom_major_version = minor;
      }
        break;
      case NOM_ATTR_ID_PROD_SPECN:
      {
        intellivue::ProductionSpec* ppspec =
          reinterpret_cast<intellivue::ProductionSpec*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!ppspec)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into ProductionSpec. attribute_id: " << static_cast<int>(
            attribute_id));
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
            maximum() << "). attribute_id: " << static_cast<int>(
            attribute_id));
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
            "specification length " << new_count << ". "
            "attribute_id: " << static_cast<int>(attribute_id));
          break;
        }

        for (int iy = 0; iy < new_count; iy++)
        {
          instance_pair->second->production_specification[iy].component_id =
            ppspec->value[iy].component_id;

          ice::ProdSpecType dices_spec_type = ice::unspecified;
          DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
            ConvertIntellivueProdSpecTypeToDicesProdSpecType(
            &dices_spec_type,
            ppspec->value[iy].spec_type);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
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
      case NOM_ATTR_VMS_MDS_STAT:
      {
        intellivue::MDSStatus* pmds_status =
          reinterpret_cast<intellivue::MDSStatus*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!pmds_status)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into MDSStatus. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        ice::MDSStatus dices_mds_status = ice::MDSStatus::disconnected;
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
          ConvertIntellivueMDSStatusToDicesMDSStatus(
          &dices_mds_status,
          *pmds_status);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }

        if (instance_pair->second->mds_status != dices_mds_status)
        {
          instance_pair->second->mds_status = dices_mds_status;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
      case NOM_ATTR_MODE_OP:
      {
        uint16_t* pop_mode = reinterpret_cast<uint16_t*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!pop_mode)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into uint16_t. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (!instance_pair->second->operating_mode)
        {
          instance_pair->second->operating_mode =
            reinterpret_cast<ice::PrivateOid *>(
            DDS::Heap_malloc(sizeof(ice::PrivateOid)));
          if (!instance_pair->second->operating_mode)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Unable to allocate memory "
              "for ice::PrivateOid. attribute_id: " << static_cast<int>(
              attribute_id));
            break;
          }
        }
        if (*instance_pair->second->operating_mode != *pop_mode)
        {
          *instance_pair->second->operating_mode = *pop_mode;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
      case NOM_ATTR_TIME_ABS:
      {
        intellivue::AbsoluteTime* pabsolute_time =
          reinterpret_cast<intellivue::AbsoluteTime*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!pabsolute_time)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into AbsoluteTime. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (pabsolute_time->century != 0xFF
          || pabsolute_time->year != 0xFF
          || pabsolute_time->month != 0xFF
          || pabsolute_time->day != 0xFF
          || pabsolute_time->hour != 0xFF
          || pabsolute_time->minute != 0xFF
          || pabsolute_time->second != 0xFF
          || pabsolute_time->sec_fractions != 0xFF)
        {
          ice::Timespec dices_absolute_time = { 0 };
          DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
            ConvertIntellivueAbsoluteTimeToDicesTimespec(
            &dices_absolute_time,
            *pabsolute_time);
          if (status != DicesRcPhilipsIntellivueMP70::OK)
          {
            LOG4CPLUS_ERROR(root_logger, sfn <<
              DicesRcPhilipsIntellivueMP70StatusMessage::
              DicesRcPhilipsIntellivueMP70ToString(status));
            return status;
          }

          if (!instance_pair->second->date_and_time)
          {
            instance_pair->second->date_and_time =
              reinterpret_cast<ice::Timespec *>(
              DDS::Heap_malloc(sizeof(ice::Timespec)));
            if (!instance_pair->second->date_and_time)
            {
              LOG4CPLUS_WARN(root_logger, sfn << "Unable to allocate memory "
                "for ice::Timespec. attribute_id: " << static_cast<int>(
                attribute_id));
              break;
            }
          }
          instance_pair->second->date_and_time->seconds =
            dices_absolute_time.seconds;
          instance_pair->second->date_and_time->nanoseconds =
            dices_absolute_time.nanoseconds;
        }
      }
        break;
      case NOM_ATTR_TIME_REL:
      {
        intellivue::RelativeTime* prelative_time =
          reinterpret_cast<intellivue::RelativeTime*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!prelative_time)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into RelativeTime. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }
        ice::Duration dices_relative_time = { 0 };
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
          ConvertIntellivueRelativeTimeToDicesDuration(
          &dices_relative_time,
          *prelative_time);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }

        if (!instance_pair->second->relative_time)
        {
          instance_pair->second->relative_time =
            reinterpret_cast<ice::Duration *>(
            DDS::Heap_malloc(sizeof(ice::Duration)));
          if (!instance_pair->second->relative_time)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Unable to allocate memory for, "
              "ice::RelativeTime. attribute_id: " << static_cast<int>(
              attribute_id));
            break;
          }
        }
        instance_pair->second->relative_time->seconds =
          dices_relative_time.seconds;
        instance_pair->second->relative_time->nanoseconds =
          dices_relative_time.nanoseconds;
      }
        break;
      case NOM_ATTR_ALTITUDE:
      {
        int16_t* paltitude_meters = reinterpret_cast<int16_t*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!paltitude_meters)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into int16_t. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (!instance_pair->second->altitude_meters)
        {
          instance_pair->second->altitude_meters =
            reinterpret_cast<ice::INT16 *>(
            DDS::Heap_malloc(sizeof(ice::INT16)));
          if (!instance_pair->second->altitude_meters)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Unable to allocate memory for "
              "ice::INT16. attribute_id: " << static_cast<int>(attribute_id));
            break;
          }
        }
        if (*instance_pair->second->altitude_meters != *paltitude_meters)
        {
          *instance_pair->second->altitude_meters = *paltitude_meters;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
      case NOM_ATTR_LINE_FREQ:
      {
        intellivue::LineFrequency* pline_frequency =
          reinterpret_cast<intellivue::LineFrequency*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!pline_frequency)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into LineFrequency. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (!instance_pair->second->line_frequency)
        {
          instance_pair->second->line_frequency = reinterpret_cast<ice::LineFrequency *>(
            DDS::Heap_malloc(sizeof(ice::LineFrequency)));
          if (!instance_pair->second->line_frequency)
          {
            LOG4CPLUS_WARN(root_logger, sfn << "Unable to allocate memory for "
              "ice::LineFrequency. attribute_id: " << static_cast<int>(
              attribute_id));
            break;
          }
        }
        ice::LineFrequency dices_line_frequency = ice::line_f_unspec;
        DicesRcPhilipsIntellivueMP70 status = IntellivueUtils::
          ConvertIntellivueLineFrequencyToDicesLineFrequency(
          &dices_line_frequency,
          *pline_frequency);
        if (status != DicesRcPhilipsIntellivueMP70::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn <<
            DicesRcPhilipsIntellivueMP70StatusMessage::
            DicesRcPhilipsIntellivueMP70ToString(status));
          return status;
        }

        if (*instance_pair->second->line_frequency != dices_line_frequency)
        {
          *instance_pair->second->line_frequency = dices_line_frequency;
          instance_pair->first = DicesRcDriver::OK;
        }
      }
        break;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}

DicesRcPhilipsIntellivueMP70 IntellivueMDSCreateEventReport::SetVMDWithMDSCreateEventReport(
  std::pair<DicesRcDriver, ice::VMD*>* instance_pair,
  const MDSCreateEventReport& mds_create_event_report)
{
  static const char* sfn = "IntellivueMDSCreateEventReport::"
    "SetVMDWithMDSCreateEventReport() ";

  if (!instance_pair)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "instance_pair is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  if (!instance_pair->second)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument "
      "ice::VMD in instance_pair is a null pointer.");
    return DicesRcPhilipsIntellivueMP70::NULL_POINTER_FUNCTION_ARGUMENT_FAILURE;
  }

  for (
    int ix = 0;
    ix < mds_create_event_report.createInfo.attribute_list.count;
    ix++)
  {
    if (!mds_create_event_report.createInfo.attribute_list.value)
    {
      LOG4CPLUS_WARN(root_logger, sfn << "attribute list AVAType list is a "
        "null pointer.");
      break;
    }
    intellivue::OIDType attribute_id = mds_create_event_report.createInfo.
      attribute_list.value[ix].attribute_id;
    switch (attribute_id)
    {
      case NOM_ATTR_LOCALIZN:
      {
        intellivue::SystemLocal* psystem_local =
          reinterpret_cast<intellivue::SystemLocal*>(
          mds_create_event_report.createInfo.attribute_list.value[ix].
          attribute_val);
        if (!psystem_local)
        {
          LOG4CPLUS_WARN(root_logger, sfn << "Failed to cast attribute_val "
            "into SystemLocal. attribute_id: " << static_cast<int>(
            attribute_id));
          break;
        }

        if (psystem_local->format == STRFMT_UNICODE_NT)
        {
          if (instance_pair->second->locale.str_spec.str_flags
            != ice::str_flag_nt)
          {
            instance_pair->second->locale.str_spec.str_flags =
              ice::str_flag_nt;
            instance_pair->first = DicesRcDriver::OK;
          }
        }
        if (instance_pair->second->locale.str_spec.str_max_len
          != ice::LONGLONG_STRING_LEN)
        {
          instance_pair->second->locale.str_spec.str_max_len =
            ice::LONGLONG_STRING_LEN;
          instance_pair->first = DicesRcDriver::OK;
        }

        switch (psystem_local->language)
        {
            // English 'e' = 0x65, 'n' = 0x6E. unused bytes filled with null.
          case ENGLISH:
            if (instance_pair->second->locale.language
              != ice::LocaleLanguageEnglish)
            {
              instance_pair->second->locale.language =
                ice::LocaleLanguageEnglish;
              instance_pair->first = DicesRcDriver::OK;
            }
            break;
          default:
            LOG4CPLUS_WARN(root_logger, sfn << "Received unknown language ("
              << psystem_local->language << ").");
            break;
        }
      }
        break;
    }
  }
  return DicesRcPhilipsIntellivueMP70::OK;
}
