#ifndef PHYSIOLOGICAL_ALARM_SIGNAL_H
#define PHYSIOLOGICAL_ALARM_SIGNAL_H

#include "alarm-signal-type-builder.h"

class PhysiologicalAlarmSignalBuilder : public AlarmSignalTypeBuilder
{
public:
  PhysiologicalAlarmSignalBuilder();
  ~PhysiologicalAlarmSignalBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PhysiologicalAlarmSignalBuilder(const PhysiologicalAlarmSignalBuilder &other);
  PhysiologicalAlarmSignalBuilder &operator=(const PhysiologicalAlarmSignalBuilder &other);
};

#endif // PHYSIOLOGICAL_ALARM_SIGNAL_H
