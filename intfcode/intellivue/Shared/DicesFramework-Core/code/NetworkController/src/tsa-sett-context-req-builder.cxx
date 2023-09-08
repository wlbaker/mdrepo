#include "tsa-sett-context-req-builder.h"
#include <tsaSupport.h>

TSASettContextReqBuilder::TSASettContextReqBuilder() :
  TSAContextTypeBuilder()
{

}

TSASettContextReqBuilder::~TSASettContextReqBuilder()
{

}

const std::string TSASettContextReqBuilder::get_topic_name()
{
  return ice::TSASettContextReqTopic;
}
