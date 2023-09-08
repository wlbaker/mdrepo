#ifndef OBSERVATION_COMPONENT_BUILDER_H
#define OBSERVATION_COMPONENT_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ObservationComponentBuilder : public AbstractTopicBuilder
{
public:
  friend class ObservationComponentBuilderUnitTest;

  ObservationComponentBuilder();
  ~ObservationComponentBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ObservationComponentBuilder(const ObservationComponentBuilder &other);
  ObservationComponentBuilder &operator=(const ObservationComponentBuilder &other);
};

#endif // OBSERVATION_COMPONENT_BUILDER_H
