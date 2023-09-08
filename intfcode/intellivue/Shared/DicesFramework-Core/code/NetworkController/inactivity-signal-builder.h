#ifndef INACTIVITY_SIGNAL_BUILDER_H
#define INACTIVITY_SIGNAL_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class InactivitySignalBuilder : public AbstractTopicBuilder
{
public:
  InactivitySignalBuilder();
  ~InactivitySignalBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  InactivitySignalBuilder(const InactivitySignalBuilder &other);
  InactivitySignalBuilder &operator=(const InactivitySignalBuilder &other);
};

#endif // INACTIVITY_SIGNAL_BUILDER_H