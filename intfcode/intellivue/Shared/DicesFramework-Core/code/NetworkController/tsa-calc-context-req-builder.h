#ifndef TSA_CALC_CONTEXT_REQ_BUILDER_H
#define TSA_CALC_CONTEXT_REQ_BUILDER_H

#include "tsa-context-type-builder.h"

class TSACalcContextReqBuilder : public TSAContextTypeBuilder
{
public:
  TSACalcContextReqBuilder();
  ~TSACalcContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TSACalcContextReqBuilder(const TSACalcContextReqBuilder &other);
  TSACalcContextReqBuilder &operator=(const TSACalcContextReqBuilder &other);
};

#endif // TSA_CALC_CONTEXT_REQ_BUILDER_H
