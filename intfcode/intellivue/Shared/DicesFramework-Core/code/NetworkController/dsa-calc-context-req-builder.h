#ifndef DSA_CALC_CONTEXT_REQ_BUILDER_H
#define DSA_CALC_CONTEXT_REQ_BUILDER_H

#include "dsa-context-type-builder.h"

class DSACalcContextReqBuilder : public DSAContextTypeBuilder
{
public:
  DSACalcContextReqBuilder();
  ~DSACalcContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSACalcContextReqBuilder(const DSACalcContextReqBuilder &other);
  DSACalcContextReqBuilder &operator=(const DSACalcContextReqBuilder &other);
};

#endif // DSA_CALC_CONTEXT_REQ_BUILDER_H
