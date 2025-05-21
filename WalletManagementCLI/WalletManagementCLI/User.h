#pragma once
#using <System.Data.dll>

#include <string>
#include <vector>
#include <chrono>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;



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
  static std::vector<User> GetAllUsers();
  static bool Login(std::string userName, std::string password);
  static std::string generateOTP();
  bool ChangePassword(int userId, std::string newPassword);
  static bool VerifyOTP(int userId, std::string inputOTP);
};

extern User* loggedInUser;
