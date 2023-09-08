#ifndef CLINICAL_NOTE_BUILDER_H
#define CLINICAL_NOTE__BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class ClinicalNoteBuilder : public AbstractTopicBuilder
{
public:
  friend class ClinicalNoteBuilderUnitTest;

  ClinicalNoteBuilder();
  ~ClinicalNoteBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  ClinicalNoteBuilder(const ClinicalNoteBuilder &other);
  ClinicalNoteBuilder &operator=(const ClinicalNoteBuilder &other);
};

#endif // KEYED_OCTET_BUILDER_H
