#ifndef ENUM_MEAS_OBS_VALUE_BUILDER_H
#define ENUM_MEAS_OBS_VALUE_BUILDER_H

#include "enum-obs-value-type-builder.h"

class EnumMeasObsValueBuilder : public EnumObsValueTypeBuilder
{
public:
  EnumMeasObsValueBuilder();
  ~EnumMeasObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumMeasObsValueBuilder(const EnumMeasObsValueBuilder &other);
  EnumMeasObsValueBuilder &operator=(const EnumMeasObsValueBuilder &other);
};

#endif // ENUM_MEAS_OBS_VALUE_BUILDER_H
