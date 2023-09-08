#include "clock-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <clockSupport.h>

#include "rc-entity-builder.h"

ClockTypeBuilder::ClockTypeBuilder() :
  AbstractTopicBuilder()
{

}

ClockTypeBuilder::~ClockTypeBuilder()
{

}

DicesRcEntityBuilder ClockTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ClockTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ClockTypeBuilder::get_type_name()
{
  return ice::ClockTypeSupport::get_type_name();
}
