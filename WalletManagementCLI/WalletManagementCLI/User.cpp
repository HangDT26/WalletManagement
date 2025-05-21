#include "pch.h"
#include "User.h"
#include "DatabaseManager.h"
#include <iostream>

User* loggedInUser = nullptr;

User::User(std::int32_t id, std::string name, std::string pass, std::string userRole)
  :userId(id), userName(name), password(pass.empty() ? generatePassword() : pass), role(userRole.empty() ? "User" : userRole), lastLogin(std::chrono::system_clock::now()) {}

//====================================
User::User(std::string name, std::string pass, std::string userRole)
  : userName(name), password(pass.empty() ? generatePassword() : pass), role(userRole.empty() ? "User" : userRole), lastLogin(std::chrono::system_clock::now()) {}

//====================================

std::string User::generatePassword() {
  std::string password = "";
  for (int i = 0; i < 8; i++) {
    password += 'A' + rand() % 26;
  }
  return password;
}

//====================================

bool User::AddNewUser() {
  if (userName.empty()) {
    std::cout << "Loi: Ten nguoi dung khong duoc de trong!" << std::endl;
    return false;
  }

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "INSERT INTO Users (UserName, Password, Role, LastLogin) VALUES (@UserName, @Password, @Role, GETDATE());";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);

    cmd->Parameters->AddWithValue("@UserName", gcnew String(userName.c_str()));
    cmd->Parameters->AddWithValue("@Password", gcnew String(password.c_str()));
    cmd->Parameters->AddWithValue("@Role", gcnew String(role.c_str()));

    int result = cmd->ExecuteNonQuery();
    conn->Close();

    if (result > 0) {
      std::cout << "Nguoi dung moi da duoc luu vao SQL Server!" << std::endl;
      return true;
    }
    else {
      std::cout << "Them nguoi dung that bai." << std::endl;
      return false;
    }
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}

//====================================

std::vector<User> User::GetAllUsers() {
  std::vector<User> userList;

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT UserName, Role FROM Users Where Role <> 'Admin'";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);

    SqlDataReader^ reader = cmd->ExecuteReader();
    while (reader->Read()) {
      std::string userName = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(reader["UserName"]->ToString()).ToPointer());
      std::string role = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(reader["Role"]->ToString()).ToPointer());

      userList.emplace_back(userName, "", role);
    }

    reader->Close();
    conn->Close();
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
  }

  return userList;
}

bool User::Login(std::string userName, std::string password) {
  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT UserId, Role FROM Users WHERE UserName = @UserName AND Password = @Password;";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);

    cmd->Parameters->AddWithValue("@UserName", gcnew String(userName.c_str()));
    cmd->Parameters->AddWithValue("@Password", gcnew String(password.c_str()));

    SqlDataReader^ reader = cmd->ExecuteReader();
    int userId = -1;
    std::string role = "";

    if (reader->Read()) {
      userId = reader->GetInt32(0);
      System::String^ netRole = reader->GetString(1);
      role = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(netRole).ToPointer());
      reader->Close();
      conn->Close();
      loggedInUser = new User(userId, userName, password, role);
      return true;
    }
    else {
      std::cout << "Sai ten nguoi dung hoac mat khau!" << std::endl;
      reader->Close();
      conn->Close();
      return false;
    }

   

  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}