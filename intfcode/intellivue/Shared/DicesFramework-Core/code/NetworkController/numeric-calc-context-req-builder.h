#ifndef NUMERIC_CALC_CONTEXT_REQ_BUILDER_H
#define NUMERIC_CALC_CONTEXT_REQ_BUILDER_H

#include "numeric-context-type-builder.h"

class NumericCalcContextReqBuilder : public NumericContextTypeBuilder
{
public:
  NumericCalcContextReqBuilder();
  ~NumericCalcContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  NumericCalcContextReqBuilder(const NumericCalcContextReqBuilder &other);
  NumericCalcContextReqBuilder &operator=(const NumericCalcContextReqBuilder &other);
};

#endif // NUMERIC_CALC_CONTEXT_REQ_BUILDER_H
