#ifndef DDSENTITYDIRECTOR_H
#define DDSENTITYDIRECTOR_H

class DDSDataReader;
class DDSDataWriter;
class DDSPublisher;
class DDSSubscriber;

#include <memory>
#include "ice-domain-entity-builder.h"

class DDSEntityDirector
{
public:
  DDSEntityDirector(int domain_id, ICEDomainEntityBuilder *builder);
  ~DDSEntityDirector();

  DicesRcEntityBuilder construct_reader();

  DDSDataReader *get_reader();

  DicesRcEntityBuilder construct_writer();

  DDSDataWriter *get_writer();

  DDSPublisher *get_publisher();

  DDSSubscriber *get_subscriber();

  // Disallow use of implicitly generated member functions:
  DDSEntityDirector(const DDSEntityDirector &other) = delete;
  DDSEntityDirector &operator=(const DDSEntityDirector &other) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;
};

#endif // DDSENTITYDIRECTOR_H
