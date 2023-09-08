#include "keyed-octets-builder.h"

#include <ndds_namespace_cpp.h>
#include <common.h>

#include "rc-entity-builder.h"

KeyedOctetsBuilder::KeyedOctetsBuilder() :
  AbstractTopicBuilder()
{

}

KeyedOctetsBuilder::~KeyedOctetsBuilder()
{

}

DicesRcEntityBuilder KeyedOctetsBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      DDS::KeyedOctetsTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string KeyedOctetsBuilder::get_type_name()
{
  return DDS::KeyedOctetsTypeSupport::get_type_name();
}

const std::string KeyedOctetsBuilder::get_topic_name()
{
  return KeyedOctetsTopic;
}
