#ifndef OPERATOR_AUTHENTICATION_TYPE_BUILDER_H_
#define OPERATOR_AUTHENTICATION_TYPE_BUILDER_H_

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class OperatorAuthenticationTypeBuilder : public AbstractTopicBuilder
{
public:
  OperatorAuthenticationTypeBuilder();
  ~OperatorAuthenticationTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationTypeBuilder(const OperatorAuthenticationTypeBuilder &other);
  OperatorAuthenticationTypeBuilder &operator=(const OperatorAuthenticationTypeBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_TYPE_BUILDER_H
