#ifndef TSA_MEAS_OBS_VALUE_BUILDER_H
#define TSA_MEAS_OBS_VALUE_BUILDER_H

#include "tsa-obs-value-type-builder.h"

class TSAMeasObsValueBuilder : public TSAObsValueTypeBuilder
{
public:
  TSAMeasObsValueBuilder();
  ~TSAMeasObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSAMeasObsValueBuilder(const TSAMeasObsValueBuilder &other);
  TSAMeasObsValueBuilder &operator=(const TSAMeasObsValueBuilder &other);
};

#endif // TSA_MEAS_OBS_VALUE_BUILDER_H
