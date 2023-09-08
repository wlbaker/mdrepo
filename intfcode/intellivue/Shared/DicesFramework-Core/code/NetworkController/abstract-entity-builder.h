#ifndef ABSTRACTENTITYBUILDER_H
#define ABSTRACTENTITYBUILDER_H

#include "ice-domain-entity-builder.h"

#include <string>
#include <memory>

class DDSDataReader;
class DDSDataWriter;
class DDSTopicDescription;
class DDSDomainParticipant;
enum class DicesRcEntityBuilder;

class AbstractEntityBuilder : public ICEDomainEntityBuilder
{
public:
  AbstractEntityBuilder();
  ~AbstractEntityBuilder();

  virtual DicesRcEntityBuilder construct_topic() = 0;

  DicesRcEntityBuilder construct_reader();

  DDSDataReader *get_reader();

  DicesRcEntityBuilder construct_writer();

  DDSDataWriter *get_writer();

  DDSDomainParticipant *get_participant();

  DDSPublisher *get_publisher();

  DDSSubscriber *get_subscriber();

  void set_participant(DDSDomainParticipant* participant);

  void set_publisher(DDSPublisher* publisher);

  void set_subscriber(DDSSubscriber* subscriber);

  // Disallow use of implicitly generated member functions:
  AbstractEntityBuilder(const AbstractEntityBuilder &other) = delete;
  AbstractEntityBuilder &operator=(const AbstractEntityBuilder &other) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

  virtual const std::string get_library_name() = 0;

  virtual const std::string get_topic_name() = 0;

  virtual const std::string get_type_name() = 0;

  virtual const std::string get_qos_profile() = 0;

  DDSTopicDescription *get_topic();
  void set_topic(DDSTopicDescription *topic);
};

#endif // ABSTRACTENTITYBUILDER_H
