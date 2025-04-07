#include <string>
#include <chrono>
#include <iostream>
using namespace std;

class User {
private:
  int Id;
  string username;
  string password;
  string role;
  chrono::system_clock::time_point lastLogin;

public:
  // Constructor
  User(int id, string user, string pass, string userRole, chrono::system_clock::time_point loginTime);

  // Getter and Setter for Id
  int getId() const;
  void setId(int id);

  // Getter and Setter for username
  string getUsername() const;
  void setUsername(const string& user);

  // Getter and Setter for password
  string getPassword() const;
  void setPassword(const string& pass);

  // Getter and Setter for role
  string getRole() const;
  void setRole(const string& userRole);

  // Getter and Setter for last login time
  chrono::system_clock::time_point getLastLogin() const;
  void setLastLogin(chrono::system_clock::time_point loginTime);

  // Method to print last login time in a readable format
  void printLastLogin() const;
};


