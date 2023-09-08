/******************************************************************************
(c) 2005-2013 Copyright, Real-Time Innovations, Inc. All rights reserved.                                  
RTI grants Licensee a license to use, modify, compile, and create derivative works 
of the Software. Licensee has the right to distribute object form only for use with RTI 
products. The Software is provided �as is�, with no warranty of any type, including 
any warranty for fitness for any purpose. RTI is under no obligation to maintain or 
support the Software. RTI shall not be liable for any incidental or consequential 
damages arising out of the use or inability to use the software.
******************************************************************************/
#include "DDSCommunicator.h"

// ----------------------------------------------------------------------------
// Destroy a DDS communication interface.
// 1. Delete all entities created by the DomainParticipant object.
// 2. Clean up types registered with the DomainParticipant. (Note that
//    failure to unregister all types causes a [small] amount of memory to
//    leak at shutdown.)
// 3. Delete the DomainParticipant.
// 4. Finalize the DomainParticipantFactory.
DDSCommunicator::~DDSCommunicator() 
{
  if (_participant) 
  {
    // Delete DataWriters, DataReaders, Topics, Subscribers, and Publishers
    // created by this DomainParticipant.
    _participant->delete_contained_entities();

    // Unregister all the data types registered with this DomainParticipant
    for (std::map<std::string, UnregisterInfo>::iterator it =
          _typeCleanupFunctions.begin();
        it != _typeCleanupFunctions.end();
        it++)
    {
      (*it).second.unregisterFunction(_participant, (*it).first.c_str());
    }

    // Delete the DomainParticipant
    TheParticipantFactory->delete_participant(_participant);

    // Finalize the participant factory.
    //
    // IMPORTANT NOTE:
    // This does not work if the application has multiple communicators, for
    // example, in different DDS domains. In that case, you must use care to
    // finalize the participant factory only after the application deletes all
    // DomainParticipants.
//    TheParticipantFactory->finalize_instance();
  }
}

// --- Create a DomainParticipant --- 

// ----------------------------------------------------------------------------
// Create a DomainParticipant with a specified domain ID.
DDS::DomainParticipant *DDSCommunicator::CreateParticipant(long domain) 
{
  const char *sfn = "DDSCommunicator::CreateParticipant";

  _participant = TheParticipantFactory->create_participant(
    domain,
    DDS::PARTICIPANT_QOS_DEFAULT,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_participant)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  } 
  return _participant;
}

// ----------------------------------------------------------------------------
// Create a DomainParticipant with a domain ID of zero.
DDS::DomainParticipant *DDSCommunicator::CreateParticipant()
{
  DDS::DomainParticipant *participant = CreateParticipant(0);
  return participant;
}

// ----------------------------------------------------------------------------
// Create a DomainParticipant with specified domain ID and specified QoS.
DDS::DomainParticipant *DDSCommunicator::CreateParticipant(
  long domain,
  const char *participantQosLibrary, 
  const char *participantQosProfile) 
{
  const char *sfn = "DDSCommunicator::CreateParticipant";

  _participant = TheParticipantFactory->create_participant_with_profile(
    domain,
    participantQosLibrary,
    participantQosProfile,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_participant) 
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  }
  return _participant;
}

// ----------------------------------------------------------------------------
// Create a DomainParticipant with a specified domain ID, specified QoS file
// names, and specified QoS.
DDS::DomainParticipant *DDSCommunicator::CreateParticipant(
  long domain,
  std::vector<std::string>fileNames,
  const char *participantQosLibrary,
  const char *participantQosProfile)
{
  const char *sfn = "DDSCommunicator::CreateParticipant";

  // Add a list of explicit file names to the DomainParticipantFactory.
  // This gives the middleware a set of places to search for the files.
  DDS::DomainParticipantFactoryQos factoryQos;
  TheParticipantFactory->get_qos(factoryQos);
  DDS_Long url_profile_seq_size = static_cast<DDS_Long>(fileNames.size());

  factoryQos.profile.url_profile.ensure_length(
    url_profile_seq_size,
    url_profile_seq_size);

  for (unsigned int i = 0; i < fileNames.size(); i++)
  {
    // NOTE: Copy the file names here so they remain in scope.
    factoryQos.profile.url_profile[i] =
      DDS_String_dup(fileNames[i].c_str());
  }

  DDS_ReturnCode_t retcode = TheParticipantFactory->set_qos(factoryQos);
    
  if (retcode != DDS_RETCODE_OK)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  }

  // Actually create the DomainParticipant
  _participant = TheParticipantFactory->create_participant_with_profile(
    domain,
    participantQosLibrary,
    participantQosProfile,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_participant)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  }
  return _participant;
}

// ----------------------------------------------------------------------------
// Create a Publisher.
// Used in the application to create type-specific DataWriter objects.
DDS::Publisher *DDSCommunicator::CreatePublisher()
{
  const char *sfn = "DDSCommunicator::CreatePublisher";

  if (!GetParticipant()) 
  {
    std::stringstream errss;
    errss << sfn << ": NULL DomainParticipant - communicator not initialized";
    std::cout << errss.str() << std::endl;
    throw errss.str();
  }

  // Create the Publisher.
  // Used to create type-specific DataWriter objects that actually send data.
  _pub = GetParticipant()->create_publisher(
    DDS::PUBLISHER_QOS_DEFAULT,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_pub)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Publisher";
    throw errss.str();
  }
  return _pub;
}

// ----------------------------------------------------------------------------
// Create a Publisher with specified QoS.
// Used in application to create type-specific DataWriter objects.
DDS::Publisher *DDSCommunicator::CreatePublisher(
  const char *qosLibrary, 
  const char *qosProfile)
{
  const char *sfn = "DDSCommunicator::CreatePublisher";

  if (!GetParticipant()) 
  {
    std::stringstream errss;
    errss << sfn << ": NULL DomainParticipant - communicator not initialized";
    std::cout << errss.str() << std::endl;
    throw errss.str();
  }

  // Create a Publisher.
  // Used to create type-specific DataWriter objects that actually send data.
  _pub = GetParticipant()->create_publisher_with_profile(
    qosLibrary,
    qosProfile,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_pub) 
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Publisher";
    throw errss.str();
  }
  return _pub;
}

// ----------------------------------------------------------------------------
// Create a Subscriber.
// Used in application to create type-specific DataReader objects.
DDS::Subscriber *DDSCommunicator::CreateSubscriber()
{
  const char *sfn = "DDSCommunicator::CreateSubscriber";

  if (!GetParticipant())
  {
    std::stringstream errss;
    errss << sfn << ": NULL DomainParticipant - communicator not initialized";
    std::cout << errss.str() << std::endl;
    throw errss.str();
  }

  // Create a Subscriber.
  // Used to create type-specific DataRreader objects that actually receive
  // data. The application can use this single Subscriber object, created here
  // in the DDSCommunicator class, to create multiple DDS DataReaders.
  _sub = GetParticipant()->create_subscriber(
    DDS::SUBSCRIBER_QOS_DEFAULT,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_sub)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Subscriber";
    throw errss.str();
  }
  return _sub;
}

// ----------------------------------------------------------------------------
// Create a Subscriber with specified QoS.
// Used in application to create type-specific DataReader objects.
DDS::Subscriber *DDSCommunicator::CreateSubscriber(
  const char *qosLibrary,
  const char *qosProfile)
{
  const char *sfn = "DDSCommunicator::CreateSubscriber";

  if (!GetParticipant())
  {
    std::stringstream errss;
    errss << sfn << ": NULL DomainParticipant - communicator not initialized";
    std::cout << errss.str() << std::endl;
    throw errss.str();
  }

  // Create a Subscriber.
  // Used to create type-specific DataRreader objects that actually receive
  // data. The application can use this single Subscriber object, created here
  // in the DDSCommunicator class, to create multiple DDS DataReaders.
  _sub = GetParticipant()->create_subscriber_with_profile(
    qosLibrary,
    qosProfile,
    0,
    DDS::STATUS_MASK_NONE);
  if (!_sub) 
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Subscriber";
    throw errss.str();
  }
  return _sub;
}
