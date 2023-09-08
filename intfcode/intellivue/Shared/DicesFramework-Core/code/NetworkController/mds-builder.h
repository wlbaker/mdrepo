#ifndef MDSBUILDER_H
#define MDSBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class MDSBuilder : public AbstractTopicBuilder
{
public:
  MDSBuilder();
  ~MDSBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  MDSBuilder(const MDSBuilder &other);
  MDSBuilder &operator=(const MDSBuilder &other);
};

#endif // MDSBUILDER_H
