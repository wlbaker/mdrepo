/**
 * @file  NumericReaderInterface.cxx
 * @brief Manage DDS entities for reading the NumericObservedValue type.
 */
//=============================================================================
#include "ndds/ndds_cpp.h"
#include "DDSCommunicator.h"
#include "DDSTypeWrapper.h"
#include "numeric.h"
#include "numericSupport.h"
#include "NumericReaderInterface.h"

// -------------------------------------------------------------------------
NumericReaderInterface::NumericReaderInterface()
  : _communicator(0),
    _reader(0),
	  _waitSet(0),
	  _condition(0),
    _instance_alive(0),
    _instance_disposed(0),
    _instance_no_writers(0)
{
}

// -------------------------------------------------------------------------
NumericReaderInterface::~NumericReaderInterface()
{
  Destroy();
}

// -------------------------------------------------------------------------
// Destroyer
// Delete the DataReader, and Communicator objects
int NumericReaderInterface::Destroy()
{
  DDS_ReturnCode_t rc {DDS_RETCODE_OK};

  if (_waitSet)
  {
    //_waitSet->detach_condition(_condition);
    _waitSet->detach_condition(_instance_alive);
    _waitSet->detach_condition(_instance_disposed);
    _waitSet->detach_condition(_instance_no_writers);
    delete _waitSet;
    _instance_alive = 0;
    _instance_disposed = 0;
    _instance_no_writers = 0;
    _waitSet = 0;
  }
  if (_reader)
  {
    _reader->delete_contained_entities();
    DDS::Subscriber *sub = _reader->get_subscriber();
    if (sub) sub->delete_datareader(_reader);
    _reader = 0;
  }
  delete _communicator;
  _communicator = 0;
  return rc;
}

// -------------------------------------------------------------------------
// Initializer
// Create the domain participant, publisher, topic and reader.
int NumericReaderInterface::Initialize(
  const long domain_id,
  const char *topicname,
  const char *qoslibraryname,
  const char *qosprofilename)
{
  const char *sfn {"NumericReaderInterface::Initialize"};
  DDS_ReturnCode_t rc {DDS_RETCODE_OK};
  _communicator = new (std::nothrow) DDSCommunicator();

  // Create a DomainParticipant
  if (!_communicator->CreateParticipant(domain_id))
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  }

  // Create a Subscriber
  DDS::Subscriber *sub = _communicator->CreateSubscriber();
  if (!sub)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Subscriber object";
    throw errss.str();
  }

  // Create topic
  DDS::Topic *topic =
    _communicator->CreateTopic<ice::NumericObservedValue>(topicname);

  // Create DataReader
  DDS::DataReader *reader = sub->create_datareader_with_profile(
    topic,
    qoslibraryname,
    qosprofilename,
    0,
    DDS::STATUS_MASK_NONE);

  if (!reader)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DataReader";
    throw errss.str();
  }

  // Downcast the generic data reader to DataReader of specific type
  _reader = ice::NumericObservedValueDataReader::narrow(reader);
  if (!_reader)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to downcast DataReader";
    throw errss.str();
  }

  // This WaitSet object will be used to block a thread until one or more
  // conditions become true.
  _waitSet = new (std::nothrow) DDS::WaitSet();
  if (!_waitSet)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create WaitSet";
    throw errss.str();
  }

  // Use this status condition to wake up the thread when data available
  _condition = _reader->get_statuscondition();

  // Wake up the thread when data available, liveliness change, instance
  // disposed or instance unregistered
  _condition->set_enabled_statuses(DDS_LIVELINESS_CHANGED_STATUS);
  if (!_condition)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to initialize condition";
    throw errss.str();
  }

  _instance_alive = _reader->create_readcondition(
    DDS_ANY_SAMPLE_STATE,
    DDS_ANY_VIEW_STATE,
    DDS_ALIVE_INSTANCE_STATE);
  _instance_disposed = _reader->create_readcondition(
    DDS_ANY_SAMPLE_STATE,
    DDS_ANY_VIEW_STATE,
    DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE);
  _instance_no_writers = _reader->create_readcondition(
    DDS_ANY_SAMPLE_STATE,
    DDS_ANY_VIEW_STATE,
    DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);

  // Attach conditions to WaitSet
//  _waitSet->attach_condition(_condition);
  _waitSet->attach_condition(_instance_alive);
  _waitSet->attach_condition(_instance_disposed);
  _waitSet->attach_condition(_instance_no_writers);
  return rc;
}

// -------------------------------------------------------------------------
// Wait for data
void NumericReaderInterface::WaitForData()
{
  const char *sfn {"NumericReaderInterface::WaitForData"};
  DDS::ConditionSeq active_conditions;
  DDS::SampleInfoSeq info_seq;
  ice::NumericObservedValueSeq data_seq;

  // How long to block for data
  DDS_Duration_t timeout {0, 1000 * 1000}; // 1ms

  while (true)
  {
    // Block thread for data to arrive
    DDS::ReturnCode_t retcode = _waitSet->wait(active_conditions, timeout);

    if (retcode != DDS::RETCODE_OK)
    {
      // OK to timeout
      if (retcode == DDS::RETCODE_TIMEOUT) continue;

      // But anything else bad
      std::stringstream errss;
      errss << sfn << ": Error " << retcode << " waiting for data";
      throw errss.str();
    }

    for (int i = 0; i < active_conditions.length(); ++i)
    {
      if (active_conditions[i] == _instance_alive)
      {
        DDS::ReturnCode_t localretcode = _reader->take_w_condition(
          data_seq,
          info_seq,
          DDS::LENGTH_UNLIMITED,
          _instance_alive);
        if (localretcode != DDS_RETCODE_OK)
        {
          std::stringstream errss;
          errss << sfn << ": Error " << retcode << " taking data _instance_alive";
          throw errss.str();
        }

        // Handle DDS_ALIVE_INSTANCE_STATE

        for (int j = 0; j < data_seq.length(); j++)
        {
          if (!info_seq[j].valid_data)
          {
            std::stringstream errss;
            errss << sfn << ": _instance_alive invalid info_seq data";
            throw errss.str();
          }

          //cout << sfn << ": Data received" << endl;
          // emit a signal here with the data value
          ice::NumericObservedValueTypeSupport::print_data(&data_seq[j]);
        }
        _reader->return_loan(data_seq, info_seq);
      }
      else if (active_conditions[i] == _instance_disposed)
      {
        DDS::ReturnCode_t localretcode = _reader->take_w_condition(
          data_seq,
          info_seq,
          DDS::LENGTH_UNLIMITED,
          _instance_disposed);
        if (localretcode != DDS_RETCODE_OK)
        {
          std::stringstream errss;
          errss << sfn << ": Error " << retcode
            << " taking data _instance_disposed";
          throw errss.str();
        }

        // Handle DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE

        for (int j = 0; j < data_seq.length(); j++)
        {
       	  // find data instance by retrieving keys associated with instance
          ice::NumericObservedValue *data_instance =
            ice::NumericObservedValueTypeSupport::create_data();
          if (!((info_seq[j].instance_handle).isValid))
          {
            std::stringstream errss;
            errss << sfn
              << ": _instance_disposed invalid info_seq instance handle";
            throw errss.str();
          }
          retcode =
            _reader->get_key_value(*data_instance,info_seq[j].instance_handle);
          if (retcode != DDS_RETCODE_OK)
          {
            std::stringstream errss;
            errss << sfn << ": Error " << retcode
              << " getting key values for _instance_disposed";
            throw errss.str();
          }
          std::cout << sfn << ": Data _instance_disposed" << std::endl;
          // emit a signal here with data_instance (contains key values)
          // to indicate data are gone
        }
        _reader->return_loan(data_seq, info_seq);
      }
      else if (active_conditions[i] == _instance_no_writers)
      {
        DDS::ReturnCode_t localretcode = _reader->take_w_condition(
          data_seq,
          info_seq,
          DDS::LENGTH_UNLIMITED,
          _instance_no_writers);
        if (localretcode != DDS_RETCODE_OK)
        {
          std::stringstream errss;
          errss << sfn << ": Error " << retcode
            << " taking data _instance_no_writers";
          throw errss.str();
        }

        // Handle DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE

        for (int j = 0; j < data_seq.length(); j++)
        {
          // find data instance by retrieving keys associated with instance
          ice::NumericObservedValue *data_instance =
            ice::NumericObservedValueTypeSupport::create_data();
          if ((!(info_seq[j].instance_handle).isValid))
          {
            std::stringstream errss;
            errss << sfn
              << ": _instance_no_writers invalid info_seq instance handle";
            throw errss.str();
          }
          retcode = _reader->get_key_value(
            *data_instance,
            info_seq[j].instance_handle);
          if (retcode != DDS_RETCODE_OK)
          {
            std::stringstream errss;
            errss << sfn << ": Error " << retcode
              << " getting key values for _instance_no_writers";
            throw errss.str();
          }
          std::cout << sfn << ": Data _instance_no_writers" << std::endl;
          // emit a signal here with data_instance (contains key values)
          // to indicate samples are gone.
        }
        _reader->return_loan(data_seq, info_seq);
      }
#if 0
      else if (active_conditions[i] == _condition)
      {
        DDS_StatusMask triggeredmask = _reader->get_status_changes();

        if (triggeredmask & DDS_LIVELINESS_CHANGED_STATUS)
        {
          DDS_LivelinessChangedStatus st;
          _reader->get_liveliness_changed_status(st);
          printf("Liveliness changed => Alive count = %d\n",st.alive_count);
          printf("Liveliness changed => Not Alive count = %d\n",st.not_alive_count);
          printf("Liveliness changed => Alive count change = %d\n",st.alive_count_change);
          printf("Liveliness changed => Not Alive count change = %d\n",st.not_alive_count_change);
        }
      }
#endif
    }
  }
}

// -------------------------------------------------------------------------
// Get data
bool NumericReaderInterface::GetData(
  const DDS_Duration_t &timeout,
  ice::NumericObservedValue *data_sample)
{
  const char *sfn {"NumericReaderInterface::GetData"};
  bool have_data {false};
  DDS::ConditionSeq active_conditions;
  DDS::SampleInfoSeq info_seq;
  ice::NumericObservedValueSeq data_seq;

  // Block thread for data to arrive
  DDS::ReturnCode_t retcode = _waitSet->wait(active_conditions, timeout);

  if (retcode != DDS::RETCODE_OK)
  {
    // OK to timeout
    if (retcode == DDS::RETCODE_TIMEOUT) return have_data;

    // But anything else bad
    std::stringstream errss;
    errss << sfn << ": Error " << retcode << " waiting for data";
    throw errss.str();
  }

  for (int i = 0; (i < active_conditions.length()) && !have_data; ++i)
  {
    if (active_conditions[i] == _instance_alive)
    {
      retcode = _reader->take_w_condition(
        data_seq,
        info_seq,
        1,  // max_samples- the maximum number of samples to be returned
        _instance_alive);
      if (retcode != DDS_RETCODE_OK)
      {
        std::stringstream errss;
        errss << sfn << ": Error " << retcode << " taking data _instance_alive";
        throw errss.str();
      }

      // Handle DDS_ALIVE_INSTANCE_STATE

      for (int j = 0; j < data_seq.length(); j++)
      {
        if (!info_seq[j].valid_data)
        {
          std::stringstream errss;
          errss << sfn << ": _instance_alive invalid info_seq data";
          throw errss.str();
        }
        //cout << sfn << ": Sample data received" << endl;
        // emit a signal here with the data_seq value
        ice::NumericObservedValueTypeSupport::copy_data(data_sample, &data_seq[j]);
        have_data = true;
        break;
      }
      _reader->return_loan(data_seq, info_seq);
    }
    else if (active_conditions[i] == _instance_disposed)
    {
      retcode = _reader->take_w_condition(
        data_seq,
        info_seq,
        DDS::LENGTH_UNLIMITED,
        _instance_disposed);
      if (retcode != DDS_RETCODE_OK)
      {
        std::stringstream errss;
        errss << sfn << ": Error " << retcode
          << " taking data _instance_disposed";
        throw errss.str();
      }

      // Handle DDS_NOT_ALIVE_DISPOSED_INSTANCE_STATE

      for (int j = 0; j < data_seq.length(); j++)
      {
        // find data instance by retrieving keys associated with instance
        ice::NumericObservedValue *data_instance =
          ice::NumericObservedValueTypeSupport::create_data();
        if (!((info_seq[j].instance_handle).isValid))
        {
          std::stringstream errss;
          errss << sfn
            << ": _instance_disposed invalid info_seq instance handle";
          throw errss.str();
        }
        retcode =
          _reader->get_key_value(*data_instance, info_seq[j].instance_handle);
        if (retcode != DDS_RETCODE_OK)
        {
          std::stringstream errss;
          errss << sfn << ": Error " << retcode
            << " getting key values for _instance_disposed";
          throw errss.str();
        }
        std::cout << sfn << ": Data _instance_disposed" << std::endl;
        // emit a signal here with data_instance (contains key values)
        // to indicate samples are gone
      }
      _reader->return_loan(data_seq, info_seq);
    }
    else if (active_conditions[i] == _instance_no_writers)
    {
      retcode = _reader->take_w_condition(
        data_seq,
        info_seq,
        DDS::LENGTH_UNLIMITED,
        _instance_no_writers);
      if (retcode != DDS_RETCODE_OK)
      {
        std::stringstream errss;
        errss << sfn << ": Error " << retcode
          << " taking data _instance_no_writers";
        throw errss.str();
      }

      // Handle DDS_NOT_ALIVE_NO_WRITERS_INSTANCE_STATE

      for (int j = 0; j < data_seq.length(); j++)
      {
        // find sample data instance by retrieving keys associated with instance
        ice::NumericObservedValue *data_instance =
          ice::NumericObservedValueTypeSupport::create_data();
        if (!((info_seq[j].instance_handle).isValid))
        {
          std::stringstream errss;
          errss << sfn
            << ": _instance_no_writers invalid info_seq instance handle";
          throw errss.str();
        }
        retcode = _reader->get_key_value(
          *data_instance,
          info_seq[j].instance_handle);
        if (retcode != DDS_RETCODE_OK)
        {
          std::stringstream errss;
          errss << sfn << ": Error " << retcode
            << " getting key values for _instance_no_writers";
          throw errss.str();
        }
        std::cout << sfn << ": Data _instance_no_writers" << std::endl;
        // emit a signal here with sample data instance (contains key values)
        // to indicate samples are gone
      }
      _reader->return_loan(data_seq, info_seq);
    }
  }
  return have_data;
}
