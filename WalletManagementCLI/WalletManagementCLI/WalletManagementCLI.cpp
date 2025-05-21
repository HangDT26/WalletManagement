#include "pch.h"
#include <iostream>
#include <string>
#include "User.h"
#include "Wallet.h"
#include "Transaction.h"
#include "DatabaseManager.h"

#define CLEAR_SCREEN "cls" 
#define AdminRole "Admin"
using namespace System;
using namespace std;
//====================================

void displayMenu() {
  cout << "==========================\n";
  cout << "  Quan ly vi dien tu\n";
  cout << "==========================\n";
  cout << "1. Dang ky\n";
  cout << "2. Dang nhap\n";
  cout << "3. Thay doi mat khau\n";
  cout << "4. Chuyen diem\n";
  cout << "5. Kiem tra so du vi\n";
  cout << "6. Lich su giao dich\n";
  cout << "7. Nap diem\n";
  cout << "8. Xem danh sach nguoi dung\n";
  cout << "9. Thoat\n";
  cout << "==========================\n";
}


bool isUserLoggedIn() {
  if (loggedInUser == nullptr) {
    std::cout << "Ban chua dang nhap!" << std::endl;
    return false;
  }
  return true;
}



bool isAdmin() {
  if (!isUserLoggedIn()) return false;

  if (loggedInUser->role != AdminRole) {
    std::cout << "Chi admin moi co quyen thuc hien tac vu nay!" << std::endl;
    return false;
  }
  return true;
}



void registerUser() {
  if (!isAdmin()) return;

  std::cout << "Nhap ten nguoi dung moi: ";
  std::string newUser, newPassword, newRole;
  std::cin >> newUser;
  std::cout << "Nhap mat khau: ";
  std::cin >> newPassword;
  std::cout << "Nhap quyen (User/Admin): ";
  std::cin >> newRole;

  User newUserObj(newUser, newPassword, newRole);
  if (newUserObj.AddNewUser()) {
    std::cout << "Dang ky thanh cong!" << std::endl;
  }
  else {
    std::cout << "Dang ky that bai!" << std::endl;
  }
}

void listAllUsers() {
  if (!isAdmin()) return;

  std::vector<User> users = User::GetAllUsers();

  if (users.empty()) {
    std::cout << "Khong co nguoi dung nao trong he thong." << std::endl;
  }
  else {
    std::cout << "Danh sach tat ca nguoi dung:" << std::endl;
    for (const User& user : users) {
      std::cout << "- " << user.userName << " | Role: " << user.role << std::endl;
    }
  }
}

void loginUser() {
  cout << "Nhap ten nguoi dung: ";
  string userName, password;
  cin >> userName;
  cout << "Nhap mat khau: ";
  cin >> password;

  if (User::Login(userName, password)) {
    cout << "Dang nhap thanh cong!" << endl;
  }
  else {
    cout << "Dang nhap that bai!" << endl;
  }
}

int main() {
  int choice;

  while (true) {
    displayMenu();
    cout << "Chon lenh (1-9): ";
    cin >> choice;

    system(CLEAR_SCREEN);

    switch (choice) {
    case 1:
      cout << "Dang ky...\n";
      registerUser();
      break;
    case 2:
      cout << "Dang nhap...\n";
      loginUser();
      break;
    case 3:
      cout << "Thay doi mat khau...\n";
      break;
    case 4:
      cout << "Chuyen diem...\n";
      break;
    case 5:
      cout << "Kiem tra so du vi...\n";
      break;
    case 6:
      cout << "Lich su giao dich...\n";
      break;
    case 7:
      cout << "Nap diem...\n";
      break;
    case 8:
      cout << "Xem danh sach nguoi dung...\n";
      listAllUsers();
      break;
    case 9:
      cout << "Thoat.\n";
      return 0;
    default:
      cout << "Loi!!!.\n";
    }
    cout << "\n Hay chon lenh tiep theo...\n" << endl;
  }
}
