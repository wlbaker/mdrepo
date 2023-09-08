 /**
 * @file  MDSWriterInterface.cxx
 * @brief Manage DDS entities for writing the MDS type.
 */
//=============================================================================
#include "ndds/ndds_cpp.h"
#include "DDSCommunicator.h"
#include "DDSTypeWrapper.h"
#include "mds.h"
#include "mdsSupport.h"
#include "MDSWriterInterface.h"

// ----------------------------------------------------------------------------
MDSWriterInterface::MDSWriterInterface()
  : _communicator(0),
    _writer(0)
{
}

// ----------------------------------------------------------------------------
MDSWriterInterface::~MDSWriterInterface()
{
  Destroy();
}

// ----------------------------------------------------------------------------
// Destroyer.
// Delete the DataWriter, and Communicator objects
int MDSWriterInterface::Destroy()
{
  DDS_ReturnCode_t rc {DDS_RETCODE_OK};

  if (_writer)
  {
    DDS::Publisher *pub = _writer->get_publisher();
    if (pub) pub->delete_datawriter(_writer);
    _writer = 0;
  }
  delete _communicator;
  _communicator = 0;
  return rc;
}

// ----------------------------------------------------------------------------
// Initializer
// Create the domain participant, publisher, topic and writer.
int MDSWriterInterface::Initialize(
  const long domain_id,
  const char *topicname,
  const char *qoslibraryname,
  const char *qosprofilename)
{
  const char *sfn {"MDSWriterInterface::Initialize"};
  DDS_ReturnCode_t rc {DDS_RETCODE_OK};
  _communicator = new (std::nothrow) DDSCommunicator();

  // Create a DomainParticipant
  if (!_communicator->CreateParticipant(domain_id))
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DomainParticipant object";
    throw errss.str();
  }

  // Create a Publisher
  DDS::Publisher *pub = _communicator->CreatePublisher();
  if (!pub)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create Publisher object";
    throw errss.str();
  }

  // Create Topic
  DDS::Topic *topic =
    _communicator->CreateTopic<ice::MDS>(topicname);

  // Create DataWriter
  DDS::DataWriter *writer = pub->create_datawriter_with_profile(
    topic,
    qoslibraryname,
    qosprofilename,
    0,
    DDS::STATUS_MASK_NONE);

  if (!writer)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to create DataWriter";
    throw errss.str();
  }

  // Downcast the generic data writer to DataWriter of specific type
  _writer = ice::MDSDataWriter::narrow(writer);
  if (!_writer)
  {
    std::stringstream errss;
    errss << sfn << ": Failed to downcast DataWriter";
    throw errss.str();
  }
  return rc;
}

// ----------------------------------------------------------------------------
// Write the data using RTI Connext DDS to any DataReader
// that shares the same Topic
int MDSWriterInterface::Write(DdsAutoType<ice::MDS> data)
{
  DDS_ReturnCode_t rc {DDS_RETCODE_ERROR};  // assume fail
  if (_writer)
  {
    DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;
    _writer->register_instance(data);
    rc = _writer->write(data, handle);
  }
  return rc;
}

// ----------------------------------------------------------------------------
// Send a "data deleted" message. This calls unregister_instance to
// notify other applications that this data went away and should be deleted.
int MDSWriterInterface::Delete(DdsAutoType<ice::MDS> data)
{
  DDS_ReturnCode_t rc {DDS_RETCODE_ERROR};  // assume fail
  if (_writer)
  {
    DDS_InstanceHandle_t handle = DDS_HANDLE_NIL;

    // Note that delete maps to "unregister" in the RTI Connext DDS world. This
    // cleans up the instance entirely, so the space can be reused for another
    // instance. A call to "dispose" does not clean up the space for a new
    // instance. Rather, dispose marks the current instance disposed, which
    // provides for reuse of the same instance.
    rc = _writer->unregister_instance(data, handle);
//    if (rc == DDS_RETCODE_OK)
      rc = _writer->dispose(data, handle);
  }
  return rc;
}
