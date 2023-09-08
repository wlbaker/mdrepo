#include "device-driver-state-builder.h"
#include <docboxSupport.h>

DeviceDriverStateBuilder::DeviceDriverStateBuilder() :
  DeviceDriverStateTypeBuilder()
{

}

DeviceDriverStateBuilder::~DeviceDriverStateBuilder()
{

}

const std::string DeviceDriverStateBuilder::get_topic_name()
{
  return docbox::DeviceDriverStateTopic;
}
