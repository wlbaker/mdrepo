#ifndef NUMERIC_SETT_OBS_VALUE_BUILDER_H
#define NUMERIC_SETT_OBS_VALUE_BUILDER_H

#include "numeric-obs-value-type-builder.h"

class NumericSettObsValueBuilder : public NumericObsValueTypeBuilder
{
public:
  NumericSettObsValueBuilder();
  ~NumericSettObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericSettObsValueBuilder(const NumericSettObsValueBuilder &other);
  NumericSettObsValueBuilder &operator=(const NumericSettObsValueBuilder &other);
};

#endif // NUMERIC_SETT_OBS_VALUE_BUILDER_H
