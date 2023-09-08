#ifndef TSA_CALC_OBS_VALUE_BUILDER_H
#define TSA_CALC_OBS_VALUE_BUILDER_H

#include "tsa-obs-value-type-builder.h"

class TSACalcObsValueBuilder : public TSAObsValueTypeBuilder
{
public:
  TSACalcObsValueBuilder();
  ~TSACalcObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSACalcObsValueBuilder(const TSACalcObsValueBuilder &other);
  TSACalcObsValueBuilder &operator=(const TSACalcObsValueBuilder &other);
};

#endif // TSA_CALC_OBS_VALUE_BUILDER_H
