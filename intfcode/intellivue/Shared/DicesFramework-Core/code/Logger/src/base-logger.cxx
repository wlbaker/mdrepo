#include "../base-logger.h"

#include <iostream>


struct DicesLogger::impl
{
  static DicesLogger *_logger;

  impl() = default;
  ~impl() = default;

  static DicesLogger *get_instance()
  {
    if (_logger == nullptr)
    {
      _logger = new (std::nothrow) DicesLogger();
    }

    return _logger;
  }

  log4cplus::Logger get_logger()
  {
    return log4cplus::Logger::getRoot();
  }

  log4cplus::Logger get_logger(const std::string &name)
  {
    return log4cplus::Logger::getInstance(name);
  }
};

DicesLogger *DicesLogger::impl::_logger = nullptr;

DicesLogger::DicesLogger()
  : _pimpl(nullptr)
{
  static const char* sfn = "DicesLogger::DicesLogger() ";

  log4cplus::PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.properties"));

  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), "Failed to create impl");
    return;
  }
}

DicesLogger *DicesLogger::get_instance()
{
  return DicesLogger::impl::get_instance();
}

log4cplus::Logger DicesLogger::get_logger()
{
  return _pimpl->get_logger();
}

log4cplus::Logger DicesLogger::get_logger(const std::string &name)
{
  return _pimpl->get_logger(name);
}

