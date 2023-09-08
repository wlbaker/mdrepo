#include "clinical-note-builder.h"

#include <ndds_namespace_cpp.h>
#include <cnoteSupport.h>

#include "rc-entity-builder.h"

ClinicalNoteBuilder::ClinicalNoteBuilder() :
  AbstractTopicBuilder()
{

}

ClinicalNoteBuilder::~ClinicalNoteBuilder()
{

}

DicesRcEntityBuilder ClinicalNoteBuilder::register_type()
{
  if(!get_participant())
  {
    return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
  }

  DDS_ReturnCode_t ret_code =
      ice::ClinicalNoteTypeSupport::register_type(
        get_participant(),
        get_type_name().c_str());

  if(ret_code == DDS_RETCODE_OK) return DicesRcEntityBuilder::OK;
  else return DicesRcEntityBuilder::REGISTER_TYPE_FAILED;
}

const std::string ClinicalNoteBuilder::get_type_name()
{
  return ice::ClinicalNoteTypeSupport::get_type_name();
}

const std::string ClinicalNoteBuilder::get_topic_name()
{
  return ice::ClinicalNoteTopic;
}
