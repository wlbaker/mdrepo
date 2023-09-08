#ifndef DIAGNOSIS_BUILDER_H
#define DIAGNOSIS_BUILDER_H

#include "diagnosis-type-builder.h"

enum class DicesRcEntityBuilder;

class DiagnosisBuilder : public DiagnosisTypeBuilder
{
public:
  DiagnosisBuilder();
  ~DiagnosisBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DiagnosisBuilder(const DiagnosisBuilder &other);
  DiagnosisBuilder &operator=(const DiagnosisBuilder &other);
};

#endif // DIAGNOSIS_BUILDER_H
