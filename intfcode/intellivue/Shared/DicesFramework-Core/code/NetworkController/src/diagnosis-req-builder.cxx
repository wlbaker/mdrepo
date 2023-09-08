#include "diagnosis-req-builder.h"
#include "exprSupport.h"

DiagnosisReqBuilder::DiagnosisReqBuilder() :
  DiagnosisTypeBuilder()
{

}

DiagnosisReqBuilder::~DiagnosisReqBuilder()
{

}

const std::string DiagnosisReqBuilder::get_topic_name()
{
  return expr::DiagnosisReqTopic;
}
