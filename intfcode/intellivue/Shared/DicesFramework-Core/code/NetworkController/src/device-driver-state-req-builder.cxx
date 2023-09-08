#include "device-driver-state-req-builder.h"
#include <docboxSupport.h>

DeviceDriverStateReqBuilder::DeviceDriverStateReqBuilder() :
  DeviceDriverStateTypeBuilder()
{

}

DeviceDriverStateReqBuilder::~DeviceDriverStateReqBuilder()
{

}

const std::string DeviceDriverStateReqBuilder::get_topic_name()
{
  return docbox::DeviceDriverStateReqTopic;
}
