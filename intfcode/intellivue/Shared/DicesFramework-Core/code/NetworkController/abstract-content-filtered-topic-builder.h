#ifndef ABSTRACTCONTENTFILTEREDTOPICBUILDER_H
#define ABSTRACTCONTENTFILTEREDTOPICBUILDER_H

#include "abstract-entity-builder.h"

#include <string>
#include <memory>

enum class DicesRcEntityBuilder;

class AbstractContentFilteredTopicBuilder : public AbstractEntityBuilder
{
public:
  AbstractContentFilteredTopicBuilder(std::string content_filtered_topic_name);
  ~AbstractContentFilteredTopicBuilder();

  DicesRcEntityBuilder construct_topic();

  // Disallow use of implicitly generated member functions:
  AbstractContentFilteredTopicBuilder(const AbstractContentFilteredTopicBuilder &other) = delete;
  AbstractContentFilteredTopicBuilder &operator=(const AbstractContentFilteredTopicBuilder &other) = delete;

protected:
    struct impl;
    std::unique_ptr<impl> _pimpl;
};

#endif // ABSTRACTCONTENTFILTEREDTOPICBUILDER_H
