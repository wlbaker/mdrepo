#ifndef RTSA_MEAS_CONTEXT_REQ_BUILDER_H
#define RTSA_MEAS_CONTEXT_REQ_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSAMeasContextReqBuilder : public RTSAContextTypeBuilder
{
public:
  RTSAMeasContextReqBuilder();
  ~RTSAMeasContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSAMeasContextReqBuilder(const RTSAMeasContextReqBuilder &other);
  RTSAMeasContextReqBuilder &operator=(const RTSAMeasContextReqBuilder &other);
};

#endif // RTSA_MEAS_CONTEXT_REQ_BUILDER_H
