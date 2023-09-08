#include "device-driver-launcher-state-cft-builder.h"

#include <ndds_namespace_cpp.h>
#include <docboxSupport.h>

#include "rc-entity-builder.h"

DeviceDriverLauncherStateCftBuilder::DeviceDriverLauncherStateCftBuilder(std::string content_filtered_topic_name) :
  AbstractContentFilteredTopicBuilder(content_filtered_topic_name)
{

}

DeviceDriverLauncherStateCftBuilder::~DeviceDriverLauncherStateCftBuilder()
{

}

DicesRcEntityBuilder DeviceDriverLauncherStateCftBuilder::register_type()
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

const std::string DeviceDriverLauncherStateCftBuilder::get_library_name()
{
  return "dices_dim_library";
}

const std::string DeviceDriverLauncherStateCftBuilder::get_topic_name()
{
  return docbox::DeviceDriverLauncherStateTopic;
}

const std::string DeviceDriverLauncherStateCftBuilder::get_type_name()
{
  return docbox::DeviceDriverLauncherStateTypeSupport::get_type_name();
}

const std::string DeviceDriverLauncherStateCftBuilder::get_qos_profile()
{
  return "dices_dim_durable_profile";
}
