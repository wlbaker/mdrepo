#ifndef RTSA_CALC_OBS_VALUE_BUILDER_H
#define RTSA_CALC_OBS_VALUE_BUILDER_H

#include "rtsa-obs-value-type-builder.h"

class RTSACalcObsValueBuilder : public RTSAObsValueTypeBuilder
{
public:
  RTSACalcObsValueBuilder();
  ~RTSACalcObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSACalcObsValueBuilder(const RTSACalcObsValueBuilder &other);
  RTSACalcObsValueBuilder &operator=(const RTSACalcObsValueBuilder &other);
};

#endif // RTSA_CALC_OBS_VALUE_BUILDER_H
