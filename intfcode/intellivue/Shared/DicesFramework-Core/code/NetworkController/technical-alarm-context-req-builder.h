#ifndef TECHNICAL_ALARM_CONTEXT_REQ_H
#define TECHNICAL_ALARM_CONTEXT_REQ_H

#include "alarm-context-type-builder.h"

class TechnicalAlarmContextReqBuilder : public AlarmContextTypeBuilder
{
public:
  TechnicalAlarmContextReqBuilder();
  ~TechnicalAlarmContextReqBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  TechnicalAlarmContextReqBuilder(const TechnicalAlarmContextReqBuilder &other);
  TechnicalAlarmContextReqBuilder &operator=(const TechnicalAlarmContextReqBuilder &other);
};

#endif // TECHNICAL_ALARM_CONTEXT_REQ_H
