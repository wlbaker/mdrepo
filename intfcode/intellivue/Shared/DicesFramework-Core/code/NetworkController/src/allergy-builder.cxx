#include "allergy-builder.h"

#include <ndds_namespace_cpp.h>
#include <allergySupport.h>

#include "rc-entity-builder.h"

AllergyBuilder::AllergyBuilder() :
  AllergyTypeBuilder()
{

}

AllergyBuilder::~AllergyBuilder()
{

}

const std::string AllergyBuilder::get_topic_name()
{
  return ice::AllergyTopic;
}
