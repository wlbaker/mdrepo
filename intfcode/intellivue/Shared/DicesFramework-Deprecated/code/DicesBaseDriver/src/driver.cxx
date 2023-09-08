/*
 * File:   driver.cxx
 * Author: Robert England
 *
 * Created on November 18, 2014
 * Last Modified on November 19, 2014
 */

#include "driver.h"

#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/configurator.h>
#include <log4cplus/helpers/loglog.h>
#include <log4cplus/helpers/stringhelper.h>
#include <mutex>
#include <thread>
#include <chrono>

#include "dices_rc_driver.h"
#include "parser.h"
#include "bus_comm.h"
#include "device_comm.h"

static log4cplus::Logger root_logger = log4cplus::Logger::getRoot();

Driver::~Driver()
{
  static const char* sfn = "Driver::~Driver() ";
  DicesRcDriver status = ShutdownDDS();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
  }
}

bool Driver::get_quit_flag()
{
  std::lock_guard<std::mutex> lock(_quit_flag_mutex);
  return _quit_flag;
}

void Driver::set_quit_flag(bool torf)
{
  std::lock_guard<std::mutex> lock(_quit_flag_mutex);
  _quit_flag = torf;
}

std::chrono::milliseconds Driver::get_sleep_time_ms()
{
  return _sleep_time_ms;
}

void Driver::set_sleep_time_ms(std::chrono::milliseconds milliseconds)
{
  _sleep_time_ms = milliseconds;
}

DicesRcDriver Driver::InitDDS(Parser* parser)
{
  static const char* sfn = "Driver::InitDDS() ";
  if (!parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Function argument parser is a null pointer");
    return DicesRcDriver::FAIL;
  }

  // Call shutdown in case _bus_comm was already initialized
  DicesRcDriver status = ShutdownDDS();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  _bus_comm = new (std::nothrow) BusComm(parser);
  if (!_bus_comm)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create BusComm");
    return DicesRcDriver::FAIL;
  }

  status = _bus_comm->InitDDSObjects();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  status = parser->AllocateMessageBuffers();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  status = parser->PopulateDDSInstances();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }
  return DicesRcDriver::OK;
}

DicesRcDriver Driver::ShutdownDDS()
{
  static const char* sfn = "Driver::ShutdownDDS() ";

  if (!_bus_comm) return DicesRcDriver::OK;

  DicesRcDriver status = _bus_comm->ShutdownDDSObjects();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  delete _bus_comm;
  _bus_comm = nullptr;

  return DicesRcDriver::OK;
}

DicesRcDriver Driver::RunDriver(Parser* parser, BaseComm* basecomm)
{
  static const char* sfn = "Driver::RunDriver()";

  if (!parser)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Function argument parser is a null "
      "pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (!basecomm)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << " Function argument basecomm is a "
      "null pointer.");
    return DicesRcDriver::BAD_FUNCTION_ARGUMENT;
  }

  if (!_bus_comm)
  {
    LOG4CPLUS_ERROR(root_logger, sfn << "Failed to create BusComm. Call Driver::InitDDS() function");
    return DicesRcDriver::FAIL;
  }

  set_quit_flag(false);

  DeviceComm dev_comm(basecomm, parser);

  DicesRcDriver status = parser->AllocateMessageBuffers();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
    return status;
  }

  status = dev_comm.InitComm();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));

    DicesRcDriver parser_status = parser->DeallocateMessageBuffers();
    if (parser_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(parser_status));
    }

    return status;
  }

  while ((status = parser->GetHandshakeCmd()) != DicesRcDriver::HANDSHAKE_DONE)
  {
    std::this_thread::sleep_for(_sleep_time_ms);

    if (status != DicesRcDriver::OK) break;

    if (parser->get_command_length() != 0)
    {
      status = dev_comm.SendToDevice();
      if (status != DicesRcDriver::OK) break;
    }

    status = dev_comm.ReadFromDevice();
    if (status != DicesRcDriver::OK)
    {
      if (status != DicesRcDriver::READ_TIMEOUT) break;

      // Log warning for read timeouts and ignore them.
      LOG4CPLUS_INFO(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      status = DicesRcDriver::OK;
    }

    status = parser->ParseResponse();
    if (status != DicesRcDriver::OK) break;
  }

  // Check status after handshaking
  if (status != DicesRcDriver::OK && status != DicesRcDriver::HANDSHAKE_DONE)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));

    DicesRcDriver shutdown_status = dev_comm.ShutdownComm();
    if (shutdown_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(shutdown_status));
    }

    shutdown_status = parser->DeallocateMessageBuffers();
    if (shutdown_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(shutdown_status));
    }

    return status;
  }

  status = _bus_comm->Associate();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));

    DicesRcDriver shutdown_status = dev_comm.ShutdownComm();
    if (shutdown_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(shutdown_status));
    }

    shutdown_status = parser->DeallocateMessageBuffers();
    if (shutdown_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(shutdown_status));
    }

    return status;
  }

  while (!get_quit_flag())
  {
    std::this_thread::sleep_for(_sleep_time_ms);

    status = _bus_comm->ReadFromBus();
    if (status == DicesRcDriver::QUIT)
    {
      set_quit_flag(true);
    }
    else if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      break;
    }

    status = parser->ParseCommand();
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      break;
    }

    status = dev_comm.SendToDevice();
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      break;
    }

    status = dev_comm.ReadFromDevice();
    if (status != DicesRcDriver::OK)
    {
      if (status != DicesRcDriver::READ_TIMEOUT)
      {
        LOG4CPLUS_INFO(root_logger, sfn
          << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
        break;
      }
      else
      {
        // Log warning for read timeouts and ignore them.
        LOG4CPLUS_INFO(root_logger, sfn
          << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
        status = DicesRcDriver::OK;
      }
    }

    status = parser->ParseResponse();
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));

      if (status == DicesRcDriver::PARSE_RESPONSE_FAILURE)
      {
        DicesRcDriver bus_comm_status = _bus_comm->PublishDeviceDriverStateError();
        if (bus_comm_status != DicesRcDriver::OK)
        {
          LOG4CPLUS_ERROR(root_logger, sfn
            << DicesRcDriverStatusMessage::DicesRcDriverToString(bus_comm_status));
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
      }
      break;
    }

    status = _bus_comm->WriteToBus();
    if (status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
      break;
    }
  }

  status = dev_comm.ShutdownComm();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));

    DicesRcDriver buf_status = parser->DeallocateMessageBuffers();
    if (buf_status != DicesRcDriver::OK)
    {
      LOG4CPLUS_ERROR(root_logger, sfn
        << DicesRcDriverStatusMessage::DicesRcDriverToString(buf_status));
    }
    return status;
  }

  status = parser->DeallocateMessageBuffers();
  if (status != DicesRcDriver::OK)
  {
    LOG4CPLUS_ERROR(root_logger, sfn
      << DicesRcDriverStatusMessage::DicesRcDriverToString(status));
  }

  return status;
}
