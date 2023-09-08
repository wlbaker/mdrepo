#ifndef ENUM_CALC_CONTEXT_BUILDER_H
#define ENUM_CALC_CONTEXT_BUILDER_H

#include "enum-context-type-builder.h"

class EnumCalcContextBuilder : public EnumContextTypeBuilder
{
public:
  EnumCalcContextBuilder();
  ~EnumCalcContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumCalcContextBuilder(const EnumCalcContextBuilder &other);
  EnumCalcContextBuilder &operator=(const EnumCalcContextBuilder &other);
};

#endif // ENUM_CALC_CONTEXT_BUILDER_H
