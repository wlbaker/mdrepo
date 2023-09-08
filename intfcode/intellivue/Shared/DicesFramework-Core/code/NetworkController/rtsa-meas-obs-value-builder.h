#ifndef RTSA_MEAS_OBS_VALUE_BUILDER_H
#define RTSA_MEAS_OBS_VALUE_BUILDER_H

#include "rtsa-obs-value-type-builder.h"

class RTSAMeasObsValueBuilder : public RTSAObsValueTypeBuilder
{
public:
  RTSAMeasObsValueBuilder();
  ~RTSAMeasObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSAMeasObsValueBuilder(const RTSAMeasObsValueBuilder &other);
  RTSAMeasObsValueBuilder &operator=(const RTSAMeasObsValueBuilder &other);
};

#endif // RTSA_MEAS_OBS_VALUE_BUILDER_H
