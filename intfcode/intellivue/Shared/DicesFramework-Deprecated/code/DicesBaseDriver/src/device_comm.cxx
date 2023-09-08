/**
 * @file device_comm.cxx
 * @brief Defines a base class which handles all communication between the
 * driver and the device.
 * @author Michael Szwaja
 */
//=============================================================================
#include "device_comm.h"
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "Communication/base-communication.h"
#include "device_comm.h"
#include "parser.h"
#include "dices_rc_driver.h"
#include "Communication/rc-base-communication.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

DeviceComm::DeviceComm(BaseComm* base_comm, Parser* parser)
  : _base_comm(base_comm),
  _parser(parser) { }

DeviceComm::~DeviceComm() { }

DicesRcDriver DeviceComm::InitComm()
{
  static const char* sfn = "DeviceComm::InitComm()";

  if (!_base_comm)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Pointer to base communication object is a null pointer.");
    return DicesRcDriver::BASE_COMM_POINTER_IS_NULL;
  }

  if (!_parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Pointer to parser object is a null pointer.");
    return DicesRcDriver::PARSER_POINTER_IS_NULL;
  }

  DicesRcBaseComm status = _base_comm->Open();
  if (status != DicesRcBaseComm::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << DicesRcBaseCommStatusMessage::
      DicesRcBaseCommToString(status));
    return DicesRcDriver::BASE_COMM_OPEN_FAILURE;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver DeviceComm::ShutdownComm()
{
  static const char* sfn = "DeviceComm::ShutdownComm()";

  DicesRcBaseComm status = _base_comm->Close();
  if (status != DicesRcBaseComm::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << DicesRcBaseCommStatusMessage::
      DicesRcBaseCommToString(status));
    return DicesRcDriver::BASE_COMM_CLOSE_FAILURE;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver DeviceComm::SendToDevice()
{
  static const char* sfn = "DeviceComm::SendToDevice()";

  ssize_t command_len = _parser->get_command_length();

  if (command_len > 0)
  {
    uint8_t* pcommand = new (std::nothrow) uint8_t[command_len];
    if (!pcommand)
    {
      LOG4CPLUS_ERROR(root_logger, " Unable to allocate space for command buffer.");
      return DicesRcDriver::COMMAND_BUFFER_ALLOCATION_FAILURE;
    }

    DicesRcDriver status = _parser->get_raw_command(pcommand, command_len);
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      return status;
    }

    DicesRcBaseComm base_comm_status = _base_comm->Send(pcommand, command_len);
    if (base_comm_status != DicesRcBaseComm::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn << DicesRcBaseCommStatusMessage::
        DicesRcBaseCommToString(base_comm_status));
      return DicesRcDriver::BASE_COMM_SEND_FAILURE;
    }
  }
  return DicesRcDriver::OK;
}

DicesRcDriver DeviceComm::ReadFromDevice()
{
  static const char* sfn = "DeviceComm::ReadFromDevice()";

  ssize_t max_response_len = _parser->get_max_response_length();
  ssize_t nbytes_read = 0;
  uint8_t* response_buffer = new (std::nothrow) uint8_t[max_response_len];
  if (!response_buffer)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Failed to allocate space for response buffer.");
    return DicesRcDriver::RESPONSE_BUFFER_POINTER_IS_NULL;
  }

  memset(response_buffer, 0x00, max_response_len);

  DicesRcBaseComm base_comm_status = _base_comm->Read(response_buffer, max_response_len, &nbytes_read);
  if (base_comm_status != DicesRcBaseComm::OK)
  {
    LOG4CPLUS_INFO(root_logger, sfn << DicesRcBaseCommStatusMessage::DicesRcBaseCommToString(base_comm_status));
    delete [] response_buffer;
    response_buffer = 0;

    // Translate BaseComm return codes into Driver return codes.
    switch (base_comm_status)
    {
      case DicesRcBaseComm::READ_TIMEOUT:
        return DicesRcDriver::READ_TIMEOUT;
        break;
      case DicesRcBaseComm::DEVICE_DISCONNECTION:
        return DicesRcDriver::DEVICE_DISCONNECTION;
        break;
      default:
        return DicesRcDriver::BASE_COMM_READ_FAILURE;
        break;
    }
  }

  DicesRcDriver status = _parser->set_raw_response(response_buffer, nbytes_read);
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
  }

  delete [] response_buffer;
  response_buffer = 0;
  return status;
}

DicesRcDriver DeviceComm::Flush()
{
  static const char* sfn = "DeviceComm::Flush()";

  DicesRcBaseComm status = _base_comm->Flush();
  if (status != DicesRcBaseComm::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << DicesRcBaseCommStatusMessage::
      DicesRcBaseCommToString(status));
    return DicesRcDriver::BASE_COMM_FLUSH_FAILURE;
  }
  return DicesRcDriver::OK;
}

