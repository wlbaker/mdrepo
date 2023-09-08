#include "module-service-state-builder.h"
#include <docboxSupport.h>

ModuleServiceStateBuilder::ModuleServiceStateBuilder() :
  ModuleServiceStateTypeBuilder()
{

}

ModuleServiceStateBuilder::~ModuleServiceStateBuilder()
{

}

const std::string ModuleServiceStateBuilder::get_topic_name()
{
  return docbox::ModuleServiceStateTopic;
}
