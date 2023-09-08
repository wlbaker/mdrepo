#include "module-display-state-req-builder.h"
#include <docboxSupport.h>

ModuleDisplayStateReqBuilder::ModuleDisplayStateReqBuilder() :
  ModuleDisplayStateTypeBuilder()
{

}

ModuleDisplayStateReqBuilder::~ModuleDisplayStateReqBuilder()
{

}

const std::string ModuleDisplayStateReqBuilder::get_topic_name()
{
  return docbox::ModuleDisplayStateReqTopic;
}
