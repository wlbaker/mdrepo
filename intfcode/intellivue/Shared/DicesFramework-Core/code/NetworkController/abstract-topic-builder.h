#ifndef ABSTRACTTOPICBUILDER_H
#define ABSTRACTTOPICBUILDER_H

#include "abstract-entity-builder.h"

#include <string>

enum class DicesRcEntityBuilder;

class AbstractTopicBuilder : public AbstractEntityBuilder
{
public:
  AbstractTopicBuilder();
  ~AbstractTopicBuilder();

  DicesRcEntityBuilder construct_topic();

protected:
  const std::string get_library_name();
  const std::string get_qos_profile();

private:
  // Disallow use of implicitly generated member functions:
  AbstractTopicBuilder(const AbstractTopicBuilder &other);
  AbstractTopicBuilder &operator=(const AbstractTopicBuilder &other);
};

#endif // ABSTRACTTOPICBUILDER_H
