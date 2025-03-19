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

    rc = sqlite3_exec(*db, SQLITE_USERS_TABLE, 0, 0, &errMsg);
    if (rc != SQLITE_OK)
    {
        printf("SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        sqlite3_close(*db);
        exit(1);
    }

    rc = sqlite3_exec(*db, SQLITE_RECORDS_TABLE, 0, 0, &errMsg);
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
    sqlite3_stmt *stmt;

    int rc = sqlite3_prepare_v2(db, SQLITE_ADD_USER, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, passWord, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE)
    {
        if (rc == SQLITE_CONSTRAINT)
        {
            my_error.error_message = REGISTRATION_ERROR;
        }
        else
        {
            my_error.error_message = DATABASE_ERROR;
        }
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int addRecord(struct Record r, sqlite3 *db)
{
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_ADD_RECCORD, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_bind_int(stmt, 1, r.userId);
    sqlite3_bind_text(stmt, 2, r.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, r.accountId);
    sqlite3_bind_text(stmt, 4, r.date, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, r.country, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, r.phone, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 7, r.amount);
    sqlite3_bind_text(stmt, 8, r.accountType, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

// return -1 if an error happen
// return 0 if every thing is ok
// return 1 if the user dose not exist in th data base
int getPassword(struct User *u, sqlite3 *db, char password[PASSWORD_LENGHT])
{
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, SQLITE_GET_PASSWORD, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }
    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_TRANSIENT);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        strncpy(password, (const char *)sqlite3_column_text(stmt, 0), PASSWORD_LENGHT - 1);
        password[PASSWORD_LENGHT - 1] = '\0';
        sqlite3_finalize(stmt);
        return 0;
    }
    else if (rc == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return 1;
    }
    else
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }
}

int getId(struct User *u, sqlite3 *db, int *err)
{
    int id = -1;
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_GET_ID, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        failure(u, db, 1);
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
    sqlite3_finalize(stmt);
    return id;
}

// return 0 if the account does not exist
// return -1 if an error happen
// return 1 if the account exist
int isAccountExist(struct User *u, sqlite3 *db, int accountId)
{
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, SQLITE_SELECT_ID, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }
    sqlite3_bind_text(stmt, 1, u->name, -1, NULL);
    sqlite3_bind_int(stmt, 2, accountId);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return 1;
    }
    else if (rc == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_finalize(stmt);
    my_error.error_message = DATABASE_ERROR;
    return -1;
}

// return -1 if an error happen
// return 1 if every thing is ok
int updateCountry(struct User *u, sqlite3 *db, int accountId)
{
    struct Record r;

    scanCountry(&r);
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_UPDATE_COUNTRY, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }

    sqlite3_bind_text(stmt, 1, r.country, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, accountId);
    sqlite3_bind_text(stmt, 3, u->name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int updatePhone(struct User *u, sqlite3 *db, int accountId)
{
    struct Record r;

    scanPhoneNumber(&r);
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_UPDATE_PHONE, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }

    sqlite3_bind_text(stmt, 1, r.phone, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, accountId);
    sqlite3_bind_text(stmt, 3, u->name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

int deleteAccount(struct User *u, sqlite3 *db, int accountId)
{
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_DELETE_ACCOUNTS, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }

    sqlite3_bind_int(stmt, 1, accountId);
    sqlite3_bind_text(stmt, 2, u->name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 1;
}

// return 0 if the account does not exist
// return -1 if an error happen
// return 1 if the account exist
int isUserExist(char a[NAME_LENGHT], sqlite3 *db)
{
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_prepare_v2(db, SQLITE_SELECT_USER, -1, &stmt, NULL);

    if (rc != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }
    sqlite3_bind_text(stmt, 1, a, -1, NULL);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW)
    {
        sqlite3_finalize(stmt);
        return 1;
    }
    else if (rc == SQLITE_DONE)
    {
        sqlite3_finalize(stmt);
        return 0;
    }
    sqlite3_finalize(stmt);
    my_error.error_message = DATABASE_ERROR;
    return -1;
}

int transfer(struct User *u, int accountId, char newOwner[NAME_LENGHT], sqlite3 *db)
{
    struct User newOwnerstruct;
    int err;

    strcpy(newOwnerstruct.name, newOwner);
    newOwnerstruct.id = getId(&newOwnerstruct, db, &err);
    if (isAccountExist(&newOwnerstruct, db, accountId))
    {
        my_error.error_message = INVALIDE_TRANSFER;
        failure(u, db, 1);
    }

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, SQLITE_UPDATE_OWNER, -1, &stmt, NULL) != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        return -1;
    }
    sqlite3_bind_int(stmt, 1, newOwnerstruct.id);
    sqlite3_bind_text(stmt, 2, newOwnerstruct.name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, accountId);
    sqlite3_bind_text(stmt, 4, u->name, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        sqlite3_finalize(stmt);
        return -1;
    }
    sqlite3_finalize(stmt);
    return 1;
}