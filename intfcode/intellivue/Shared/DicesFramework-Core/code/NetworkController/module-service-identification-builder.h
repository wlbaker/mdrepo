#ifndef MODULE_SERVICE_IDENTIFICATION_BUILDER_H
#define MODULE_SERVICE_IDENTIFICATION_BUILDER_H

#include "module-service-identification-type-builder.h"

class ModuleServiceIdentificationBuilder : public ModuleServiceIdentificationTypeBuilder
{
public:
  ModuleServiceIdentificationBuilder();
  ~ModuleServiceIdentificationBuilder();

protected:
  const std::string get_topic_name();

private:
  // Disallow use of implicitly generated member functions:
  ModuleServiceIdentificationBuilder(const ModuleServiceIdentificationBuilder &other);
  ModuleServiceIdentificationBuilder &operator=(const ModuleServiceIdentificationBuilder &other);
};

#endif // MODULE_SERVICE_IDENTIFICATION_BUILDER_H
