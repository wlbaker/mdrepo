#ifndef CLINICAL_NOTE_BUNDLE_BUILDER_H
#define CLINICAL_NOTE_BUNDLE_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ClinicalNoteBundleBuilder : public AbstractTopicBuilder
{
public:
  friend class ClinicalNoteBundleBuilderUnitTest;

  ClinicalNoteBundleBuilder();
  ~ClinicalNoteBundleBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ClinicalNoteBundleBuilder(const ClinicalNoteBundleBuilder &other);
  ClinicalNoteBundleBuilder &operator=(const ClinicalNoteBundleBuilder &other);
};

#endif // KEYED_OCTET_BUILDER_H
