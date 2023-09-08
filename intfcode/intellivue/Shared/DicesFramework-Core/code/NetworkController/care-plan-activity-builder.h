#ifndef CARE_PLAN_ACTIVITY_BUILDER_H
#define CARE_PLAN_ACTIVITY_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class CarePlanActivityBuilder : public AbstractTopicBuilder
{
public:
  friend class CarePlanActivityBuilderUnitTest;

  CarePlanActivityBuilder();
  ~CarePlanActivityBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  CarePlanActivityBuilder(const CarePlanActivityBuilder &other);
  CarePlanActivityBuilder &operator=(const CarePlanActivityBuilder &other);
};

#endif // KEYED_OCTET_BUILDER_H
