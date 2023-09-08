#ifndef DSA_SETT_CONTEXT_REQ_BUILDER_H
#define DSA_SETT_CONTEXT_REQ_BUILDER_H

#include "dsa-context-type-builder.h"

class DSASettContextReqBuilder : public DSAContextTypeBuilder
{
public:
  DSASettContextReqBuilder();
  ~DSASettContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  DSASettContextReqBuilder(const DSASettContextReqBuilder &other);
  DSASettContextReqBuilder &operator=(const DSASettContextReqBuilder &other);
};

#endif // DSA_SETT_CONTEXT_REQ_BUILDER_H
