#include "Transaction.h"
#include "pch.h"

Transaction::Transaction(int tId, int sId, int rId, double amt, std::chrono::system_clock::time_point date, int stat)
  : transactionId(tId), senderId(sId), receiverId(rId), amount(amt), createdDate(date), statusId(stat) {}