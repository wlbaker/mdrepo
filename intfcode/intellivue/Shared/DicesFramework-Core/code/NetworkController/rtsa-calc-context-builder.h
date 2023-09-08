#ifndef RTSA_CALC_CONTEXT_BUILDER_H
#define RTSA_CALC_CONTEXT_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSACalcContextBuilder : public RTSAContextTypeBuilder
{
public:
  RTSACalcContextBuilder();
  ~RTSACalcContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSACalcContextBuilder(const RTSACalcContextBuilder &other);
  RTSACalcContextBuilder &operator=(const RTSACalcContextBuilder &other);
};

#endif // RTSA_CALC_CONTEXT_BUILDER_H
