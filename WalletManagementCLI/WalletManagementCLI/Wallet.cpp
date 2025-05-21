#include "Wallet.h"
#include "DatabaseManager.h"
#include <iostream>

Wallet::Wallet(int walletId, int userId, double balance)
  : walletId(walletId), userId(userId), balance(balance) {}

//====================================

bool Wallet::TransferPoints(int senderId, int receiverId, double amount) {
  if (amount <= 0) {
    std::cout << "So diem chuyen phai lon hon 0!" << std::endl;
    return false;
  }

  if (senderId == receiverId) {
    std::cout << "Loi: Ban khong the chuyen diem cho chinh minh!" << std::endl;
    return false;
  }

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT WalletId, Balance FROM Wallets WHERE UserId = @SenderId;";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@SenderId", senderId);

    SqlDataReader^ reader = cmd->ExecuteReader();
    int senderWalletId = -1;
    double senderBalance = -1;

    if (reader->Read()) {
      senderWalletId = reader->GetInt32(0);
      senderBalance = reader->GetDouble(1);
    }
    reader->Close();

    if (senderWalletId == -1) {
      query = "INSERT INTO Transactions (SenderId, ReceiverId, Amount, CreatedDate, StatusId) VALUES (@SenderId, @ReceiverId, @Amount, GETDATE(), 2);";
      cmd = gcnew SqlCommand(query, conn);
      cmd->Parameters->AddWithValue("@SenderId", senderId);
      cmd->Parameters->AddWithValue("@ReceiverId", receiverId);
      cmd->Parameters->AddWithValue("@Amount", amount);
      cmd->ExecuteNonQuery();

      std::cout << "Loi: Khong tim thay vi cua nguoi gui!" << std::endl;
      conn->Close();
      return false;
    }

    if (senderBalance < amount) {
      std::cout << "So du khong du de chuyen!" << std::endl;
      conn->Close();
      return false;
    }

    query = "SELECT WalletId FROM Wallets WHERE UserId = @ReceiverId;";
    cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@ReceiverId", receiverId);

    reader = cmd->ExecuteReader();
    int receiverWalletId = -1;
    if (reader->Read()) {
      receiverWalletId = reader->GetInt32(0);
    }
    reader->Close();

    if (receiverWalletId == -1) {
      query = "INSERT INTO Transactions (SenderId, ReceiverId, Amount, CreatedDate, StatusId) VALUES (@SenderId, @ReceiverId, @Amount, GETDATE(), 2);";
      cmd = gcnew SqlCommand(query, conn);
      cmd->Parameters->AddWithValue("@SenderId", senderId);
      cmd->Parameters->AddWithValue("@ReceiverId", receiverId);
      cmd->Parameters->AddWithValue("@Amount", amount);
      cmd->ExecuteNonQuery();

      std::cout << "Loi: Khong tim thay vi cua nguoi nhan!" << std::endl;
      conn->Close();
      return false;
    }

    query = "UPDATE Wallets SET Balance = Balance - @Amount WHERE UserId = @SenderId;";
    cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@SenderId", senderId);
    cmd->Parameters->AddWithValue("@Amount", amount);
    cmd->ExecuteNonQuery();

    query = "UPDATE Wallets SET Balance = Balance + @Amount WHERE UserId = @ReceiverId;";
    cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@ReceiverId", receiverId);
    cmd->Parameters->AddWithValue("@Amount", amount);
    cmd->ExecuteNonQuery();

    query = "INSERT INTO Transactions (SenderId, ReceiverId, Amount, CreatedDate, StatusId) VALUES (@SenderId, @ReceiverId, @Amount, GETDATE(), 1);";
    cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@SenderId", senderId);
    cmd->Parameters->AddWithValue("@ReceiverId", receiverId);
    cmd->Parameters->AddWithValue("@Amount", amount);
    cmd->ExecuteNonQuery();

    conn->Close();
    return true;
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}


//====================================

bool Wallet::DepositPoints(int userId, double amount) {
  if (amount <= 0) {
    std::cout << "So diem nap phai lon hon 0!" << std::endl;
    return false;
  }

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT WalletId FROM Wallets WHERE UserId = @UserId;";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@UserId", userId);

    SqlDataReader^ reader = cmd->ExecuteReader();
    bool hasWallet = reader->Read();
    reader->Close();

    if (hasWallet) {
      query = "UPDATE Wallets SET Balance = Balance + @Amount WHERE UserId = @UserId;";
      cmd = gcnew SqlCommand(query, conn);
    }
    else {
      query = "INSERT INTO Wallets (UserId, Balance) VALUES (@UserId, @Amount);";
      cmd = gcnew SqlCommand(query, conn);
    }

    cmd->Parameters->AddWithValue("@UserId", userId);
    cmd->Parameters->AddWithValue("@Amount", amount);
    cmd->ExecuteNonQuery();

    conn->Close();
    return true;
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return false;
  }
}

//====================================

double Wallet::CheckBalance(int userId) {
  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT Balance FROM Wallets WHERE UserId = @UserId;";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@UserId", userId);

    SqlDataReader^ reader = cmd->ExecuteReader();
    double balance = -1;

    if (reader->Read()) {
      balance = reader->GetDouble(0);
    }
    reader->Close();
    conn->Close();

    return balance;
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
    return -1;
  }
}

//====================================

std::vector<TransactionRecord> Wallet::GetTransactionHistory(int userId) {
  std::vector<TransactionRecord> transactions;

  try {
    SqlConnection^ conn = DatabaseManager::GetConnection();
    conn->Open();

    String^ query = "SELECT t.TransationId, u.UserName AS ReceiverName, t.Amount, t.CreatedDate, s.StatusName "
      "FROM Transactions t "
      "JOIN TransationStatus s ON t.StatusId = s.StatusId "
      "JOIN Users u ON t.ReceiverId = u.UserId "
      "WHERE t.SenderId = @UserId;";
    SqlCommand^ cmd = gcnew SqlCommand(query, conn);
    cmd->Parameters->AddWithValue("@UserId", userId);

    SqlDataReader^ reader = cmd->ExecuteReader();
    while (reader->Read()) {
      TransactionRecord transaction;
      transaction.transactionId = reader->GetInt32(0);

      System::String^ netReceiverName = reader->GetString(1);
      transaction.receiverName = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(netReceiverName).ToPointer());

      transaction.amount = reader->GetDouble(2);

      System::String^ netCreatedDate = reader->GetDateTime(3).ToString();
      transaction.createdDate = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(netCreatedDate).ToPointer());

      System::String^ netStatusName = reader->GetString(4);
      transaction.statusName = std::string((char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(netStatusName).ToPointer());


      transactions.push_back(transaction);
    }

    reader->Close();
    conn->Close();
  }
  catch (Exception^ e) {
    Console::WriteLine("Loi ket noi: " + e->Message);
  }

  return transactions;
}

