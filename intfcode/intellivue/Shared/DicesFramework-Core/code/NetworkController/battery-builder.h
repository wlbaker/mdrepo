#ifndef BATTERYBUILDER_H
#define BATTERYBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class BatteryBuilder : public AbstractTopicBuilder
{
public:
  BatteryBuilder();
  ~BatteryBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  BatteryBuilder(const BatteryBuilder &other);
  BatteryBuilder &operator=(const BatteryBuilder &other);
};

#endif // BATTERYBUILDER_H
