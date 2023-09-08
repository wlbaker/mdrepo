#include "driver-manager-state-req-builder.h"
#include <docboxSupport.h>

DriverManagerStateReqBuilder::DriverManagerStateReqBuilder() :
  DriverManagerStateTypeBuilder()
{

}

DriverManagerStateReqBuilder::~DriverManagerStateReqBuilder()
{

}

const std::string DriverManagerStateReqBuilder::get_topic_name()
{
  return docbox::DriverManagerStateReqTopic;
}
