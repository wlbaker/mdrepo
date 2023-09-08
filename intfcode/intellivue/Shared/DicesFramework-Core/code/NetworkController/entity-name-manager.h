#ifndef ENTITYNAMEMANAGER_H
#define ENTITYNAMEMANAGER_H

#include <string>
#include <map>

static const std::map<int, std::string> kPublisherNames = {
    { 2, "ManagerPublisherName" },
    { 3, "CoordinatorPublisherName" }
};

static const std::map<int, std::string> kSubscriberNames = {
    { 2, "ManagerSubscriberName" },
    { 3, "CoordinatorSubscriberName" }
};

class EntityNameManager
{
 public:
  static std::string GetPublisherName(int domain_id);
  static std::string GetSubscriberName(int domain_id);

 private:
  // Disallow use of implicitly generated member functions:
  EntityNameManager(const EntityNameManager &other);
  EntityNameManager &operator=(const EntityNameManager &other);
  // Static object
  EntityNameManager();
};

#endif // ENTITYNAMEMANAGER_H
