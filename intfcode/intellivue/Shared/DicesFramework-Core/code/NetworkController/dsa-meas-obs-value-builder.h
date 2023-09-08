#ifndef DSA_MEAS_OBS_VALUE_BUILDER_H
#define DSA_MEAS_OBS_VALUE_BUILDER_H

#include "dsa-obs-value-type-builder.h"

class DSAMeasObsValueBuilder : public DSAObsValueTypeBuilder
{
public:
  DSAMeasObsValueBuilder();
  ~DSAMeasObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSAMeasObsValueBuilder(const DSAMeasObsValueBuilder &other);
  DSAMeasObsValueBuilder &operator=(const DSAMeasObsValueBuilder &other);
};

#endif // DSA_MEAS_OBS_VALUE_BUILDER_H
