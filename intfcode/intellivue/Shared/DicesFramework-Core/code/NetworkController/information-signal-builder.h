#ifndef INFORMATIONSIGNALBUILDER_H
#define INFORMATIONSIGNALBUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class InformationSignalBuilder : public AbstractTopicBuilder
{
public:
  InformationSignalBuilder();
  ~InformationSignalBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  InformationSignalBuilder(const InformationSignalBuilder &other);
  InformationSignalBuilder &operator=(const InformationSignalBuilder &other);
};

#endif // INFORMATIONSIGNALBUILDER_H
