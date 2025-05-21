#pragma once
#include <string>

#include <chrono>
class User
{
public:
  std::int32_t userId;
  std::string userName;
  std::string password;
  std::string role;
  std::chrono::system_clock::time_point lastLogin;

  User(std::int32_t id, std::string name, std::string pass, std::string userRole);
  User(std::string name, std::string pass, std::string userRole);

  static std::string generatePassword();
  bool AddNewUser();
};

