#ifndef DIAGNOSIS_REQ_BUILDER_H
#define DIAGNOSIS_REQ_BUILDER_H

#include "diagnosis-type-builder.h"

enum class DicesRcEntityBuilder;

class DiagnosisReqBuilder : public DiagnosisTypeBuilder
{
public:
  DiagnosisReqBuilder();
  ~DiagnosisReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DiagnosisReqBuilder(const DiagnosisReqBuilder &other);
  DiagnosisReqBuilder &operator=(const DiagnosisReqBuilder &other);
};

#endif // DIAGNOSIS_REQ_BUILDER_H
