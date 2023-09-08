#include "module-service-identification-req-builder.h"
#include <docboxSupport.h>

ModuleServiceIdentificationReqBuilder::ModuleServiceIdentificationReqBuilder() :
  ModuleServiceIdentificationTypeBuilder()
{

}

ModuleServiceIdentificationReqBuilder::~ModuleServiceIdentificationReqBuilder()
{

}

const std::string ModuleServiceIdentificationReqBuilder::get_topic_name()
{
  return docbox::ModuleServiceIdentificationReqTopic;
}
