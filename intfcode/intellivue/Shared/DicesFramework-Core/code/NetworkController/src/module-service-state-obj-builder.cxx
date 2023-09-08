#include "module-service-state-obj-builder.h"
#include <docboxSupport.h>

ModuleServiceStateObjBuilder::ModuleServiceStateObjBuilder() :
  ModuleServiceStateTypeBuilder()
{

}

ModuleServiceStateObjBuilder::~ModuleServiceStateObjBuilder()
{

}

const std::string ModuleServiceStateObjBuilder::get_topic_name()
{
  return docbox::ModuleServiceStateObjTopic;
}
