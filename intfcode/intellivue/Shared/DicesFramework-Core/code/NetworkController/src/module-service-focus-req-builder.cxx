#include "module-service-focus-req-builder.h"
#include <docboxSupport.h>

ModuleServiceFocusReqBuilder::ModuleServiceFocusReqBuilder() :
  ModuleServiceFocusTypeBuilder()
{

}

ModuleServiceFocusReqBuilder::~ModuleServiceFocusReqBuilder()
{

}

const std::string ModuleServiceFocusReqBuilder::get_topic_name()
{
  return docbox::ModuleServiceFocusReqTopic;
}
