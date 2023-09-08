#include "tsa-sett-obs-value-builder.h"
#include <tsaSupport.h>

TSASettObsValueBuilder::TSASettObsValueBuilder() :
  TSAObsValueTypeBuilder()
{

}

TSASettObsValueBuilder::~TSASettObsValueBuilder()
{

}

const std::string TSASettObsValueBuilder::get_topic_name()
{
  return ice::TSASettObservedValueTopic;
}
