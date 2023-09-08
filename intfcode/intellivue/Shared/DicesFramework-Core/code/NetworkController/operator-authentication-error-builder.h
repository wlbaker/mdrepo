#ifndef OPERATOR_AUTHENTICATION_ERROR_BUILDER_H_
#define OPERATOR_AUTHENTICATION_ERROR_BUILDER_H_

#include "operator-authentication-error-type-builder.h"

class OperatorAuthenticationErrorBuilder : public OperatorAuthenticationErrorTypeBuilder
{
public:
  OperatorAuthenticationErrorBuilder();
  ~OperatorAuthenticationErrorBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationErrorBuilder(const OperatorAuthenticationErrorBuilder &other);
  OperatorAuthenticationErrorBuilder &operator=(const OperatorAuthenticationErrorBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_ERROR_BUILDER_H_
