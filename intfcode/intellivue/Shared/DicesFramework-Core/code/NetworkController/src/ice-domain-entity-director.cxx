#include "ice-domain-entity-director.h"

#include <ndds/ndds_namespace_cpp.h>

#include "rc-entity-builder.h"
#include "network-controller.h"

struct ICEDomainEntityDirector::impl
{
    ICEDomainEntityBuilder *_builder;

    impl(ICEDomainEntityBuilder *builder)
      :  _builder(builder)
    {
    }

    ~impl() = default;


    DicesRcEntityBuilder construct_reader()
    {
      DicesRcEntityBuilder ret_code = DicesRcEntityBuilder::OK;

      if(!NetworkController::instance())
      {
        return DicesRcEntityBuilder::NETWORK_CONTROLLER_POINTER_IS_NULL;
      }

      DDS::DomainParticipant* participant = NetworkController::instance()->get_participant();
      if(!participant)
      {
        return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
      }

      DDS::Publisher* publisher = NetworkController::instance()->get_publisher();
      if(!publisher)
      {
        return DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL;
      }

      DDS::Subscriber* subscriber = NetworkController::instance()->get_subscriber();
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

      if(!NetworkController::instance())
      {
        return DicesRcEntityBuilder::NETWORK_CONTROLLER_POINTER_IS_NULL;
      }

      DDS::DomainParticipant* participant = NetworkController::instance()->get_participant();
      if(!participant)
      {
        return DicesRcEntityBuilder::PARTICIPANT_POINTER_IS_NULL;
      }

      DDS::Publisher* publisher = NetworkController::instance()->get_publisher();
      if(!publisher)
      {
        return DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL;
      }

      DDS::Subscriber* subscriber = NetworkController::instance()->get_subscriber();
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
      if(!NetworkController::instance())
      {
        return nullptr;
      }

      DDS::DomainParticipant* participant = NetworkController::instance()->get_participant();
      if(!participant)
      {
        return nullptr;
      }

      DDS::Publisher* publisher = NetworkController::instance()->get_publisher();
      if(!publisher)
      {
        return nullptr;
      }

      DDS::Subscriber* subscriber = NetworkController::instance()->get_subscriber();
      if(!subscriber)
      {
        return nullptr;
      }

      _builder->set_participant(participant);
      _builder->set_publisher(publisher);
      _builder->set_subscriber(subscriber);

      return _builder->get_publisher();
    }

    DDSSubscriber *get_subscriber()
    {
      if(!NetworkController::instance())
      {
        return nullptr;
      }

      DDS::DomainParticipant* participant = NetworkController::instance()->get_participant();
      if(!participant)
      {
        return nullptr;
      }

      DDS::Publisher* publisher = NetworkController::instance()->get_publisher();
      if(!publisher)
      {
        return nullptr;
      }

      DDS::Subscriber* subscriber = NetworkController::instance()->get_subscriber();
      if(!subscriber)
      {
        return nullptr;
      }

      _builder->set_participant(participant);
      _builder->set_publisher(publisher);
      _builder->set_subscriber(subscriber);

      return _builder->get_subscriber();
    }
};

ICEDomainEntityDirector::ICEDomainEntityDirector(ICEDomainEntityBuilder *builder)
  : _pimpl(nullptr)
{
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl(builder));
  if (!_pimpl)
  {
    return;
  }
}

ICEDomainEntityDirector::~ICEDomainEntityDirector()
{
}

DicesRcEntityBuilder ICEDomainEntityDirector::construct_reader()
{
  return _pimpl->construct_reader();
}

DDSDataReader *ICEDomainEntityDirector::get_reader()
{
  return _pimpl->get_reader();
}

DicesRcEntityBuilder ICEDomainEntityDirector::construct_writer()
{
  return _pimpl->construct_writer();
}

DDSDataWriter *ICEDomainEntityDirector::get_writer()
{
  return _pimpl->get_writer();
}

DDSPublisher *ICEDomainEntityDirector::get_publisher()
{
  return _pimpl->get_publisher();
}

DDSSubscriber *ICEDomainEntityDirector::get_subscriber()
{
  return _pimpl->get_subscriber();
}
