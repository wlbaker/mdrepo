#ifndef RTSA_SETT_CONTEXT_BUILDER_H
#define RTSA_SETT_CONTEXT_BUILDER_H

#include "rtsa-context-type-builder.h"

class RTSASettContextBuilder : public RTSAContextTypeBuilder
{
public:
  RTSASettContextBuilder();
  ~RTSASettContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  RTSASettContextBuilder(const RTSASettContextBuilder &other);
  RTSASettContextBuilder &operator=(const RTSASettContextBuilder &other);
};

#endif // RTSA_SETT_CONTEXT_BUILDER_H
