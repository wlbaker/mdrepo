#include "dsa-sett-obs-value-builder.h"
#include <dsaSupport.h>

DSASettObsValueBuilder::DSASettObsValueBuilder() :
  DSAObsValueTypeBuilder()
{

}

DSASettObsValueBuilder::~DSASettObsValueBuilder()
{

}

const std::string DSASettObsValueBuilder::get_topic_name()
{
  return ice::DSASettObservedValueTopic;
}
