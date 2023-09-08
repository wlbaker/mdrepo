#include "module-display-state-builder.h"
#include <docboxSupport.h>

ModuleDisplayStateBuilder::ModuleDisplayStateBuilder() :
  ModuleDisplayStateTypeBuilder()
{

}

ModuleDisplayStateBuilder::~ModuleDisplayStateBuilder()
{

}

const std::string ModuleDisplayStateBuilder::get_topic_name()
{
  return docbox::ModuleDisplayStateTopic;
}
