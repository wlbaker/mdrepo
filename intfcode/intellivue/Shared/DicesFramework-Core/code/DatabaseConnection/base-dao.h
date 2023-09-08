#ifndef BASEDAO_H
#define BASEDAO_H

#include <string>
//#include "ndds/ndds_namespace_cpp.h"
#include <pqxx/pqxx>

class BaseDAO 
{
public:
  BaseDAO();
  ~BaseDAO();
  
  pqxx::connection* getConnection();
  
  std::string getTableName(std::string);

protected:
  struct impl;
  std::unique_ptr<impl> _pimpl;

};

#endif	/* BASEDAO_H */
