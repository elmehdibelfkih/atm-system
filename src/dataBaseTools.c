#include "header.h"

void intiDataBase(sqlite3 **db)
{
    char *errMsg = NULL;
    int rc = sqlite3_open("./data/atm.db", db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
        exit(1);
    }

    // create the users table if not exist
    rc = sqlite3_exec(*db, SQLLITE_USERS_TABLE, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }

    // create the records table if not exist
    rc = sqlite3_exec(*db, SQLLITE_RECORDS_TABLE, 0, 0, &errMsg);
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

// return 1 if an error happen
// return 0 if every thing is ok
int getPassword(struct User *u, sqlite3 *db, char password[50])
{
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLLITE_GET_PASSWORD, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return 1;
    }
    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_STATIC);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        strcpy(password, (char *)sqlite3_column_text(stmt, 0));
    }
    else
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_finalize(stmt);
    return 0;
}

int getId(struct User *u, sqlite3 *db, int *err) // FIXME: set the custom errno
{
    int id = -1;
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLLITE_GET_ID, -1, &stmt, NULL) != SQLITE_OK)
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
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLLITE_ADD_RECCORD, -1, &stmt, NULL) != SQLITE_OK)
    {
        fprintf(stderr, "SQL Error: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Bind parameters with correct indices
    sqlite3_bind_int(stmt, 1, r.userId);
    sqlite3_bind_text(stmt, 2, r.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, r.accountId);
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
