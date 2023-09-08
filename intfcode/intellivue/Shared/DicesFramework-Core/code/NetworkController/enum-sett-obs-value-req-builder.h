#ifndef ENUM_SETT_OBS_VALUE_REQ_BUILDER_H
#define ENUM_SETT_OBS_VALUE_REQ_BUILDER_H

#include "enum-obs-value-type-builder.h"

class EnumSettObsValueReqBuilder : public EnumObsValueTypeBuilder
{
public:
  EnumSettObsValueReqBuilder();
  ~EnumSettObsValueReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumSettObsValueReqBuilder(const EnumSettObsValueReqBuilder &other);
  EnumSettObsValueReqBuilder &operator=(const EnumSettObsValueReqBuilder &other);
};

#endif // ENUM_SETT_OBS_VALUE_REQ_BUILDER_H
