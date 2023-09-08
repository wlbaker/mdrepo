#ifndef REMINDERSIGNALBUILDER_H
#define REMINDERSIGNALBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ReminderSignalBuilder : public AbstractTopicBuilder
{
public:
  ReminderSignalBuilder();
  ~ReminderSignalBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ReminderSignalBuilder(const ReminderSignalBuilder &other);
  ReminderSignalBuilder &operator=(const ReminderSignalBuilder &other);
};

#endif // REMINDERSIGNALBUILDER_H
