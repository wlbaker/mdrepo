#ifndef CARE_PLAN_BUILDER_H
#define CARE_PLAN_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class CarePlanBuilder : public AbstractTopicBuilder
{
public:
  friend class CarePlanBuilderUnitTest;

  CarePlanBuilder();
  ~CarePlanBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  CarePlanBuilder(const CarePlanBuilder &other);
  CarePlanBuilder &operator=(const CarePlanBuilder &other);
};

#endif // KEYED_OCTET_BUILDER_H
