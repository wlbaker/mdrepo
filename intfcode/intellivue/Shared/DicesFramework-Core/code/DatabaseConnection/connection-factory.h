#ifndef CONNECTIONFACTORY_H
#define CONNECTIONFACTORY_H

#include <string>
#include <pqxx/pqxx>

class ConnectionFactory
{ 
public:
  pqxx::connection* getConnection();
  void Disconnect();

  static ConnectionFactory* instance(); 

  static std::string get_db_user();
  static std::string get_db_pwd();
  static std::string get_host();
  static std::string get_db_name();

  static void set_db_user(const std::string& db_user);
  static void set_db_pwd(const std::string& db_pwd);
  static void set_host(const std::string& host);
  static void set_db_name(const std::string& db_name);

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

private:
  ConnectionFactory();  
};

#endif // CONNECTIONFACTORY_H
