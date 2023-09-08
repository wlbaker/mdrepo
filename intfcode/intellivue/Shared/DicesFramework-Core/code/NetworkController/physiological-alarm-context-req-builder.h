#ifndef PHYSIOLOGICAL_ALARM_CONTEXT_REQ_H
#define PHYSIOLOGICAL_ALARM_CONTEXT_REQ_H

#include "alarm-context-type-builder.h"

class PhysiologicalAlarmContextReqBuilder : public AlarmContextTypeBuilder
{
public:
  PhysiologicalAlarmContextReqBuilder();
  ~PhysiologicalAlarmContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  PhysiologicalAlarmContextReqBuilder(const PhysiologicalAlarmContextReqBuilder &other);
  PhysiologicalAlarmContextReqBuilder &operator=(const PhysiologicalAlarmContextReqBuilder &other);
};

#endif // PHYSIOLOGICAL_ALARM_CONTEXT_REQ_H
