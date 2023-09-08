#include "numeric-sett-obs-value-req-builder.h"
#include <numericSupport.h>

NumericSettObsValueReqBuilder::NumericSettObsValueReqBuilder() :
  NumericObsValueTypeBuilder()
{

}

NumericSettObsValueReqBuilder::~NumericSettObsValueReqBuilder()
{

}

const std::string NumericSettObsValueReqBuilder::get_topic_name()
{
  return ice::NumericSettObservedValueReqTopic;
}
