#include "location-builder.h"
#include "locationSupport.h"

LocationBuilder::LocationBuilder() :
  LocationTypeBuilder()
{

}

LocationBuilder::~LocationBuilder()
{

}

const std::string LocationBuilder::get_topic_name()
{
  return ice::LocationTopic;
}
