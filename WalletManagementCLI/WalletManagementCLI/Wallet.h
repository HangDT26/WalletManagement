#ifndef WALLET_H
#define WALLET_H

#using <System.Data.dll>

#include <string>
#include <vector>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

struct TransactionRecord {
  int transactionId;
  std::string receiverName;
  double amount;
  std::string createdDate;
  std::string statusName;
};

class Wallet {
public:

  int walletId;
  int userId;
  double balance;

  Wallet(int wId, int uId, double bal);
  static bool TransferPoints(int senderId, int receiverId, double amount);
  static bool DepositPoints(int userId, double amount);
  static double CheckBalance(int userId);
  static std::vector<TransactionRecord> GetTransactionHistory(int userId);
};

#endif


