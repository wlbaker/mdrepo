#ifndef ENUM_OBS_VALUE_TYPE_BUILDER_H
#define ENUM_OBS_VALUE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class EnumObsValueTypeBuilder : public AbstractTopicBuilder
{
public:
  EnumObsValueTypeBuilder();
  ~EnumObsValueTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumObsValueTypeBuilder(const EnumObsValueTypeBuilder &other);
  EnumObsValueTypeBuilder &operator=(const EnumObsValueTypeBuilder &other);
};

#endif // ENUM_OBS_VALUE_TYPE_BUILDER_H
