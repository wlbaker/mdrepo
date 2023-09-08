#include "device-driver-launcher-state-builder.h"
#include <docboxSupport.h>

DeviceDriverLauncherStateBuilder::DeviceDriverLauncherStateBuilder() :
  DeviceDriverLauncherStateTypeBuilder()
{

}

DeviceDriverLauncherStateBuilder::~DeviceDriverLauncherStateBuilder()
{

}

const std::string DeviceDriverLauncherStateBuilder::get_topic_name()
{
  return docbox::DeviceDriverLauncherStateTopic;
}
