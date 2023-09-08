#ifndef CONNECTION_UTILITIES_H_
#define CONNECTION_UTILITIES_H_

#include <string>

std::string exec(const char* cmd);
bool IsPostgresServiceUp();
void WaitForPostgresServiceUp();

#endif
