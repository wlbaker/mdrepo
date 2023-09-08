#ifndef ICE_UTILITIES_H
#define ICE_UTILITIES_H

#include <ndds/ndds_namespace_cpp.h>

#include "base-logger.h"
#include "rc-ice-domain-reader.h"

enum class DicesRcICEDomainReader;

namespace IceUtilities
{
  template <typename T>
  DicesRcICEDomainReader read_samples_for_condition(
        typename T::DataReader *topic_reader,
        DDS::ReadCondition *read_condition,
        std::function<void(T*, DDS::SampleInfo*)> ProcessSample);

  template <typename T>
  DicesRcICEDomainReader take_samples_for_condition(
        typename T::DataReader *topic_reader,
        DDS::ReadCondition *read_condition,
        std::function<void(T*, DDS::SampleInfo*)> ProcessSample);
}

template <typename T>
DicesRcICEDomainReader IceUtilities::read_samples_for_condition(
      typename T::DataReader *topic_reader,
      DDS::ReadCondition *read_condition,
      std::function<void(T*, DDS::SampleInfo*)> ProcessSample)
{
  typename T::Seq samples;
  DDS::SampleInfoSeq info_seq;
  DDS::ReturnCode_t retcode;

  retcode = topic_reader->read_w_condition(
              samples,
              info_seq,
              DDS::LENGTH_UNLIMITED,
              read_condition);

  if (retcode == DDS::RETCODE_OK)
  {
    for (int j = 0; j < samples.length(); j++)
    {
      if(info_seq[j].instance_state & DDS::ALIVE_INSTANCE_STATE &&
         info_seq[j].valid_data)
      {
        ProcessSample(&samples[j], &info_seq[j]);
      }
      else
      {
        T* key_holder = T::TypeSupport::create_data();

        if (!key_holder)
        {
          LOG4CPLUS_ERROR(
                DicesLogger::get_instance()->get_logger(),
                "Failed to create data.");
          continue;
        }

        DDS::ReturnCode_t key_ret_code;
        key_ret_code = topic_reader->get_key_value(
                         *key_holder,
                         info_seq[j].instance_handle);
        if (key_ret_code != DDS::RETCODE_OK)
        {
          LOG4CPLUS_ERROR(
                DicesLogger::get_instance()->get_logger(),
                "Failed to get key value.");
          continue;
        }

        ProcessSample(key_holder, &info_seq[j]);
      }
    }

    topic_reader->return_loan(samples, info_seq);
  }
  else if(retcode != DDS::RETCODE_NO_DATA)
  {
    LOG4CPLUS_ERROR(
          DicesLogger::get_instance()->get_logger(),
          "error " << retcode << " when taking sequence");
    return DicesRcICEDomainReader::FAIL;
  }

  return DicesRcICEDomainReader::OK;
}

template <typename T>
DicesRcICEDomainReader IceUtilities::take_samples_for_condition(
      typename T::DataReader *topic_reader,
      DDS::ReadCondition *read_condition,
      std::function<void(T*, DDS::SampleInfo*)> ProcessSample)
{
  typename T::Seq samples;
  DDS::SampleInfoSeq info_seq;
  DDS::ReturnCode_t retcode;

  if(!topic_reader)
  {
    LOG4CPLUS_ERROR(
      DicesLogger::get_instance()->get_logger(),
      "error taking samples, topic reader is null");
    return DicesRcICEDomainReader::FAIL;
  }

  if(!read_condition)
  {
    LOG4CPLUS_ERROR(
      DicesLogger::get_instance()->get_logger(),
      "error taking samples, read condition is null");
    return DicesRcICEDomainReader::FAIL;
  }

  retcode = topic_reader->take_w_condition(
              samples,
              info_seq,
              DDS::LENGTH_UNLIMITED,
              read_condition);

  if (retcode == DDS::RETCODE_OK)
  {
    for (int j = 0; j < samples.length(); j++)
    {
      if(info_seq[j].instance_state & DDS::ALIVE_INSTANCE_STATE &&
         info_seq[j].valid_data)
      {
        ProcessSample(&samples[j], &info_seq[j]);
      }
      else
      {
        T* key_holder = T::TypeSupport::create_data();

        if (!key_holder)
        {
          LOG4CPLUS_ERROR(
                DicesLogger::get_instance()->get_logger(),
                "Failed to create data.");
          continue;
        }

        DDS::ReturnCode_t key_ret_code;
        key_ret_code = topic_reader->get_key_value(
                         *key_holder,
                         info_seq[j].instance_handle);
        if (key_ret_code != DDS::RETCODE_OK)
        {
          LOG4CPLUS_ERROR(
                DicesLogger::get_instance()->get_logger(),
                "Failed to get key value.");
          continue;
        }

        ProcessSample(key_holder, &info_seq[j]);
      }
    }

    topic_reader->return_loan(samples, info_seq);
  }
  else if(retcode != DDS::RETCODE_NO_DATA)
  {
    LOG4CPLUS_ERROR(
          DicesLogger::get_instance()->get_logger(),
          "error " << retcode << " when taking sequence");
    return DicesRcICEDomainReader::FAIL;
  }

  return DicesRcICEDomainReader::OK;
}

#endif
