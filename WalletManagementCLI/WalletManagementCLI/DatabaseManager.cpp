#include "DatabaseManager.h"
#include "pch.h"

SqlConnection^ DatabaseManager::GetConnection() {
  String^ connectionString = "Server=ADMINISTRATOR;Database=WalletManagement;User Id=sa;Password=1234$;";
  return gcnew SqlConnection(connectionString);
}

