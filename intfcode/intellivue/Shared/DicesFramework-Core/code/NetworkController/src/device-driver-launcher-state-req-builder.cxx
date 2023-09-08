#include "device-driver-launcher-state-req-builder.h"
#include <docboxSupport.h>

DeviceDriverLauncherStateReqBuilder::DeviceDriverLauncherStateReqBuilder() :
  DeviceDriverLauncherStateTypeBuilder()
{

}

DeviceDriverLauncherStateReqBuilder::~DeviceDriverLauncherStateReqBuilder()
{

}

const std::string DeviceDriverLauncherStateReqBuilder::get_topic_name()
{
  return docbox::DeviceDriverLauncherStateReqTopic;
}
