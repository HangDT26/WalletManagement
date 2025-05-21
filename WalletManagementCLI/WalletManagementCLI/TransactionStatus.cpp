#include "TransactionStatus.h"
#include "pch.h"

TransactionStatus::TransactionStatus(int sId, std::string name, std::string desc)
  : statusId(sId), statusName(name), statusDesc(desc) {}
