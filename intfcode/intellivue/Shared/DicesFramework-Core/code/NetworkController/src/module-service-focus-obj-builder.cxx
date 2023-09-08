#include "module-service-focus-obj-builder.h"
#include <docboxSupport.h>

ModuleServiceFocusObjBuilder::ModuleServiceFocusObjBuilder() :
  ModuleServiceFocusTypeBuilder()
{

}

ModuleServiceFocusObjBuilder::~ModuleServiceFocusObjBuilder()
{

}

const std::string ModuleServiceFocusObjBuilder::get_topic_name()
{
  return docbox::ModuleServiceFocusObjTopic;
}
