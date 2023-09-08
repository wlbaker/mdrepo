#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <memory>

enum class DicesRcEntityBuilder;

class DDSDomainParticipant;
class DDSPublisher;
class DDSSubscriber;

class NetworkController
{
public:
  ~NetworkController();

  DicesRcEntityBuilder init();

  int get_domain_id();
  void set_domain_id(int domain_id);

  static NetworkController *instance();

  DDSDomainParticipant *get_participant();
  DDSPublisher *get_publisher();
  DDSSubscriber *get_subscriber();

  // Disallow use of implicitly generated member functions:
  NetworkController(const NetworkController &other) = delete;
  NetworkController &operator=(const NetworkController &other) = delete;

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

private:

  NetworkController();
};

#endif // NETWORKCONTROLLER_H
