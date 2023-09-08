#ifndef PHYSIOLOGICAL_ALARM_CONTEXT_H
#define PHYSIOLOGICAL_ALARM_CONTEXT_H

#include "alarm-context-type-builder.h"

class PhysiologicalAlarmContextBuilder : public AlarmContextTypeBuilder
{
public:
  PhysiologicalAlarmContextBuilder();
  ~PhysiologicalAlarmContextBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PhysiologicalAlarmContextBuilder(const PhysiologicalAlarmContextBuilder &other);
  PhysiologicalAlarmContextBuilder &operator=(const PhysiologicalAlarmContextBuilder &other);
};

#endif // PHYSIOLOGICAL_ALARM_CONTEXT_H
