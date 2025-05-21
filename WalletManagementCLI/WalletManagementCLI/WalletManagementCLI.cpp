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

//====================================

bool isUserLoggedIn() {
  if (loggedInUser == nullptr) {
    std::cout << "Ban chua dang nhap!" << std::endl;
    return false;
  }
  return true;
}

//====================================

bool isAdmin() {
  if (!isUserLoggedIn()) return false;

  if (loggedInUser->role != AdminRole) {
    std::cout << "Chi admin moi co quyen thuc hien tac vu nay!" << std::endl;
    return false;
  }
  return true;
}

//====================================

void registerUser() {
  if (!isAdmin()) return;

  std::cout << "Nhap ten nguoi dung moi: ";
  std::string newUser, newPassword, newRole;
  std::cin >> newUser;
  std::cin.ignore();
  std::cout << "Nhap mat khau: (co the bo trong):";
  std::getline(std::cin, newPassword);
  std::cout << "Nhap quyen (User/Admin) (co the bo trong):";
  std::getline(std::cin, newRole);

  User newUserObj(newUser, newPassword, newRole);
  if (newUserObj.AddNewUser()) {
    std::cout << "Dang ky thanh cong!" << std::endl;
  }
  else {
    std::cout << "Dang ky that bai!" << std::endl;
  }
}

//====================================

void listAllUsers() {
  if (!isAdmin()) return;

  std::vector<User> users = User::GetAllUsers();

  if (users.empty()) {
    std::cout << "Khong co nguoi dung nao trong he thong." << std::endl;
  }
  else {
    std::cout << "Danh sach tat ca nguoi dung:" << std::endl;
    for (const User& user : users) {
      std::cout << user.userId << " - " << user.userName << " | Role: " << user.role << std::endl;
    }
  }
}

//====================================

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

//====================================

void changePassword() {
  if (loggedInUser == nullptr) {
    std::cout << "Ban chua dang nhap!" << std::endl;
    return;
  }
  int userId;
  std::string newPassword;
  if (loggedInUser->role == AdminRole)
  {
    std::cout << "Nhap Id nguoi dung: ";
    std::cin >> userId;
  }
  else
  {
    userId = loggedInUser->userId;
  }

  std::cout << "Nhap mat khau moi: ";
  std::cin.ignore();
  std::getline(std::cin, newPassword);

  if (loggedInUser->ChangePassword(userId, newPassword)) {
    std::cout << "Mat khau da duoc cap nhat thanh cong!" << std::endl;
  }
  else {
    std::cout << "Thay doi mat khau that bai!" << std::endl;
  }
}

//====================================

void transferPoints() {
  if (!isUserLoggedIn()) return;

  int receiverId;
  double amount;

  std::cout << "Nhap UserId cua nguoi nhan: ";
  std::cin >> receiverId;
  std::cout << "Nhap so diem can chuyen: ";
  std::cin >> amount;

  if (Wallet::TransferPoints(loggedInUser->userId, receiverId, amount)) {
    std::cout << "Chuyen diem thanh cong!" << std::endl;
  }
  else {
    std::cout << "Chuyen diem that bai!" << std::endl;
  }
}

//====================================

void depositPoints() {
  if (!isUserLoggedIn()) return;

  double amount;
  std::cout << "Nhap so diem can nap: ";
  std::cin >> amount;

  if (Wallet::DepositPoints(loggedInUser->userId, amount)) {
    std::cout << "Nap diem thanh cong!" << std::endl;
  }
  else {
    std::cout << "Nap diem that bai!" << std::endl;
  }
}

//====================================

void checkWalletBalance() {
  if (!isUserLoggedIn()) return;

  double balance = Wallet::CheckBalance(loggedInUser->userId);
  if (balance >= 0) {
    std::cout << "So du vi cua ban: " << balance << std::endl;
  }
  else {
    std::cout << "Khong tim thay vi cua ban!" << std::endl;
  }
}

//====================================

void showTransactionHistory() {
  if (!isUserLoggedIn()) return;

  std::vector<TransactionRecord> transactions = Wallet::GetTransactionHistory(loggedInUser->userId);

  if (transactions.empty()) {
    std::cout << "Khong co giao dich nao!" << std::endl;
  }
  else {
    std::cout << "Lich su giao dich cua ban:" << std::endl;
    for (const TransactionRecord& txn : transactions) {
      std::cout << "- ID: " << txn.transactionId
        << ", Nguoi nhan: " << txn.receiverName
        << ", So diem: " << txn.amount
        << ", Ngay: " << txn.createdDate
        << ", Trang thai: " << txn.statusName
        << std::endl;
    }
  }
}

//====================================

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
      changePassword();
      break;
    case 4:
      cout << "Chuyen diem...\n";
      transferPoints();
      break;
    case 5:
      cout << "Kiem tra so du vi...\n";
      checkWalletBalance();
      break;
    case 6:
      cout << "Lich su giao dich...\n";
      showTransactionHistory();
      break;
    case 7:
      cout << "Nap diem...\n";
      depositPoints();
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
