#include "clinical-note-bundle-builder.h"

#include <ndds_namespace_cpp.h>
#include <cnoteSupport.h>

#include "rc-entity-builder.h"

ClinicalNoteBundleBuilder::ClinicalNoteBundleBuilder() :
  AbstractTopicBuilder()
{

}

ClinicalNoteBundleBuilder::~ClinicalNoteBundleBuilder()
{

}

DicesRcEntityBuilder ClinicalNoteBundleBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ClinicalNoteBundleTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ClinicalNoteBundleBuilder::get_type_name()
{
  return ice::ClinicalNoteBundleTypeSupport::get_type_name();
}

const std::string ClinicalNoteBundleBuilder::get_topic_name()
{
  return ice::ClinicalNoteBundleTopic;
}
