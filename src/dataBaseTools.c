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
                    "date_of_creation TEXT NOT NULL, "
                    "country TEXT NOT NULL, "
                    "phone TEXT NOT NULL, "
                    "balance INTEGER NOT NULL, " // MUST BE FLOAT
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

    // testing
    addUser("mehdi", "belfkih", *db);

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