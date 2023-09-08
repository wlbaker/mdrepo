#ifndef VMD_BUILDER_H
#define VMD_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class VMDBuilder : public AbstractTopicBuilder
{
public:
  VMDBuilder();
  ~VMDBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  VMDBuilder(const VMDBuilder &other);
  VMDBuilder &operator=(const VMDBuilder &other);
};

#endif // VMD_BUILDER_H
