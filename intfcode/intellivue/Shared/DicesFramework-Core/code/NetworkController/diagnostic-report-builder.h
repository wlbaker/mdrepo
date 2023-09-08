#ifndef DIAGNOSTIC_REPORT_BUILDER_H
#define DIAGNOSTIC_REPORT_BUILDER_H

#include "abstract-topic-builder.h"

enum class DicesRcEntityBuilder;

class DiagnosticReportBuilder : public AbstractTopicBuilder
{
public:
  friend class DiagnosticReportBuilderUnitTest;

  DiagnosticReportBuilder();
  ~DiagnosticReportBuilder();

  DicesRcEntityBuilder register_type();

protected:
  const std::string get_topic_name();

  const std::string get_type_name();

private:
  // Disallow use of implicitly generated member functions:
  DiagnosticReportBuilder(const DiagnosticReportBuilder &other);
  DiagnosticReportBuilder &operator=(const DiagnosticReportBuilder &other);
};

#endif // DIAGNOSTIC_REPORT_BUILDER_H
