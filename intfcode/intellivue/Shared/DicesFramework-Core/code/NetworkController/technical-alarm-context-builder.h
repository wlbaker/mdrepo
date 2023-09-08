#ifndef TECHNICAL_ALARM_CONTEXT_H
#define TECHNICAL_ALARM_CONTEXT_H

#include "alarm-context-type-builder.h"

class TechnicalAlarmContextBuilder : public AlarmContextTypeBuilder
{
public:
  TechnicalAlarmContextBuilder();
  ~TechnicalAlarmContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TechnicalAlarmContextBuilder(const TechnicalAlarmContextBuilder &other);
  TechnicalAlarmContextBuilder &operator=(const TechnicalAlarmContextBuilder &other);
};

#endif // TECHNICAL_ALARM_CONTEXT_H
