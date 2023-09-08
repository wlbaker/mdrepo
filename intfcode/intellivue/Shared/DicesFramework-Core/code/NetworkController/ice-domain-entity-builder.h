#ifndef ICEDOMAINENTITYBUILDER
#define ICEDOMAINENTITYBUILDER

class DDSDomainParticipant;
class DDSDataReader;
class DDSDataWriter;
class DDSPublisher;
class DDSSubscriber;
class DDSTopic;
enum class DicesRcEntityBuilder;

class ICEDomainEntityBuilder
{
public:
  ICEDomainEntityBuilder()
  {

  }

  ~ICEDomainEntityBuilder()
  {

  }

  virtual DicesRcEntityBuilder register_type() = 0;

  virtual DicesRcEntityBuilder construct_reader() = 0;

  virtual DicesRcEntityBuilder construct_topic() = 0;

  virtual DDSDataReader *get_reader() = 0;

  virtual DicesRcEntityBuilder construct_writer() = 0;

  virtual DDSDataWriter *get_writer() = 0;

  virtual DDSDomainParticipant *get_participant() = 0;

  virtual DDSPublisher *get_publisher() = 0;

  virtual DDSSubscriber *get_subscriber() = 0;

  virtual void set_participant(DDSDomainParticipant* participant) = 0;

  virtual void set_publisher(DDSPublisher* publisher) = 0;

  virtual void set_subscriber(DDSSubscriber* subscriber) = 0;

private:
  // Disallow use of implicitly generated member functions:
  ICEDomainEntityBuilder(const ICEDomainEntityBuilder &other);
  ICEDomainEntityBuilder &operator=(const ICEDomainEntityBuilder &other);
};

#endif // ICEDOMAINENTITYBUILDER
