#ifndef OPERATOR_AUTHENTICATION_ERROR_TYPE_BUILDER_H_
#define OPERATOR_AUTHENTICATION_ERROR_TYPE_BUILDER_H_

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class OperatorAuthenticationErrorTypeBuilder : public AbstractTopicBuilder
{
public:
  OperatorAuthenticationErrorTypeBuilder();
  ~OperatorAuthenticationErrorTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorAuthenticationErrorTypeBuilder(const OperatorAuthenticationErrorTypeBuilder &other);
  OperatorAuthenticationErrorTypeBuilder &operator=(const OperatorAuthenticationErrorTypeBuilder &other);
};

#endif // OPERATOR_AUTHENTICATION_ERROR_TYPE_BUILDER_H
