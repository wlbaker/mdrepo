#ifndef OBSERVATION_BUILDER_H
#define OBSERVATION_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ObservationBuilder : public AbstractTopicBuilder
{
public:
  friend class ObservationBuilderUnitTest;

  ObservationBuilder();
  ~ObservationBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ObservationBuilder(const ObservationBuilder &other);
  ObservationBuilder &operator=(const ObservationBuilder &other);
};

#endif // OBSERVATION_BUILDER_H
