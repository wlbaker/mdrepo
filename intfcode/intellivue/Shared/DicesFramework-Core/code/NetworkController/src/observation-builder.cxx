#include "observation-builder.h"

#include <ndds_namespace_cpp.h>
#include <diagnosticsSupport.h>

#include "rc-entity-builder.h"

ObservationBuilder::ObservationBuilder() :
  AbstractTopicBuilder()
{

}

ObservationBuilder::~ObservationBuilder()
{

}

DicesRcEntityBuilder ObservationBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ObservationTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ObservationBuilder::get_type_name()
{
  return ice::ObservationTypeSupport::get_type_name();
}

const std::string ObservationBuilder::get_topic_name()
{
  return ice::ObservationTopic;
}
