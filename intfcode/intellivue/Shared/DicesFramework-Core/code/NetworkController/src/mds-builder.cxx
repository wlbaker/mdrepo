#include "mds-builder.h"

#include <ndds_namespace_cpp.h>
#include <mdsSupport.h>

#include "rc-entity-builder.h"

MDSBuilder::MDSBuilder() :
  AbstractTopicBuilder()
{

}

MDSBuilder::~MDSBuilder()
{

}

DicesRcEntityBuilder MDSBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::MDSTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string MDSBuilder::get_type_name()
{
  return ice::MDSTypeSupport::get_type_name();
}

const std::string MDSBuilder::get_topic_name()
{
  return ice::MDSTopic;
}
