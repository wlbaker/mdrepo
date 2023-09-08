#ifndef NUMERIC_OBS_VALUE_TYPE_BUILDER_H
#define NUMERIC_OBS_VALUE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class NumericObsValueTypeBuilder : public AbstractTopicBuilder
{
public:
  NumericObsValueTypeBuilder();
  ~NumericObsValueTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericObsValueTypeBuilder(const NumericObsValueTypeBuilder &other);
  NumericObsValueTypeBuilder &operator=(const NumericObsValueTypeBuilder &other);
};

#endif // NUMERIC_OBS_VALUE_TYPE_BUILDER_H
