#ifndef APP_FOCUS_STATE_ERROR_BUILDER_H
#define APP_FOCUS_STATE_ERROR_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class AppFocusStateErrorBuilder : public AbstractTopicBuilder
{
public:
  AppFocusStateErrorBuilder();
  ~AppFocusStateErrorBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  AppFocusStateErrorBuilder(const AppFocusStateErrorBuilder &other);
  AppFocusStateErrorBuilder &operator=(const AppFocusStateErrorBuilder &other);
};

#endif // APP_FOCUS_STATE_ERROR_BUILDER_H
