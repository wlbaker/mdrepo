#ifndef ALARM_SIGNAL_TYPE_H
#define ALARM_SIGNAL_TYPE_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class AlarmSignalTypeBuilder : public AbstractTopicBuilder
{
public:
  AlarmSignalTypeBuilder();
  ~AlarmSignalTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  AlarmSignalTypeBuilder(const AlarmSignalTypeBuilder &other);
  AlarmSignalTypeBuilder &operator=(const AlarmSignalTypeBuilder &other);
};

#endif // ALARM_SIGNAL_TYPE_H
