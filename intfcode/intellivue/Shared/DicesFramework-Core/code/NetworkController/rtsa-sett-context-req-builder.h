#ifndef RTSA_SETT_CONTEXT_REQ_BUILDER_H
#define RTSA_SETT_CONTEXT_REQ_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSASettContextReqBuilder : public RTSAContextTypeBuilder
{
public:
  RTSASettContextReqBuilder();
  ~RTSASettContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSASettContextReqBuilder(const RTSASettContextReqBuilder &other);
  RTSASettContextReqBuilder &operator=(const RTSASettContextReqBuilder &other);
};

#endif // RTSA_SETT_CONTEXT_REQ_BUILDER_H
