#ifndef ENUM_CALC_OBS_VALUE_BUILDER_H
#define ENUM_CALC_OBS_VALUE_BUILDER_H

#include "enum-obs-value-type-builder.h"

class EnumCalcObsValueBuilder : public EnumObsValueTypeBuilder
{
public:
  EnumCalcObsValueBuilder();
  ~EnumCalcObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumCalcObsValueBuilder(const EnumCalcObsValueBuilder &other);
  EnumCalcObsValueBuilder &operator=(const EnumCalcObsValueBuilder &other);
};

#endif // ENUM_CALC_OBS_VALUE_BUILDER_H
