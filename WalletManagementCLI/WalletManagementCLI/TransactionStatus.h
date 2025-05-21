#ifndef TRANSACTIONSTATUS_H
#define TRANSACTIONSTATUS_H

#include <string>

class TransactionStatus {
public:
  int statusId;
  std::string statusName;
  std::string statusDesc;

  TransactionStatus(int sId, std::string name, std::string desc);
};

#endif