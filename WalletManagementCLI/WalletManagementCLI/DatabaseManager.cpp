#include "DatabaseManager.h"
#include "pch.h"

SqlConnection^ DatabaseManager::GetConnection() {
  String^ connectionString = "Server=[Your_Server];Database=WalletManagement;User Id=[Your_Id];Password=[Your_Password];";
  return gcnew SqlConnection(connectionString);
}

