#include "User.h"

// Constructor
User::User(int id, string user, string pass, string userRole, chrono::system_clock::time_point loginTime)
  : Id(id), username(user), password(pass), role(userRole), lastLogin(loginTime) {}

// Getter and Setter for Id
int User::getId() const {
  return Id;
}

void User::setId(int id) {
  Id = id;
}

// Getter and Setter for username
string User::getUsername() const {
  return username;
}

void User::setUsername(const string& user) {
  username = user;
}

// Getter and Setter for password
string User::getPassword() const {
  return password;
}

void User::setPassword(const string& pass) {
  password = pass;
}

// Getter and Setter for role
string User::getRole() const {
  return role;
}

void User::setRole(const string& userRole) {
  role = userRole;
}

// Getter and Setter for last login time
chrono::system_clock::time_point User::getLastLogin() const {
  return lastLogin;
}

void User::setLastLogin(chrono::system_clock::time_point loginTime) {
  lastLogin = loginTime;
}

 //Method to print last login time in a readable format
void User::printLastLogin() const {
  time_t lastLoginTime = chrono::system_clock::to_time_t(lastLogin);
  char buffer[26];  // Buffer to hold the formatted time
  ctime_s(buffer, sizeof(buffer), &lastLoginTime);  // Using ctime_s (safe version)
  cout << "Last login: " << buffer;
}
