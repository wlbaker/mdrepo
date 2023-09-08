#ifndef MODULE_SERVICE_FOCUS_ERROR_BUILDER_H
#define MODULE_SERVICE_FOCUS_ERROR_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceFocusErrorBuilder : public AbstractTopicBuilder
{
public:
  ModuleServiceFocusErrorBuilder();
  ~ModuleServiceFocusErrorBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceFocusErrorBuilder(const ModuleServiceFocusErrorBuilder &other);
  ModuleServiceFocusErrorBuilder &operator=(const ModuleServiceFocusErrorBuilder &other);
};

#endif // MODULE_SERVICE_FOCUS_ERROR_BUILDER_H
