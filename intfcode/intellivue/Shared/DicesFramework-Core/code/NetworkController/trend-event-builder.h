#ifndef TREND_EVENT_BUILDER_H
#define TREND_EVENT_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class TrendEventBuilder : public AbstractTopicBuilder
{
public:
  TrendEventBuilder();
  ~TrendEventBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  TrendEventBuilder(const TrendEventBuilder &other);
  TrendEventBuilder &operator=(const TrendEventBuilder &other);
};

#endif // TREND_EVENT_BUILDER_H