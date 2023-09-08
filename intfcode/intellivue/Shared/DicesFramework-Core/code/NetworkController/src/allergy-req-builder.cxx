#include "allergy-req-builder.h"

#include <ndds_namespace_cpp.h>
#include <allergySupport.h>

#include "rc-entity-builder.h"

AllergyReqBuilder::AllergyReqBuilder() :
  AllergyTypeBuilder()
{

}

AllergyReqBuilder::~AllergyReqBuilder()
{

}


const std::string AllergyReqBuilder::get_topic_name()
{
  return ice::AllergyReqTopic;
}
