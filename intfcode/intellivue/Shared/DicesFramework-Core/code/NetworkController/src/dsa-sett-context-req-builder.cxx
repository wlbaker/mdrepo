#include "dsa-sett-context-req-builder.h"
#include <dsaSupport.h>

DSASettContextReqBuilder::DSASettContextReqBuilder() :
  DSAContextTypeBuilder()
{

}

DSASettContextReqBuilder::~DSASettContextReqBuilder()
{

}

const std::string DSASettContextReqBuilder::get_topic_name()
{
  return ice::DSASettContextReqTopic;
}
