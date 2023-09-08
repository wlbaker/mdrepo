#ifndef DIAGNOSIS_TYPE_BUILDER_H
#define DIAGNOSIS_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DiagnosisTypeBuilder : public AbstractTopicBuilder
{
public:
  DiagnosisTypeBuilder();
  ~DiagnosisTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DiagnosisTypeBuilder(const DiagnosisTypeBuilder &other);
  DiagnosisTypeBuilder &operator=(const DiagnosisTypeBuilder &other);
};

#endif // DIAGNOSIS_TYPE_BUILDER_H
