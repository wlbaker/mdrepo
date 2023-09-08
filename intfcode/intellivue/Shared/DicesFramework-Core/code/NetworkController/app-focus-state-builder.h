#ifndef APP_FOCUS_STATE_BUILDER_H
#define APP_FOCUS_STATE_BUILDER_H

#include "app-focus-state-type-builder.h"

class AppFocusStateBuilder : public AppFocusStateTypeBuilder
{
public:
  AppFocusStateBuilder();
  ~AppFocusStateBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  AppFocusStateBuilder(const AppFocusStateBuilder &other);
  AppFocusStateBuilder &operator=(const AppFocusStateBuilder &other);
};

#endif // APP_FOCUS_STATE_BUILDER_H
