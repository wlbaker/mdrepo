#include "dicestyperegister.h"

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/stringhelper.h>
#include <ndds_namespace_cpp.h>

#include "alarmSupport.h"
#include "allergySupport.h"
#include "batterySupport.h"
#include "clockSupport.h"
#include "channelSupport.h"
#include "commonSupport.h"
#include "docboxSupport.h"
#include "dsaSupport.h"
#include "enumSupport.h"
#include "locationSupport.h"
#include "mdsSupport.h"
#include "metricSupport.h"
#include "numericSupport.h"
#include "operatorSupport.h"
#include "patdemoSupport.h"
#include "rtsaSupport.h"
#include "saSupport.h"
#include "trendevtSupport.h"
#include "tsaSupport.h"
#include "vmdSupport.h"
#include "exprSupport.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

DICESTypeRegister::DICESTypeRegister() { }

DICESTypeRegister::~DICESTypeRegister() { }

DICESTypeRegisterRC DICESTypeRegister::registerAllTypes()
{
  DDS::ReturnCode_t retcode;
  std::string errorStrBase =
    "DICESTypeRegister::registerAllTypes Failed to register type support for ";

  retcode =
    TheParticipantFactory->register_type_support(
    ice::AlarmSignalTypeSupport::register_type,
    ice::AlarmSignalTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::AlarmSignalTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::InformationSignalTypeSupport::register_type,
    ice::InformationSignalTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::InformationSignalTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::ReminderSignalTypeSupport::register_type,
    ice::ReminderSignalTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::ReminderSignalTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::AlarmContextTypeSupport::register_type,
    ice::AlarmContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::AlarmContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::AllergyTypeSupport::register_type,
    ice::AllergyTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::AllergyTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::BatteryTypeSupport::register_type,
    ice::BatteryTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::BatteryTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::ChannelTypeSupport::register_type,
    ice::ChannelTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::ChannelTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::ClockTypeSupport::register_type,
    ice::ClockTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::ClockTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::DeviceDriverLauncherStateTypeSupport::register_type,
    docbox::DeviceDriverLauncherStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::DeviceDriverLauncherStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::DeviceDriverStateTypeSupport::register_type,
    docbox::DeviceDriverStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::DeviceDriverStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::DSAContextTypeSupport::register_type,
    ice::DSAContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::DSAContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::DSAObservedValueTypeSupport::register_type,
    ice::DSAObservedValueTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::DSAObservedValueTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::EnumerationContextTypeSupport::register_type,
    ice::EnumerationContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::EnumerationContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::EnumerationObservedValueTypeSupport::register_type,
    ice::EnumerationObservedValueTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::EnumerationObservedValueTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::InactivitySignalTypeSupport::register_type,
    docbox::InactivitySignalTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::InactivitySignalTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::LocationTypeSupport::register_type,
    ice::LocationTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::LocationTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::MDSTypeSupport::register_type,
    ice::MDSTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::MDSTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::NumericContextTypeSupport::register_type,
    ice::NumericContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::NumericContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::NumericObservedValueTypeSupport::register_type,
    ice::NumericObservedValueTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::NumericObservedValueTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::OperatorTypeSupport::register_type,
    ice::OperatorTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::OperatorTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::OperatorAuthenticationTypeSupport::register_type,
    ice::OperatorAuthenticationTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::OperatorAuthenticationTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::OperatorAuthenticationErrorTypeSupport::register_type,
    ice::OperatorAuthenticationErrorTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::OperatorAuthenticationErrorTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::PatientIdentificationTypeSupport::register_type,
    ice::PatientIdentificationTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::PatientIdentificationTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::PatientDemographicsTypeSupport::register_type,
    ice::PatientDemographicsTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::PatientDemographicsTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::RTSAContextTypeSupport::register_type,
    ice::RTSAContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::RTSAContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::RTSAObservedValueTypeSupport::register_type,
    ice::RTSAObservedValueTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::RTSAObservedValueTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::TrendEventTypeSupport::register_type,
    docbox::TrendEventTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::TrendEventTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::TSAContextTypeSupport::register_type,
    ice::TSAContextTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::TSAContextTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::TSAObservedValueTypeSupport::register_type,
    ice::TSAObservedValueTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::TSAObservedValueTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    ice::VMDTypeSupport::register_type,
    ice::VMDTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::VMDTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::ModuleServiceIdentificationTypeSupport::register_type,
    docbox::ModuleServiceIdentificationTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::ModuleServiceIdentificationTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    docbox::ModuleServiceStateTypeSupport::register_type,
    docbox::ModuleServiceStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::ModuleServiceStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    expr::DiagnosisTypeSupport::register_type,
    expr::DiagnosisTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + expr::DiagnosisTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    expr::DxHistoryTypeSupport::register_type,
    expr::DxHistoryTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + expr::DxHistoryTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
    expr::PatientMedicationTypeSupport::register_type,
    expr::PatientMedicationTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + expr::PatientMedicationTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }
  
  retcode =
    TheParticipantFactory->register_type_support(
      docbox::LCDModuleStateTypeSupport::register_type,
      docbox::LCDModuleStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::LCDModuleStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }
  
  retcode =
    TheParticipantFactory->register_type_support(
      docbox::ModuleServiceFocusTypeSupport::register_type,
      docbox::ModuleServiceFocusTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::ModuleServiceFocusTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
      docbox::ModuleServiceFocusErrorTypeSupport::register_type,
      docbox::ModuleServiceFocusErrorTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::ModuleServiceFocusErrorTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }
  
  retcode =
    TheParticipantFactory->register_type_support(
      ice::PatientIdentificationErrorTypeSupport::register_type,
      ice::PatientIdentificationErrorTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + ice::PatientIdentificationErrorTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
      docbox::DriverManagerStateTypeSupport::register_type,
      docbox::DriverManagerStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::DriverManagerStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }

  retcode =
    TheParticipantFactory->register_type_support(
      docbox::ModuleDisplayStateTypeSupport::register_type,
      docbox::ModuleDisplayStateTypeSupport::get_type_name());

  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, errorStrBase + docbox::ModuleDisplayStateTypeSupport::get_type_name());
    return DICESTypeRegisterRC::FAILED_TO_REGISTER_TYPES;
  }
    
  return DICESTypeRegisterRC::OK;
}

DICESTypeRegisterRC DICESTypeRegister::UnregisterAllTypes(
  DDS::DomainParticipant* participant)
{
  static const char* sfn = "DICESTypeRegister::UnregisterAllTypes()";
  static const char* err_str_base = " Failed to unregister type support for ";
  DICESTypeRegisterRC status = DICESTypeRegisterRC::OK;
  DDS::ReturnCode_t retcode = DDS::RETCODE_OK;

  if (!participant)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Pointer to DDS Domain Participant "
      "is null");
    return DICESTypeRegisterRC::BAD_FUNCTION_ARGUMENT;
  }

  retcode = ice::AlarmSignalTypeSupport::unregister_type(
    participant,
    ice::AlarmSignalTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::AlarmSignalTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::InformationSignalTypeSupport::unregister_type(
    participant,
    ice::InformationSignalTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::InformationSignalTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::ReminderSignalTypeSupport::unregister_type(
    participant,
    ice::ReminderSignalTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::ReminderSignalTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::AlarmContextTypeSupport::unregister_type(
    participant,
    ice::AlarmContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::AlarmContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::AllergyTypeSupport::unregister_type(
    participant,
    ice::AllergyTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::AllergyTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::BatteryTypeSupport::unregister_type(
    participant,
    ice::BatteryTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::BatteryTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::ChannelTypeSupport::unregister_type(
    participant,
    ice::ChannelTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::ChannelTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::ClockTypeSupport::unregister_type(
    participant,
    ice::ClockTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::ClockTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::DeviceDriverLauncherStateTypeSupport::unregister_type(
    participant,
    docbox::DeviceDriverLauncherStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base
      << docbox::DeviceDriverLauncherStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::DeviceDriverStateTypeSupport::unregister_type(
    participant,
    docbox::DeviceDriverStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::DeviceDriverStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::DSAContextTypeSupport::unregister_type(
    participant,
    ice::DSAContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::DSAContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::DSAObservedValueTypeSupport::unregister_type(
    participant,
    ice::DSAObservedValueTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::DSAObservedValueTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::EnumerationContextTypeSupport::unregister_type(
    participant,
    ice::EnumerationContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::EnumerationContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::EnumerationObservedValueTypeSupport::unregister_type(
    participant,
    ice::EnumerationObservedValueTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::EnumerationObservedValueTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::InactivitySignalTypeSupport::unregister_type(
    participant,
    docbox::InactivitySignalTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::InactivitySignalTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::LocationTypeSupport::unregister_type(
    participant,
    ice::LocationTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::LocationTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::MDSTypeSupport::unregister_type(
    participant,
    ice::MDSTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::MDSTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::NumericContextTypeSupport::unregister_type(
    participant,
    ice::NumericContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::NumericContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::NumericObservedValueTypeSupport::unregister_type(
    participant,
    ice::NumericObservedValueTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::NumericObservedValueTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::OperatorTypeSupport::unregister_type(
    participant,
    ice::OperatorTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::OperatorTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::OperatorAuthenticationTypeSupport::unregister_type(
    participant,
    ice::OperatorAuthenticationTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::OperatorAuthenticationTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::OperatorAuthenticationErrorTypeSupport::unregister_type(
    participant,
    ice::OperatorAuthenticationErrorTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::OperatorAuthenticationErrorTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::PatientIdentificationTypeSupport::unregister_type(
    participant,
    ice::PatientIdentificationTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::PatientIdentificationTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::PatientDemographicsTypeSupport::unregister_type(
    participant,
    ice::PatientDemographicsTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::PatientDemographicsTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::RTSAContextTypeSupport::unregister_type(
    participant,
    ice::RTSAContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::RTSAContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::RTSAObservedValueTypeSupport::unregister_type(
    participant,
    ice::RTSAObservedValueTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::RTSAObservedValueTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::TrendEventTypeSupport::unregister_type(
    participant,
    docbox::TrendEventTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::TrendEventTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::TSAContextTypeSupport::unregister_type(
    participant,
    ice::TSAContextTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::TSAContextTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::TSAObservedValueTypeSupport::unregister_type(
    participant,
    ice::TSAObservedValueTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::TSAObservedValueTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = ice::VMDTypeSupport::unregister_type(
    participant,
    ice::VMDTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::VMDTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::ModuleServiceIdentificationTypeSupport::unregister_type(
    participant,
    docbox::ModuleServiceIdentificationTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::ModuleServiceIdentificationTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::ModuleServiceStateTypeSupport::unregister_type(
    participant,
    docbox::ModuleServiceStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::ModuleServiceStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = expr::DiagnosisTypeSupport::unregister_type(
    participant,
    expr::DiagnosisTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << expr::DiagnosisTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = expr::DxHistoryTypeSupport::unregister_type(
    participant,
    expr::DxHistoryTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << expr::DxHistoryTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = expr::PatientMedicationTypeSupport::unregister_type(
    participant,
    expr::PatientMedicationTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << expr::PatientMedicationTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }
  
  retcode = docbox::LCDModuleStateTypeSupport::unregister_type(
    participant,
    docbox::LCDModuleStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::LCDModuleStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::ModuleServiceFocusTypeSupport::unregister_type(
    participant,
    docbox::ModuleServiceFocusTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::ModuleServiceFocusTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::ModuleServiceFocusErrorTypeSupport::unregister_type(
    participant,
    docbox::ModuleServiceFocusErrorTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::ModuleServiceFocusErrorTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }
  
  retcode = ice::PatientIdentificationErrorTypeSupport::unregister_type(
    participant,
    ice::PatientIdentificationErrorTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << ice::PatientIdentificationErrorTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::DriverManagerStateTypeSupport::unregister_type(
    participant,
    docbox::DriverManagerStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::DriverManagerStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  retcode = docbox::ModuleDisplayStateTypeSupport::unregister_type(
    participant,
    docbox::ModuleDisplayStateTypeSupport::get_type_name());
  if (retcode != DDS::RETCODE_OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << err_str_base << docbox::ModuleDisplayStateTypeSupport::get_type_name());
    status = DICESTypeRegisterRC::FAILED_TO_UNREGISTER_TYPES;
  }

  return status;
}
