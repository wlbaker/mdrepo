#include "entity-name-manager.h"

#include "base-logger.h"

std::string EntityNameManager::GetPublisherName(int domain_id)
{
  std::string sfn = "EntityNameManager::GetPublisherName ";
  if (kPublisherNames.count(domain_id) == 0)
  {
    LOG4CPLUS_ERROR(DicesLogger::get_instance()->get_logger(),
      sfn << "Domain ID " << domain_id << " not recognized; returning empty string.");
  }
  return kPublisherNames.at(domain_id);
}

std::string EntityNameManager::GetSubscriberName(int domain_id)
{
  std::string sfn = "EntityNameManager::GetSubscriberName ";
  if (kSubscriberNames.count(domain_id) == 0)
  {
    LOG4CPLUS_ERROR(DicesLogger::get_instance()->get_logger(),
      sfn << "Domain ID " << domain_id << " not recognized; returning empty string.");
  }
  return kSubscriberNames.at(domain_id);
}
