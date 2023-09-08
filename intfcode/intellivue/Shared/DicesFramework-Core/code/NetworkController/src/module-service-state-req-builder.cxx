#include "module-service-state-req-builder.h"
#include <docboxSupport.h>

ModuleServiceStateReqBuilder::ModuleServiceStateReqBuilder() :
  ModuleServiceStateTypeBuilder()
{

}

ModuleServiceStateReqBuilder::~ModuleServiceStateReqBuilder()
{

}

const std::string ModuleServiceStateReqBuilder::get_topic_name()
{
  return docbox::ModuleServiceStateReqTopic;
}
