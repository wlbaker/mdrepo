#ifndef OPERATOR_AUTHENTICATION_BUILDER_H_
#define OPERATOR_AUTHENTICATION_BUILDER_H_

#include "operator-authentication-type-builder.h"

class OperatorAuthenticationBuilder : public OperatorAuthenticationTypeBuilder
{
public:
  OperatorAuthenticationBuilder();
  ~OperatorAuthenticationBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationBuilder(const OperatorAuthenticationBuilder &other);
  OperatorAuthenticationBuilder &operator=(const OperatorAuthenticationBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_BUILDER_H_
