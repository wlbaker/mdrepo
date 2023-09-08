#ifndef RTSA_CALC_CONTEXT_REQ_BUILDER_H
#define RTSA_CALC_CONTEXT_REQ_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSACalcContextReqBuilder : public RTSAContextTypeBuilder
{
public:
  RTSACalcContextReqBuilder();
  ~RTSACalcContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSACalcContextReqBuilder(const RTSACalcContextReqBuilder &other);
  RTSACalcContextReqBuilder &operator=(const RTSACalcContextReqBuilder &other);
};

#endif // RTSA_CALC_CONTEXT_REQ_BUILDER_H
