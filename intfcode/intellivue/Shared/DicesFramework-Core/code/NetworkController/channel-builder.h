#ifndef CHANNELBUILDER_H
#define CHANNELBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ChannelBuilder : public AbstractTopicBuilder
{
public:
  ChannelBuilder();
  ~ChannelBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ChannelBuilder(const ChannelBuilder &other);
  ChannelBuilder &operator=(const ChannelBuilder &other);
};

#endif // CHANNELBUILDER_H
