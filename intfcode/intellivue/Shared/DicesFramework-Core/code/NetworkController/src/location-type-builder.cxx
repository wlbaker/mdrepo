#include "location-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <locationSupport.h>

#include "rc-entity-builder.h"

LocationTypeBuilder::LocationTypeBuilder() :
  AbstractTopicBuilder()
{

}

LocationTypeBuilder::~LocationTypeBuilder()
{

}

DicesRcEntityBuilder LocationTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::LocationTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string LocationTypeBuilder::get_type_name()
{
  return ice::LocationTypeSupport::get_type_name();
}
