#include "device-driver-launcher-state-obj-builder.h"
#include <docboxSupport.h>

DeviceDriverLauncherStateObjBuilder::DeviceDriverLauncherStateObjBuilder() :
  DeviceDriverLauncherStateTypeBuilder()
{

}

DeviceDriverLauncherStateObjBuilder::~DeviceDriverLauncherStateObjBuilder()
{

}

const std::string DeviceDriverLauncherStateObjBuilder::get_topic_name()
{
  return docbox::DeviceDriverLauncherStateObjTopic;
}
