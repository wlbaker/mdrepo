#ifndef NUMERIC_CALC_OBS_VALUE_BUILDER_H
#define NUMERIC_CALC_OBS_VALUE_BUILDER_H

#include "numeric-obs-value-type-builder.h"

class NumericCalcObsValueBuilder : public NumericObsValueTypeBuilder
{
public:
  NumericCalcObsValueBuilder();
  ~NumericCalcObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericCalcObsValueBuilder(const NumericCalcObsValueBuilder &other);
  NumericCalcObsValueBuilder &operator=(const NumericCalcObsValueBuilder &other);
};

#endif // NUMERIC_CALC_OBS_VALUE_BUILDER_H
