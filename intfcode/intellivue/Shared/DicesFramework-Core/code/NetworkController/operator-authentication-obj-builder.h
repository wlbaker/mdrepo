#ifndef OPERATOR_AUTHENTICATION_OBJ_BUILDER_H_
#define OPERATOR_AUTHENTICATION_OBJ_BUILDER_H_

#include "operator-authentication-type-builder.h"

class OperatorAuthenticationObjBuilder : public OperatorAuthenticationTypeBuilder
{
public:
  OperatorAuthenticationObjBuilder();
  ~OperatorAuthenticationObjBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationObjBuilder(const OperatorAuthenticationObjBuilder &other);
  OperatorAuthenticationObjBuilder &operator=(const OperatorAuthenticationObjBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_OBJ_BUILDER_H_
