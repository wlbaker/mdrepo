/*
(c) 2005-2013 Copyright, Real-Time Innovations, Inc. All rights reserved.
RTI grants Licensee a license to use, modify, compile, and create derivative works
of the Software. Licensee has the right to distribute object form only for use with RTI
products. The Software is provided �as is�, with no warranty of any type, including
any warranty for fitness for any purpose. RTI is under no obligation to maintain or
support the Software. RTI shall not be liable for any incidental or consequential
damages arising out of the use or inability to use the software.
*/
#ifndef DDS_COMMUNICATOR_H
#define DDS_COMMUNICATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "ndds/ndds_cpp.h"
#include "ndds/ndds_namespace_cpp.h"

// ----------------------------------------------------------------------------
// Unregister types from the DomainParticipant.
// Types are automatically registered when you create the topic, and 
// unregistered at shutdown.
typedef DDS_ReturnCode_t (*unregister_fn)(DDSDomainParticipant *, const char *);

// ----------------------------------------------------------------------------
// UnregisterInfo
// Maintain a mapping between a data type and its unregister function. Used at
// shutdown when cleaning up the DomainParticipant and all of its registered
// data types.
struct UnregisterInfo 
{
  std::string typeName;
  unregister_fn unregisterFunction;
};

// ----------------------------------------------------------------------------
// DDSCommunicator:
// Use this class for RTI Connext DDS interfaces to create the core
// communication objects, such as a DomainParticipant, Publisher and/or 
// Subscriber.
class DDSCommunicator 
{
private:
  // Disallow use of implicitly generated member functions:
  DDSCommunicator (const DDSCommunicator  &src);
  DDSCommunicator  &operator=(const DDSCommunicator  &rhs);

  // Used to create other DDS entities
  DDS::DomainParticipant *_participant;

  // Used to create DataWriters
  DDS::Publisher *_pub;

  // Used to create DataReaders
  DDS::Subscriber *_sub;

  // Map type names and unregistration functions. CreateTopic() adds functions
  // to this, after each data type registers with the DomainParticipant. This
  // cleans up a [small] amount of memory that would otherwise appear as a
  // memory leak at shutdown.
  std::map<std::string, UnregisterInfo> _typeCleanupFunctions;

public:
  // CREATORS

  DDSCommunicator()
    : _participant(0),
      _pub(0),
      _sub(0)
  {
  }

  ~DDSCommunicator();

  // MANIPULATORS

  // --- Create a DomainParticipant --- 

  // A DomainParticipant starts the DDS discovery process. It creates several
  // threads, sends and receives discovery information over one or more
  // transports, and maintains an in-memory discovery database of remote
  // DomainParticipants, remote DataWriters, and remote DataReaders.
  //
  // Quality of Service can apply at the DomainParticipant level. This QoS
  // controls the characteristics of
  // 1. Transport properties such as type of network (UDPv4, UDPv6, shared
  //    memory) or which network interfaces it can use.
  // 2. Which applications this discovers. By default, apps discover other DDS
  //    applications over multicast, loopback, and shared memory.
  // 3. Resource limits for the DomainParticipant.
  //
  // For more information on participant QoS, see the .xml files in the
  // Config directory

  // Create a DomainParticipant with default QoS in domain 0
  DDS::DomainParticipant *CreateParticipant();

  // Create a DomainParticipant with default QoS in the specified domain
  DDS::DomainParticipant *CreateParticipant(long domain);

  // Create a DomainParticipant with specified QoS in the specified domain
  DDS::DomainParticipant *CreateParticipant(
    long domain,
    const char *participantQosLibrary,
    const char *participantQosProfile);

  // Load a set of XML files to load QoS profile information.
  // Creates a DomainParticipant with specified QoS in the specified domain.
  DDS::DomainParticipant *CreateParticipant(
    long domain,
    std::vector<std::string>fileNames,
    const char *participantQosLibrary,
    const char *participantQosProfile);

  // --- Get the DomainParticipant --- 

  // --- Create a Publisher --- 

  // The Publisher object is a factory to create type-specific DataWriters.
  // Note that you can use the same publisher for multiple DataWriters - 
  // typically you create zero or one Publisher per application.

  // Create a Publisher with default QoS
  DDS::Publisher *CreatePublisher();

  // Create a Publisher with specified QoS
  DDS::Publisher *CreatePublisher(
    const char *qosLibrary, 
    const char *qosProfile);


  // --- Create a Subscriber --- 

  // The Subscriber object is a factory to create type-specific DataReaders.
  // Note that you can use the same subscriber for multiple DataReaders - 
  // typically you create zero or one Subscriber per application.

  // Create a Subscriber with default QoS
  DDS::Subscriber *CreateSubscriber();

  // Create a Subscriber with specified QoS
  DDS::Subscriber *CreateSubscriber(
    const char *qosLibrary,
    const char *qosProfile);
  
  // --- Create a Topic --- 

  // Create a Topic templatized with the type name.
  // Provides data type store, and delete at shutdown.
  template <typename T>
  DDS::Topic *CreateTopic(const char *topicname)
  {
    const char *sfn = "DDSCommunicator::CreateTopic";

    // Register the data type with the DomainParticipant.
    // This tells the DomainParticipant how to create/destroy/serialize/
    // deserialize this data type.
    const char *typeName = T::TypeSupport::get_type_name();

    DDS_ReturnCode_t retcode =
      T::TypeSupport::register_type(GetParticipant(), typeName);
    if (retcode != DDS_RETCODE_OK) 
    {
      std::stringstream errss;
      errss << sfn << ": Failed to register type. Already regisetered?";
      throw errss.str();
    }

    // Create the Topic object, using the associated data type that
    // was registered above.
    DDS::Topic *topic = GetParticipant()->create_topic(
      topicname,
      typeName,
      DDS_TOPIC_QOS_DEFAULT,
      0, /* listener */
      DDS_STATUS_MASK_NONE);
    if (!topic) 
    {
      std::stringstream errss;
      errss << sfn << ": Failed to create Topic "
        << topicname << ". Already created?";
      throw errss.str();
    }

    // Save the type unregister information for a clean shutdown. This prevents
    // an apparent memory leak at shutdown.
    UnregisterInfo unregisterInfo;
    unregisterInfo.typeName = typeName;
    unregisterInfo.unregisterFunction = T::TypeSupport::unregister_type;
    _typeCleanupFunctions[typeName] = unregisterInfo;
    return topic;
  }

  // ACCESSORS

  DDS::DomainParticipant *GetParticipant() { return _participant; }
  DDS::Publisher *GetPublisher() { return _pub; }
  DDS::Subscriber *GetSubscriber() { return _sub; }
};

#endif
