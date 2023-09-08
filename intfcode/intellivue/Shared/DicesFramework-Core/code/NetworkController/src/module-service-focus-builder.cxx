#include "module-service-focus-builder.h"
#include <docboxSupport.h>

ModuleServiceFocusBuilder::ModuleServiceFocusBuilder() :
  ModuleServiceFocusTypeBuilder()
{

}

ModuleServiceFocusBuilder::~ModuleServiceFocusBuilder()
{

}

const std::string ModuleServiceFocusBuilder::get_topic_name()
{
  return docbox::ModuleServiceFocusTopic;
}
