#ifndef ENUM_CALC_CONTEXT_REQ_BUILDER_H
#define ENUM_CALC_CONTEXT_REQ_BUILDER_H

#include "enum-context-type-builder.h"

class EnumCalcContextReqBuilder : public EnumContextTypeBuilder
{
public:
  EnumCalcContextReqBuilder();
  ~EnumCalcContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  EnumCalcContextReqBuilder(const EnumCalcContextReqBuilder &other);
  EnumCalcContextReqBuilder &operator=(const EnumCalcContextReqBuilder &other);
};

#endif // ENUM_CALC_CONTEXT_REQ_BUILDER_H
