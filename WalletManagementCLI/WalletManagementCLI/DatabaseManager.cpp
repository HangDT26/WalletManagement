#include "DatabaseManager.h"
#include "pch.h"

SqlConnection^ DatabaseManager::GetConnection() {
  String^ connectionString = "Server=[Your_server];Database=WalletManagement;User Id=[your_id];Password=[your_password];";
  return gcnew SqlConnection(connectionString);
}

