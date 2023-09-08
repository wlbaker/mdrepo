#include "numeric-sett-obs-value-builder.h"
#include <numericSupport.h>

NumericSettObsValueBuilder::NumericSettObsValueBuilder() :
  NumericObsValueTypeBuilder()
{

}

NumericSettObsValueBuilder::~NumericSettObsValueBuilder()
{

}

const std::string NumericSettObsValueBuilder::get_topic_name()
{
  return ice::NumericSettObservedValueTopic;
}
