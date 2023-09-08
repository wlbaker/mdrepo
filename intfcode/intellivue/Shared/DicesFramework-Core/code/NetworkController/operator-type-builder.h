#ifndef OPERATOR_TYPE_BUILDER_H
#define OPERATOR_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class OperatorTypeBuilder : public AbstractTopicBuilder
{
public:
  OperatorTypeBuilder();
  ~OperatorTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorTypeBuilder(const OperatorTypeBuilder &other);
  OperatorTypeBuilder &operator=(const OperatorTypeBuilder &other);
};

#endif // OPERATOR_TYPE_BUILDER_H
