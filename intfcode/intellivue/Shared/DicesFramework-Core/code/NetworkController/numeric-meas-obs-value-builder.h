#ifndef NUMERIC_MEAS_OBS_VALUE_BUILDER_H
#define NUMERIC_MEAS_OBS_VALUE_BUILDER_H

#include "numeric-obs-value-type-builder.h"

class NumericMeasObsValueBuilder : public NumericObsValueTypeBuilder
{
public:
  NumericMeasObsValueBuilder();
  ~NumericMeasObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericMeasObsValueBuilder(const NumericMeasObsValueBuilder &other);
  NumericMeasObsValueBuilder &operator=(const NumericMeasObsValueBuilder &other);
};

#endif // NUMERIC_MEAS_OBS_VALUE_BUILDER_H
