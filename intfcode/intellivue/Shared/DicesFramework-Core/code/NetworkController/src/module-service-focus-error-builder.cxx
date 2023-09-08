#include "module-service-focus-error-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

ModuleServiceFocusErrorBuilder::ModuleServiceFocusErrorBuilder() :
  AbstractTopicBuilder()
{

}

ModuleServiceFocusErrorBuilder::~ModuleServiceFocusErrorBuilder()
{

}

DicesRcEntityBuilder ModuleServiceFocusErrorBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::ModuleServiceFocusErrorTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ModuleServiceFocusErrorBuilder::get_type_name()
{
  return docbox::ModuleServiceFocusErrorTypeSupport::get_type_name();
}

const std::string ModuleServiceFocusErrorBuilder::get_topic_name()
{
  return docbox::ModuleServiceFocusErrorTopic;
}
