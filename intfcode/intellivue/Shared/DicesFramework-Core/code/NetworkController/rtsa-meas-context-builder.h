#ifndef RTSA_MEAS_CONTEXT_BUILDER_H
#define RTSA_MEAS_CONTEXT_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSAMeasContextBuilder : public RTSAContextTypeBuilder
{
public:
  RTSAMeasContextBuilder();
  ~RTSAMeasContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSAMeasContextBuilder(const RTSAMeasContextBuilder &other);
  RTSAMeasContextBuilder &operator=(const RTSAMeasContextBuilder &other);
};

#endif // RTSA_MEAS_CONTEXT_BUILDER_H
