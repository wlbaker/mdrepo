#include "driver-manager-state-builder.h"
#include <docboxSupport.h>

DriverManagerStateBuilder::DriverManagerStateBuilder() :
  DriverManagerStateTypeBuilder()
{

}

DriverManagerStateBuilder::~DriverManagerStateBuilder()
{

}

const std::string DriverManagerStateBuilder::get_topic_name()
{
  return docbox::DriverManagerStateTopic;
}
