#include "diagnostic-report-builder.h"

#include <ndds_namespace_cpp.h>
#include <diagnosticsSupport.h>

#include "rc-entity-builder.h"

DiagnosticReportBuilder::DiagnosticReportBuilder() :
  AbstractTopicBuilder()
{

}

DiagnosticReportBuilder::~DiagnosticReportBuilder()
{

}

DicesRcEntityBuilder DiagnosticReportBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::DiagnosticReportTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string DiagnosticReportBuilder::get_type_name()
{
  return ice::DiagnosticReportTypeSupport::get_type_name();
}

const std::string DiagnosticReportBuilder::get_topic_name()
{
  return ice::DiagnosticReportTopic;
}
