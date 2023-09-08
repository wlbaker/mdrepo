#ifndef ICEDOMAINENTITYDIRECTOR_H
#define ICEDOMAINENTITYDIRECTOR_H

class DDSDataReader;
class DDSDataWriter;
class DDSPublisher;
class DDSSubscriber;

#include <memory>
#include "ice-domain-entity-builder.h"

class ICEDomainEntityDirector
{
public:
  ICEDomainEntityDirector(ICEDomainEntityBuilder *builder);
  ~ICEDomainEntityDirector();

  DicesRcEntityBuilder construct_reader();

  DDSDataReader *get_reader();

  DicesRcEntityBuilder construct_writer();

  DDSDataWriter *get_writer();

  DDSPublisher *get_publisher();

  DDSSubscriber *get_subscriber();

  // Disallow use of implicitly generated member functions:
  ICEDomainEntityDirector(const ICEDomainEntityDirector &other) = delete;
  ICEDomainEntityDirector &operator=(const ICEDomainEntityDirector &other) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;
};

#endif // ICEDOMAINENTITYDIRECTOR_H
