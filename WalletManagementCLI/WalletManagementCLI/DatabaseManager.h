#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#using <System.Data.dll>

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

ref class DatabaseManager {
public:
  static SqlConnection^ GetConnection();
};

#endif

