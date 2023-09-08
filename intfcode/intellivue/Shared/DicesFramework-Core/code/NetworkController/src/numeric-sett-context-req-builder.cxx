#include "numeric-sett-context-req-builder.h"
#include <numericSupport.h>

NumericSettContextReqBuilder::NumericSettContextReqBuilder() :
  NumericContextTypeBuilder()
{

}

NumericSettContextReqBuilder::~NumericSettContextReqBuilder()
{

}

const std::string NumericSettContextReqBuilder::get_topic_name()
{
  return ice::NumericSettContextReqTopic;
}
