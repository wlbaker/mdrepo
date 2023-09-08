#include "abstract-entity-builder.h"

#include <ndds_namespace_cpp.h>

#include "rc-entity-builder.h"
#include "network-controller.h"

struct AbstractEntityBuilder::impl
{
  DDSDomainParticipant *_participant;
  DDSPublisher *_publisher;
  DDSSubscriber *_subscriber;
  DDSDataReader *_reader;
  DDSDataWriter *_writer;
  DDSTopicDescription *_topic;

  impl()
    : _participant(nullptr),
      _publisher(nullptr),
      _subscriber(nullptr),
      _reader(nullptr),
      _writer(nullptr),
      _topic(nullptr)
  {
  }

  ~impl() = default;

  DicesRcEntityBuilder construct_reader(AbstractEntityBuilder& src)
  {
    if(_reader) return DicesRcEntityBuilder::OK;

    if(!_subscriber)
    {
      return DicesRcEntityBuilder::SUBSCRIBER_POINTER_IS_NULL;
    }

    if(!_topic)
    {
      return DicesRcEntityBuilder::TOPIC_POINTER_IS_NULL;
    }

    _reader = _subscriber->
              create_datareader_with_profile(
                _topic,
                src.get_library_name().c_str(),
                src.get_qos_profile().c_str(),
                NULL,
                DDS::STATUS_MASK_NONE);

    if(!_reader)
    {
      return DicesRcEntityBuilder::CREATE_READER_FAILED;
    }

    return DicesRcEntityBuilder::OK;
  }

  DicesRcEntityBuilder construct_writer(AbstractEntityBuilder& src)
  {
    if(_writer) return DicesRcEntityBuilder::OK;

    if(!_publisher)
    {
      return DicesRcEntityBuilder::PUBLISHER_POINTER_IS_NULL;
    }

    if(!_topic)
    {
      return DicesRcEntityBuilder::TOPIC_POINTER_IS_NULL;
    }

    DDSTopic *topic = DDSTopic::narrow(_topic);

    if(!topic)
    {
      return DicesRcEntityBuilder::FAIL;
    }

    _writer = _publisher->
              create_datawriter_with_profile(
                topic,
                src.get_library_name().c_str(),
                src.get_qos_profile().c_str(),
                NULL,
                DDS::STATUS_MASK_NONE);
    if(!_writer)
    {
      return DicesRcEntityBuilder::CREATE_WRITER_FAILED;
    }

    return DicesRcEntityBuilder::OK;
  }
};

AbstractEntityBuilder::AbstractEntityBuilder() :
  ICEDomainEntityBuilder(),
  _pimpl(nullptr)
{
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    return;
  }
}

AbstractEntityBuilder::~AbstractEntityBuilder()
{

}

DDSTopicDescription *AbstractEntityBuilder::get_topic()
{
  return _pimpl->_topic;
}

void AbstractEntityBuilder::set_topic(DDSTopicDescription *topic)
{
  _pimpl->_topic = topic;
}

DicesRcEntityBuilder AbstractEntityBuilder::construct_reader()
{
  return _pimpl->construct_reader(*this);
}

DDSDataReader *AbstractEntityBuilder::get_reader()
{
  return _pimpl->_reader;
}

DicesRcEntityBuilder AbstractEntityBuilder::construct_writer()
{
  return _pimpl->construct_writer(*this);
}

DDSDataWriter *AbstractEntityBuilder::get_writer()
{
  return _pimpl->_writer;
}

DDSDomainParticipant *AbstractEntityBuilder::get_participant()
{
  return _pimpl->_participant;
}

DDSPublisher *AbstractEntityBuilder::get_publisher()
{
  return _pimpl->_publisher;
}

DDSSubscriber *AbstractEntityBuilder::get_subscriber()
{
  return _pimpl->_subscriber;
}

void AbstractEntityBuilder::set_participant(DDSDomainParticipant *participant)
{
  _pimpl->_participant = participant;
}

void AbstractEntityBuilder::set_publisher(DDSPublisher *publisher)
{
  _pimpl->_publisher = publisher;
}

void AbstractEntityBuilder::set_subscriber(DDSSubscriber *subscriber)
{
  _pimpl->_subscriber = subscriber;
}

