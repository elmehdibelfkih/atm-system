#ifndef SQLITEQUERIES_H
#define SQLITEQUERIES_H

#define SQLITE_GET_PASSWORD "SELECT password FROM users WHERE name = ?"

#define SQLITE_GET_ID "SELECT id FROM users WHERE name = ?"

#define SQLITE_USERS_TABLE "CREATE TABLE IF NOT EXISTS users("      \
                           "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
                           "name TEXT UNIQUE NOT NULL, "            \
                           "password TEXT NOT NULL);"

#define SQLITE_RECORDS_TABLE "CREATE TABLE IF NOT EXISTS records("    \
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
                             "user_id INTEGER NOT NULL, "             \
                             "name TEXT NOT NULL, "                   \
                             "accountId INTEGER NOT NULL, "           \
                             "date DATE NOT NULL, "                   \
                             "country TEXT NOT NULL, "                \
                             "phone TEXT NOT NULL, "                  \
                             "balance REAL NOT NULL, "                \
                             "type_of_account TEXT NOT NULL);"

#define SQLITE_ADD_RECCORD "INSERT INTO records (user_id, name, accountId, date, \
country, phone, balance, type_of_account) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"

#define SQLITE_ADD_USER "INSERT INTO users (name, password) VALUES (?, ?);"

#define SQLITE_SELECT_ID "SELECT * FROM records WHERE name = ? AND accountId = ?"

#define SQLITE_UPDATE_PHONE "UPDATE records SET phone = ? WHERE accountId = ? AND name = ?"

#define SQLITE_UPDATE_COUNTRY "UPDATE records SET country = ? WHERE accountId = ? AND name = ?"

#define SQLITE_SELECT_ACCOUNTS "SELECT * FROM records WHERE name = ?"

#define SQLITE_DELETE_ACCOUNTS "DELETE FROM records WHERE accountId = ? AND name = ?"

#define SQLITE_SELECT_USER "SELECT * FROM users WHERE name = ?"

#define SQLITE_UPDATE_OWNER "UPDATE records SET (user_id, name) = (?, ?) WHERE accountId = ? AND name = ?"

#define SQLITE_SELECT_ACCOUNT "SELECT * FROM records WHERE name = ? AND accountId = ?"

#define SQLITE_UPDATE_AMOUNT "UPDATE records SET balance = ? WHERE accountId = ? AND name = ?"

#define SQLITE_SELECT_BALANCE "SELECT balance FROM records WHERE name = ? AND accountId = ?"

#define SQLITE_SELECT_TYPE_OF_ACCOUNT "SELECT type_of_account FROM records WHERE name = ? AND accountId = ?"


#endif