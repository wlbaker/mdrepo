#include "diagnosis-builder.h"
#include "exprSupport.h"

DiagnosisBuilder::DiagnosisBuilder() :
  DiagnosisTypeBuilder()
{

}

DiagnosisBuilder::~DiagnosisBuilder()
{

}

const std::string DiagnosisBuilder::get_topic_name()
{
  return expr::DiagnosisTopic;
}
