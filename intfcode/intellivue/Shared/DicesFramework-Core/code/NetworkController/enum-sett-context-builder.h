#ifndef ENUM_SETT_CONTEXT_BUILDER_H
#define ENUM_SETT_CONTEXT_BUILDER_H

#include "enum-context-type-builder.h"

class EnumSettContextBuilder : public EnumContextTypeBuilder
{
public:
  EnumSettContextBuilder();
  ~EnumSettContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumSettContextBuilder(const EnumSettContextBuilder &other);
  EnumSettContextBuilder &operator=(const EnumSettContextBuilder &other);
};

#endif // ENUM_SETT_CONTEXT_BUILDER_H
