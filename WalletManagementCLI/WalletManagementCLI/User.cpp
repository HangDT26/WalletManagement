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

std::string User::generateOTP() {
  srand(time(0));
  int otp = 100000 + rand() % 900000;
  return std::to_string(otp);
}

//====================================

bool User::AddNewUser() {
  if (userName.empty()) {
    std::cout << "Loi: Ten nguoi dung khong duoc de trong!" << std::endl;
    return false;
  }

  if (password.empty())
  {
    password = generatePassword();
  }

  if (role.empty())
  {
    role = "User";
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

    String^ query = "SELECT UserId, UserName, Role FROM Users Where Role <> 'Admin'";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);

    SqlDataReader^ reader = cmd->ExecuteReader();
    while (reader->Read()) {
      int id = reader->GetInt32(0);
      std::string userName = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(reader["UserName"]->ToString()).ToPointer());
      std::string role = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(reader["Role"]->ToString()).ToPointer());

      userList.emplace_back(id, userName, "", role);
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
    }
    else {
      std::cout << "Sai ten nguoi dung hoac mat khau!" << std::endl;
      reader->Close();
      conn->Close();
      return false;
    }

    std::string otpCode = generateOTP();
    conn->Open();
    query = "INSERT INTO OTP (OTP, UserId, IsUsed, ExpireTime) VALUES (@OTP, @UserId, 0, DATEADD(MINUTE, 5, GETDATE()));";
    cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@OTP", gcnew String(otpCode.c_str()));
    cmd->Parameters->AddWithValue("@UserId", userId);
    cmd->ExecuteNonQuery();
    conn->Close();

    std::cout << "Ma OTP da duoc tao: " << otpCode << std::endl;
    std::cout << "Vui long nhap ma OTP de xac nhan dang nhap: ";
    std::string inputOTP;
    std::cin >> inputOTP;

    if (VerifyOTP(userId, inputOTP)) {
      loggedInUser = new User(userId, userName, password, role);
      return true;
    }
    else {
      std::cout << "OTP khong hop le hoac het han!" << std::endl;
      return false;
    }

  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}

bool User::VerifyOTP(int userId, std::string inputOTP) {
  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT OTPId FROM OTP WHERE UserId = @UserId AND OTP = @OTP AND IsUsed = 0 AND ExpireTime > GETDATE();";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@UserId", userId);
    cmd->Parameters->AddWithValue("@OTP", gcnew String(inputOTP.c_str()));

    SqlDataReader^ reader = cmd->ExecuteReader();
    bool isValid = reader->Read();
    int otpId = isValid ? reader->GetInt32(0) : -1;
    reader->Close();

    if (isValid) {
      query = "UPDATE OTP SET IsUsed = 1 WHERE OTPId = @OTPId;";
      cmd = gcnew SqlCommand(query, conn);
      cmd->Parameters->AddWithValue("@OTPId", otpId);
      cmd->ExecuteNonQuery();
    }

    conn->Close();
    return isValid;
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}

bool User::ChangePassword(int userId, std::string newPassword) {
  if (loggedInUser == nullptr) {
    std::cout << "Ban chua dang nhap!" << std::endl;
    return false;
  }

  if (newPassword.empty()) {
    std::cout << "Mat khau moi khong duoc de trong!" << std::endl;
    return false;
  }

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();

    std::string otpCode = generateOTP();
    conn->Open();

    String^ query = "INSERT INTO OTP (OTP, UserId, IsUsed, ExpireTime) VALUES (@OTP, @UserId, 0, DATEADD(MINUTE, 5, GETDATE()));";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);

    cmd->Parameters->AddWithValue("@OTP", gcnew String(otpCode.c_str()));
    cmd->Parameters->AddWithValue("@UserId", loggedInUser->userId);
    cmd->ExecuteNonQuery();
    conn->Close();

    std::cout << "Ma OTP da duoc tao: " << otpCode << std::endl;
    std::cout << "Nhap ma OTP de xac nhan thay doi mat khau: ";
    std::string inputOTP;
    std::cin >> inputOTP;

    if (!VerifyOTP(loggedInUser->userId, inputOTP)) {
      std::cout << "OTP khong hop le hoac het han! Mat khau khong duoc thay doi." << std::endl;
      return false;
    }

    conn->Open();

    query = "UPDATE Users SET Password = @NewPassword WHERE UserId = @UserId;";
    cmd = gcnew SqlCommand(query, conn);

    cmd->Parameters->AddWithValue("@UserId", userId);
    cmd->Parameters->AddWithValue("@NewPassword", gcnew String(newPassword.c_str()));

    int result = cmd->ExecuteNonQuery();
    conn->Close();

    if (result > 0) {
      loggedInUser->password = newPassword;
      return true;
    }
    else {
      std::cout << "Loi: Khong tim thay nguoi dung!" << std::endl;
      return false;
    }
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}