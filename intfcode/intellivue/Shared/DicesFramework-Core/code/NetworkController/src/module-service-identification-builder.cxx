#include "module-service-identification-builder.h"
#include <docboxSupport.h>

ModuleServiceIdentificationBuilder::ModuleServiceIdentificationBuilder() :
  ModuleServiceIdentificationTypeBuilder()
{

}

ModuleServiceIdentificationBuilder::~ModuleServiceIdentificationBuilder()
{

}

const std::string ModuleServiceIdentificationBuilder::get_topic_name()
{
  return docbox::ModuleServiceIdentificationTopic;
}
