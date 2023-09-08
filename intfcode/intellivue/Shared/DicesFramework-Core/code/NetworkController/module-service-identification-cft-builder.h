#ifndef MODULE_SERVICE_IDENTIFICATION_CFT_BUILDER_H
#define MODULE_SERVICE_IDENTIFICATION_CFT_BUILDER_H

#include "abstract-content-filtered-topic-builder.h"

enum class DicesRcEntityBuilder;

class ModuleServiceIdentificationCftBuilder : public AbstractContentFilteredTopicBuilder
{
public:
  ModuleServiceIdentificationCftBuilder(std::string content_filtered_topic_name);
  ~ModuleServiceIdentificationCftBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_library_name();

  const std::string get_type_name();

  const std::string get_qos_profile();

  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceIdentificationCftBuilder(const ModuleServiceIdentificationCftBuilder &other);
  ModuleServiceIdentificationCftBuilder &operator=(const ModuleServiceIdentificationCftBuilder &other);
};

#endif // MODULE_SERVICE_IDENTIFICATION_CFT_BUILDER_H
