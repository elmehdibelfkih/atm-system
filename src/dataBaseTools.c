#include "header.h"

void intiDataBase(sqlite3 **db)
{
    char *errMsg = NULL;
    char *users = "CREATE TABLE IF NOT EXISTS users("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "name TEXT UNIQUE NOT NULL, "
                  "password TEXT NOT NULL);";
    char *records = "CREATE TABLE IF NOT EXISTS records("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "user_id INTEGER NOT NULL, "
                    "name TEXT NOT NULL, "
                    "account_id INTEGER UNIQUE NOT NULL, "
                    "date_of_creation DATE NOT NULL, "
                    "country TEXT NOT NULL, "
                    "phone NUMERIC NOT NULL, "
                    "balance REAL NOT NULL, " // MUST BE FLOAT
                    "type_of_account TEXT NOT NULL);";
    int rc = sqlite3_open("./data/atm.db", db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }

    // create the users table if not exist
    rc = sqlite3_exec(*db, users, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }

    // create the records table if not exist
    rc = sqlite3_exec(*db, records, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }
    return;
}

int addUser(char *name, char *passWord, sqlite3 *db)
{
    char *errMsg = NULL;
    char query[256];

    snprintf(query, sizeof(query), "INSERT INTO users (name, password) VALUES ('%s', '%s');", name, passWord);
    int rc = sqlite3_exec(db, query, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        if (strcmp("UNIQUE constraint failed: users.name", errMsg) == 0)
        {
            printf("\n\nThe username you entered is already in use. Please choose a different one.\n");
        }
        else
        {
            printf("%s\n", errMsg);
        }
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

const char *getPassword(struct User *u, sqlite3 *db, int *err)
{
    const unsigned char *password;
    char *sql = "SELECT password FROM users WHERE name = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        exit(1); // FIXME: avoid using exit
    }
    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        password = sqlite3_column_text(stmt, 0);
    }
    else
    {
        *err = 1;
        password = (const unsigned char *)"no user found";
    }
    // sqlite3_finalize(stmt); // FIXME
    return (const char *)password;
}

int getId(struct User *u, sqlite3 *db, int *err)
{
    int id = -1;
    char *sql = "SELECT id FROM users WHERE name = ?";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        exit(1); // FIXME: avoid using exit
    }
    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        id = sqlite3_column_int(stmt, 0);
    }
    else
    {
        *err = 1;
        id = -1;
    }
    // sqlite3_finalize(stmt); // FIXME
    return id;
}

void addRecord(struct Record r, sqlite3 *db)
{
    printf("hani\n");
    char *sql = "INSERT INTO records (user_id, name, account_id, date_of_creation, country, phone, balance, type_of_account) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind parameters with correct indices
    sqlite3_bind_int(stmt, 1, r.userId);
    sqlite3_bind_text(stmt, 2, r.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, r.accountNbr);
    sqlite3_bind_text(stmt, 4, r.date, -1, SQLITE_STATIC); // FIXME
    sqlite3_bind_text(stmt, 5, r.country, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, r.phone); // Assuming phone is a string
    sqlite3_bind_double(stmt, 7, r.amount);
    sqlite3_bind_text(stmt, 8, r.accountType, -1, SQLITE_STATIC);

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        fprintf(stderr, "SQL Execution Error: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    // Cleanup
    sqlite3_finalize(stmt);
}
