#include "device-driver-state-obj-builder.h"
#include <docboxSupport.h>

DeviceDriverStateObjBuilder::DeviceDriverStateObjBuilder() :
  DeviceDriverStateTypeBuilder()
{

}

DeviceDriverStateObjBuilder::~DeviceDriverStateObjBuilder()
{

}

const std::string DeviceDriverStateObjBuilder::get_topic_name()
{
  return docbox::DeviceDriverStateObjTopic;
}
