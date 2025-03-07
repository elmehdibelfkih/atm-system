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
                             "phone NUMERIC NOT NULL, "               \
                             "balance REAL NOT NULL, "                \
                             "type_of_account TEXT NOT NULL);"
#define SQLITE_ADD_RECCORD "INSERT INTO records (user_id, name, accountId, date, \
country, phone, balance, type_of_account) VALUES (?, ?, ?, ?, ?, ?, ?, ?)"

#define SQLITE_ADD_USER "INSERT INTO users (name, password) VALUES (?, ?);"

#endif