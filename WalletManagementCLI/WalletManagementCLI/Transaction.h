#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>

class Transaction {
public:
  int transactionId;
  int senderId;
  int receiverId;
  double amount;
  std::chrono::system_clock::time_point createdDate;
  int statusId;

  Transaction(int tId, int sId, int rId, double amt, std::chrono::system_clock::time_point date, int stat);
};

#endif

