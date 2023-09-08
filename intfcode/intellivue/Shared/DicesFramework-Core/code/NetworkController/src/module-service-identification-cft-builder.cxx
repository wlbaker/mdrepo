#include "module-service-identification-cft-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

ModuleServiceIdentificationCftBuilder::ModuleServiceIdentificationCftBuilder(std::string content_filtered_topic_name) :
  AbstractContentFilteredTopicBuilder(content_filtered_topic_name)
{

}

ModuleServiceIdentificationCftBuilder::~ModuleServiceIdentificationCftBuilder()
{

}

DicesRcEntityBuilder ModuleServiceIdentificationCftBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::ModuleServiceIdentificationTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ModuleServiceIdentificationCftBuilder::get_library_name()
{
  return "dices_dim_library";
}

const std::string ModuleServiceIdentificationCftBuilder::get_type_name()
{
  return docbox::ModuleServiceIdentificationTypeSupport::get_type_name();
}

const std::string ModuleServiceIdentificationCftBuilder::get_qos_profile()
{
  return "dices_dim_durable_profile";
}

const std::string ModuleServiceIdentificationCftBuilder::get_topic_name()
{
  return docbox::ModuleServiceIdentificationTopic;
}
