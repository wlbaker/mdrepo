#ifndef OPERATOR_AUTHENTICATION_REQ_BUILDER_H_
#define OPERATOR_AUTHENTICATION_REQ_BUILDER_H_

#include "operator-authentication-type-builder.h"

class OperatorAuthenticationReqBuilder : public OperatorAuthenticationTypeBuilder
{
public:
  OperatorAuthenticationReqBuilder();
  ~OperatorAuthenticationReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationReqBuilder(const OperatorAuthenticationReqBuilder &other);
  OperatorAuthenticationReqBuilder &operator=(const OperatorAuthenticationReqBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_REQ_BUILDER_H_
