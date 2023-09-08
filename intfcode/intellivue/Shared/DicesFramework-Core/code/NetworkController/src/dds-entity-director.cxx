#include "dds-entity-director.h"

#include <ndds/ndds_namespace_cpp.h>

#include "rc-entity-builder.h"
#include "entity-name-manager.h"
#include "common.h"

struct DDSEntityDirector::impl
{
  int _domain_id;
  ICEDomainEntityBuilder *_builder;

  impl(int domain_id, ICEDomainEntityBuilder *builder)
    : _domain_id(domain_id),
      _builder(builder)
  {
  }

  ~impl() = default;

  DicesRcEntityBuilder construct_reader()
  {
    DicesRcEntityBuilder ret_code = DicesRcEntityBuilder::OK;

    DDS::DomainParticipant* participant = DDSTheParticipantFactory->
      lookup_participant(_domain_id);
    if(!participant)
    {
      return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
    }

    DDS::Publisher* publisher = participant->lookup_publisher_by_name(
      EntityNameManager::GetPublisherName(_domain_id).c_str());
    if(!publisher)
    {
      return DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL;
    }

    DDS::Subscriber* subscriber = participant->lookup_subscriber_by_name(
      EntityNameManager::GetSubscriberName(_domain_id).c_str());
    if(!subscriber)
    {
      return DicesRcEntityBuilder::SUBSCRIBER_POINTER_IS_NULL;
    }

    _builder->set_participant(participant);
    _builder->set_publisher(publisher);
    _builder->set_subscriber(subscriber);

    ret_code = _builder->register_type();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    ret_code = _builder->construct_topic();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    ret_code = _builder->construct_reader();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    return ret_code;
  }

  DDSDataReader *get_reader()
  {
    return _builder->get_reader();
  }

  DicesRcEntityBuilder construct_writer()
  {
    DicesRcEntityBuilder ret_code = DicesRcEntityBuilder::OK;

    DDS::DomainParticipant* participant = DDSTheParticipantFactory->
      lookup_participant(_domain_id);
    if(!participant)
    {
      return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
    }

    DDS::Publisher* publisher = participant->lookup_publisher_by_name(
      EntityNameManager::GetPublisherName(_domain_id).c_str());
    if(!publisher)
    {
      return DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL;
    }

    DDS::Subscriber* subscriber = participant->lookup_subscriber_by_name(
      EntityNameManager::GetSubscriberName(_domain_id).c_str());
    if(!subscriber)
    {
      return DicesRcEntityBuilder::SUBSCRIBER_POINTER_IS_NULL;
    }

    _builder->set_participant(participant);
    _builder->set_publisher(publisher);
    _builder->set_subscriber(subscriber);

    ret_code = _builder->register_type();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    ret_code = _builder->construct_topic();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    ret_code = _builder->construct_writer();

    if(ret_code != DicesRcEntityBuilder::OK)
      return ret_code;

    return ret_code;
  }

  DDSDataWriter *get_writer()
  {
    return _builder->get_writer();
  }

  DDSPublisher *get_publisher()
  {
    DDS::DomainParticipant* participant = DDSTheParticipantFactory->
      lookup_participant(_domain_id);
    if(!participant)
    {
      return nullptr;
    }

    DDS::Publisher* publisher = participant->lookup_publisher_by_name(
      EntityNameManager::GetPublisherName(_domain_id).c_str());

    _builder->set_publisher(publisher);

    return _builder->get_publisher();
  }

  DDSSubscriber *get_subscriber()
  {
    DDS::DomainParticipant* participant = DDSTheParticipantFactory->
      lookup_participant(_domain_id);
    if(!participant)
    {
      return nullptr;
    }

    DDS::Subscriber* subscriber = participant->lookup_subscriber_by_name(
      EntityNameManager::GetSubscriberName(_domain_id).c_str());

    _builder->set_subscriber(subscriber);

    return _builder->get_subscriber();
  }

};

DDSEntityDirector::DDSEntityDirector(int domain_id, ICEDomainEntityBuilder *builder)
  : _pimpl(nullptr)
{
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl(domain_id, builder));
  if (!_pimpl)
  {
    return;
  }
}

DDSEntityDirector::~DDSEntityDirector()
{
}

DicesRcEntityBuilder DDSEntityDirector::construct_reader()
{
  return _pimpl->construct_reader();
}

DDSDataReader *DDSEntityDirector::get_reader()
{
  return _pimpl->get_reader();
}

DicesRcEntityBuilder DDSEntityDirector::construct_writer()
{
  return _pimpl->construct_writer();
}

DDSDataWriter *DDSEntityDirector::get_writer()
{
  return _pimpl->get_writer();
}

DDSPublisher *DDSEntityDirector::get_publisher()
{
  return _pimpl->get_publisher();
}

DDSSubscriber *DDSEntityDirector::get_subscriber()
{
  return _pimpl->get_subscriber();
}
