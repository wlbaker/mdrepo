#ifndef RTSA_SETT_OBS_VALUE_BUILDER_H
#define RTSA_SETT_OBS_VALUE_BUILDER_H

#include "rtsa-obs-value-type-builder.h"

class RTSASettObsValueBuilder : public RTSAObsValueTypeBuilder
{
public:
  RTSASettObsValueBuilder();
  ~RTSASettObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSASettObsValueBuilder(const RTSASettObsValueBuilder &other);
  RTSASettObsValueBuilder &operator=(const RTSASettObsValueBuilder &other);
};

#endif // RTSA_SETT_OBS_VALUE_BUILDER_H
