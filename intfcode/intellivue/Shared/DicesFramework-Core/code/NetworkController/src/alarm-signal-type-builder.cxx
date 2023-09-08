#include "alarm-signal-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <alarmSupport.h>

#include "rc-entity-builder.h"

AlarmSignalTypeBuilder::AlarmSignalTypeBuilder() :
  AbstractTopicBuilder()
{

}

AlarmSignalTypeBuilder::~AlarmSignalTypeBuilder()
{

}

DicesRcEntityBuilder AlarmSignalTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::AlarmSignalTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string AlarmSignalTypeBuilder::get_type_name()
{
  return ice::AlarmSignalTypeSupport::get_type_name();
}
