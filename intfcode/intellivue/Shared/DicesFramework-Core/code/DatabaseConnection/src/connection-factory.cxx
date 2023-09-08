#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include "connection-factory.h"

static log4cplus::Logger root_log = log4cplus::Logger::getRoot();

struct ConnectionFactory::impl
{
  // Hardcoding these values for now
  static std::string _db_user;
  static std::string _db_pwd;
  static std::string _host;
  static std::string _db_name;

  // singleton
  static ConnectionFactory* _sConnectionFactory;

  // the connection - for now just a single connection.
  // connection pooling can be used to scale solution if needed.
  static pqxx::connection* _sConnection;

  impl() = default;

  ~impl() = default;

  pqxx::connection* getConnection()
  {
    const char *sfn = " ConnectionFactory::getConnection()";

    if (_sConnection == nullptr)
    {
      std::string connectionStr;

      if (_db_name.empty() == false)
      {
        connectionStr = "dbname=" + _db_name;
      }
      if (_db_user.empty() == false)
      {
        if (connectionStr.empty() == false)
        {
          connectionStr += " "; // Add space between options
        }
        connectionStr += "user="  + _db_user;
      }
      if (_db_pwd.empty() == false)
      {
        if (connectionStr.empty() == false)
        {
          connectionStr += " "; // Add space between options
        }
        connectionStr += "password="  + _db_pwd;
      }
      if (_host.empty() == false)
      {
        if (connectionStr.empty() == false)
        {
          connectionStr += " "; // Add space between options
        }
        connectionStr += "host="  + _host;
      }

      try
      {
        _sConnection = new pqxx::connection(connectionStr);
      }
      catch (const pqxx::pqxx_exception &e)
      {
        LOG4CPLUS_ERROR(root_log, sfn << " error creating connection: " << e.base().what());
      }
      catch (const std::exception &e)
      {
        LOG4CPLUS_ERROR(root_log, sfn <<  " exception creating connection: " << e.what());
      }
    }

    return _sConnection;
  }

  void Disconnect()
  {
    const char *sfn = " ConnectionFactory::Disconnect()";

    if (_sConnection == nullptr) return;

    try
    {
      _sConnection->disconnect();
    }
    catch (const std::exception& ex)
    {
      LOG4CPLUS_ERROR(root_log, sfn << " error disconnecting from database: "
        << ex.what());
    }

    delete _sConnection;
    _sConnection = nullptr;
  }

  ConnectionFactory* instance()
  {
    if (_sConnectionFactory == nullptr)
    {
      _sConnectionFactory = new ConnectionFactory();
    }

    return _sConnectionFactory;
  }
};

std::string ConnectionFactory::impl::_db_user = "postgres";
std::string ConnectionFactory::impl::_db_pwd = "";
std::string ConnectionFactory::impl::_host = "localhost";
std::string ConnectionFactory::impl::_db_name = "dicesdb";

// singleton
ConnectionFactory* ConnectionFactory::impl::_sConnectionFactory = nullptr;

// the connection - for now just a single connection.
// connection pooling can be used to scale solution if needed.
pqxx::connection* ConnectionFactory::impl::_sConnection = nullptr;

std::string ConnectionFactory::get_db_user()
{
  return ConnectionFactory::impl::_db_user;
}

std::string ConnectionFactory::get_db_pwd()
{
  return ConnectionFactory::impl::_db_pwd;
}

std::string ConnectionFactory::get_host()
{
  return ConnectionFactory::impl::_host;
}

std::string ConnectionFactory::get_db_name()
{
  return ConnectionFactory::impl::_db_name;
}

void ConnectionFactory::set_db_user(const std::string& db_user)
{
  ConnectionFactory::impl::_db_user = db_user;
}

void ConnectionFactory::set_db_pwd(const std::string& db_pwd)
{
  ConnectionFactory::impl::_db_pwd = db_pwd;
}

void ConnectionFactory::set_host(const std::string& host)
{
  ConnectionFactory::impl::_host = host;
}

void ConnectionFactory::set_db_name(const std::string& db_name)
{
  ConnectionFactory::impl::_db_name = db_name;
}

pqxx::connection* ConnectionFactory::getConnection()
{
  return _pimpl->getConnection();
}

void ConnectionFactory::Disconnect()
{
  _pimpl->Disconnect();
}

ConnectionFactory* ConnectionFactory::instance()
{
  if (ConnectionFactory::impl::_sConnectionFactory == nullptr)
  {
    ConnectionFactory::impl::_sConnectionFactory = new (std::nothrow) ConnectionFactory();
  }

  return ConnectionFactory::impl::_sConnectionFactory;
} 

ConnectionFactory::ConnectionFactory()
  :_pimpl(nullptr)
{
  static const char* sfn = "ConnectionFactory::ConnectionFactory() ";
  _pimpl = std::unique_ptr<impl>(new (std::nothrow) impl());
  if (!_pimpl)
  {
    LOG4CPLUS_ERROR(log4cplus::Logger::getRoot(), sfn << "Failed to create impl");
    return;
  }
}
