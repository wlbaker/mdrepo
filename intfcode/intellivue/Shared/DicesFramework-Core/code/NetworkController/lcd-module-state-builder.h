#ifndef LCD_MODULE_STATE_BUILDER_H
#define LCD_MODULE_STATE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class LCDModuleStateBuilder : public AbstractTopicBuilder
{
public:
  LCDModuleStateBuilder();
  ~LCDModuleStateBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  LCDModuleStateBuilder(const LCDModuleStateBuilder &other);
  LCDModuleStateBuilder &operator=(const LCDModuleStateBuilder &other);
};

#endif // LCD_MODULE_STATE_BUILDER_H
