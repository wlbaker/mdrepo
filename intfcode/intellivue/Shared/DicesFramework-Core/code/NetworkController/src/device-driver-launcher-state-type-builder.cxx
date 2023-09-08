#include "device-driver-launcher-state-type-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

DeviceDriverLauncherStateTypeBuilder::DeviceDriverLauncherStateTypeBuilder() :
  AbstractTopicBuilder()
{

}

DeviceDriverLauncherStateTypeBuilder::~DeviceDriverLauncherStateTypeBuilder()
{

}

DicesRcEntityBuilder DeviceDriverLauncherStateTypeBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      docbox::DeviceDriverLauncherStateTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string DeviceDriverLauncherStateTypeBuilder::get_type_name()
{
  return docbox::DeviceDriverLauncherStateTypeSupport::get_type_name();
}
