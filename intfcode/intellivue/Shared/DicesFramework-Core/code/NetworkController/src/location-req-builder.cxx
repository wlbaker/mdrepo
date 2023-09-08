#include "location-req-builder.h"
#include "locationSupport.h"

LocationReqBuilder::LocationReqBuilder() :
  LocationTypeBuilder()
{

}

LocationReqBuilder::~LocationReqBuilder()
{

}

const std::string LocationReqBuilder::get_topic_name()
{
  return ice::LocationReqTopic;
}
