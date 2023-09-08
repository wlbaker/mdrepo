#include "network-controller.h"

#include "base-logger.h"
#include "rc-entity-builder.h"
#include "semaphore.h"
#include "common.h"
#include "entity-name-manager.h"


struct NetworkController::impl
{
  static NetworkController *_instance;

  int _domain_id;
  DDSDomainParticipant *_participant;
  DDSPublisher *_publisher;
  DDSSubscriber *_subscriber;

  impl()
    : _domain_id(ice::DDS_DOMAIN_ID_MANAGER),
      _participant(nullptr),
      _publisher(nullptr),
      _subscriber(nullptr)
  {

  }

  ~impl() = default;

  DicesRcEntityBuilder init()
  {
    return DicesRcEntityBuilder::OK;
  }

  static NetworkController *instance()
  {
    if(!_instance)
    {
      _instance = new (std::nothrow) NetworkController;
    }

    return _instance;
  }

  DDSDomainParticipant *get_participant()
  {
    _participant = DDSTheParticipantFactory->lookup_participant(_domain_id);
    return _participant;
  }

  DDSPublisher *get_publisher()
  {
    if (!_participant)
    {
      _publisher = nullptr;
      return _publisher;
    }
    _publisher = _participant->lookup_publisher_by_name(EntityNameManager::GetPublisherName(_domain_id).c_str());
    return _publisher;
  }

  DDSSubscriber *get_subscriber()
  {
    if (!_participant)
    {
      _subscriber = nullptr;
      return _subscriber;
    }
    _subscriber = _participant->lookup_subscriber_by_name(EntityNameManager::GetSubscriberName(_domain_id).c_str());
    return _subscriber;
  }

};

NetworkController *NetworkController::impl::_instance = nullptr;

NetworkController::NetworkController()
  : _pimpl(nullptr)
{
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    return;
  }
}

NetworkController::~NetworkController()
{
}

DicesRcEntityBuilder NetworkController::init()
{
  return _pimpl->init();
}

NetworkController *NetworkController::instance()
{
  return NetworkController::impl::instance();
}

void NetworkController::set_domain_id(int domain_id)
{
  _pimpl->_domain_id = domain_id;
}

int NetworkController::get_domain_id()
{
  return _pimpl->_domain_id;
}

DDSDomainParticipant *NetworkController::get_participant()
{
  return _pimpl->get_participant();
}

DDSPublisher *NetworkController::get_publisher()
{
  return _pimpl->get_publisher();
}

DDSSubscriber *NetworkController::get_subscriber()
{
  return _pimpl->get_subscriber();
}
