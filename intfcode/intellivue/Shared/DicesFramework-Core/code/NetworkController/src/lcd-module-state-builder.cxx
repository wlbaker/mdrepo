#include "lcd-module-state-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

LCDModuleStateBuilder::LCDModuleStateBuilder() :
  AbstractTopicBuilder()
{

}

LCDModuleStateBuilder::~LCDModuleStateBuilder()
{

}

DicesRcEntityBuilder LCDModuleStateBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::LCDModuleStateTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string LCDModuleStateBuilder::get_type_name()
{
  return docbox::LCDModuleStateTypeSupport::get_type_name();
}

const std::string LCDModuleStateBuilder::get_topic_name()
{
  return docbox::LCDModuleStateTopic;
}
