#ifndef OPERATOR_BUILDER_H
#define OPERATOR_BUILDER_H

#include "operator-type-builder.h"

class OperatorBuilder : public OperatorTypeBuilder
{
public:
  OperatorBuilder();
  ~OperatorBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  OperatorBuilder(const OperatorBuilder &other);
  OperatorBuilder &operator=(const OperatorBuilder &other);
};

#endif // OPERATOR_BUILDER_H
