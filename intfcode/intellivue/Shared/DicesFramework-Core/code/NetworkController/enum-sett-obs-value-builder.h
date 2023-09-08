#ifndef ENUM_SETT_OBS_VALUE_BUILDER_H
#define ENUM_SETT_OBS_VALUE_BUILDER_H

#include "enum-obs-value-type-builder.h"

class EnumSettObsValueBuilder : public EnumObsValueTypeBuilder
{
public:
  EnumSettObsValueBuilder();
  ~EnumSettObsValueBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumSettObsValueBuilder(const EnumSettObsValueBuilder &other);
  EnumSettObsValueBuilder &operator=(const EnumSettObsValueBuilder &other);
};

#endif // ENUM_SETT_OBS_VALUE_BUILDER_H
