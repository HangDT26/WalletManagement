#include "pch.h"
#include <iostream>
#include "User.h"
#include "Wallet.h"
#include "Transaction.h"
#include "DatabaseManager.h"

#define CLEAR_SCREEN "cls" 
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
      break;
    case 2:
      cout << "Dang nhap...\n";
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
