#ifndef APP_FOCUS_STATE_TYPE_BUILDER_H
#define APP_FOCUS_STATE_TYPE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class AppFocusStateTypeBuilder : public AbstractTopicBuilder
{
public:
  AppFocusStateTypeBuilder();
  ~AppFocusStateTypeBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  AppFocusStateTypeBuilder(const AppFocusStateTypeBuilder &other);
  AppFocusStateTypeBuilder &operator=(const AppFocusStateTypeBuilder &other);
};

#endif // APP_FOCUS_STATE_TYPE_BUILDER_H
