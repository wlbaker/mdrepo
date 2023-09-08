#ifndef TECHNICAL_ALARM_SIGNAL_H
#define TECHNICAL_ALARM_SIGNAL_H

#include "alarm-signal-type-builder.h"

class TechnicalAlarmSignalBuilder : public AlarmSignalTypeBuilder
{
public:
  TechnicalAlarmSignalBuilder();
  ~TechnicalAlarmSignalBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TechnicalAlarmSignalBuilder(const TechnicalAlarmSignalBuilder &other);
  TechnicalAlarmSignalBuilder &operator=(const TechnicalAlarmSignalBuilder &other);
};

#endif // TECHNICAL_ALARM_SIGNAL_H
