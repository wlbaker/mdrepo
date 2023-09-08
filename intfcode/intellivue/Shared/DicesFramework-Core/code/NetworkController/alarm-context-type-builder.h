#ifndef ALARM_CONTEXT_TYPE_H
#define ALARM_CONTEXT_TYPE_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class AlarmContextTypeBuilder : public AbstractTopicBuilder
{
public:
  AlarmContextTypeBuilder();
  ~AlarmContextTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  AlarmContextTypeBuilder(const AlarmContextTypeBuilder &other);
  AlarmContextTypeBuilder &operator=(const AlarmContextTypeBuilder &other);
};

#endif // ALARM_CONTEXT_TYPE_H
