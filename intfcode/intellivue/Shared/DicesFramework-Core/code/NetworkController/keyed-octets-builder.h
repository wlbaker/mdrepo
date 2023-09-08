#ifndef KEYED_OCTETS_BUILDER_H
#define KEYED_OCTETS_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class KeyedOctetsBuilder : public AbstractTopicBuilder
{
public:
  KeyedOctetsBuilder();
  ~KeyedOctetsBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  KeyedOctetsBuilder(const KeyedOctetsBuilder &other);
  KeyedOctetsBuilder &operator=(const KeyedOctetsBuilder &other);
};

#endif // KEYED_OCTET_BUILDER_H
