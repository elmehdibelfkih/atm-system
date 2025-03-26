#include "header.h"

void createNewAcc(struct User *u, sqlite3 *db)
{
    struct Record r;
    int err = 0;

    system("clear");
    printf("\t\t\t===== New record =====\n");

    scanDate(&r);
    if (scanAccountNumber(&r, u, db) == -1)
    {
        failure(u, db, 1);
    }
    scanPhoneNumber(&r);
    scanCountry(&r);
    scanDeposit(&r);
    scanAccountType(&r);
    strcpy(r.name, u->name);
    r.userId = getId(u, db, &err);
    if (addRecord(r, db) == -1)
    {
        failure(u, db, 1);
    }
    success(u, db, 1);
}

void updateAccount(struct User *u, sqlite3 *db)
{
    int accountId;
    int option;
    int ret;

    getAccountId(u, db, &accountId);
    system("clear");
    printf("\t\tEnter 1 to update the country or 2 to update the phone number.\n");
    scanInt(&option, "option: ", 1, 2);
    if (option == 1)
    {
        ret = updateCountry(u, db, accountId);
        if (ret == -1)
        {
            failure(u, db, 1);
        }
        success(u, db, 1);
    }
    else if (option == 2)
    {
        ret = updatePhone(u, db, accountId);
        if (ret == -1)
        {
            failure(u, db, 1);
        }
        success(u, db, 1);
    }
}

void checkAllAccounts(struct User *u, sqlite3 *db)
{
    sqlite3_stmt *stmt;
    int rc;
    struct Record r;

    rc = sqlite3_prepare_v2(db, SQLITE_SELECT_ACCOUNTS, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        failure(u, db, 1);
    }

    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_STATIC);

    system("clear");
    printf("\n\n\t\t====== All accounts from user, %s =====\n\n", u->name);

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        printf("=========================================\n");

        r.accountId = sqlite3_column_int(stmt, 3);

        const char *date = (const char *)sqlite3_column_text(stmt, 4);
        const char *country = (const char *)sqlite3_column_text(stmt, 5);
        const char *phone = (const char *)sqlite3_column_text(stmt, 6);
        const char *accountType = (const char *)sqlite3_column_text(stmt, 8);
        strcpy(r.date, date ? date : "N/A");
        strcpy(r.country, country ? country : "N/A");
        strcpy(r.phone, phone ? phone : "N/A");
        r.amount = sqlite3_column_double(stmt, 7);
        strcpy(r.accountType, accountType ? accountType : "N/A");

        printAccountInfo(r);
        printf("=========================================\n");
    }

    if (rc != SQLITE_DONE)
    {
        my_error.error_message = DATABASE_ERROR;
        failure(u, db, 1);
    }

    sqlite3_finalize(stmt);
    success(u, db, 0);
}

void checkExistingAccounts(struct User *u, sqlite3 *db)
{
    int accountId;

    getAccountId(u, db, &accountId);
    sqlite3_stmt *stmt;
    int rc;
    struct Record r;

    rc = sqlite3_prepare_v2(db, SQLITE_SELECT_ACCOUNT, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        my_error.error_message = DATABASE_ERROR;
        failure(u, db, 1);
    }

    sqlite3_bind_text(stmt, 1, u->name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, accountId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW)
    {
        my_error.error_message = DATABASE_ERROR;
        failure(u, db, 1);
    }
    system("clear");
    printf("\n\n\t\t====== account %d from user %s =====\n\n", accountId, u->name);
    printf("=========================================\n");

    r.accountId = sqlite3_column_int(stmt, 3);

    const char *date = (const char *)sqlite3_column_text(stmt, 4);
    const char *country = (const char *)sqlite3_column_text(stmt, 5);
    const char *phone = (const char *)sqlite3_column_text(stmt, 6);
    const char *accountType = (const char *)sqlite3_column_text(stmt, 8);
    strcpy(r.date, date ? date : "N/A");
    strcpy(r.country, country ? country : "N/A");
    strcpy(r.phone, phone ? phone : "N/A");
    r.amount = sqlite3_column_double(stmt, 7);
    strcpy(r.accountType, accountType ? accountType : "N/A");

    printAccountInfo(r);
    printInterest(r.accountType, r.amount, r.date);
    printf("=========================================\n");

    sqlite3_finalize(stmt);
    success(u, db, 0);
}

void makeTransaction(struct User *u, sqlite3 *db)
{
    (void)u;
    (void)db;
}

void removeExistingAccount(struct User *u, sqlite3 *db)
{
    int accountId;

    getAccountId(u, db, &accountId);
    if (deleteAccount(u, db, accountId) == -1)
    {
        failure(u, db, 1);
    }
    success(u, db, 1);
}

void transferAccount(struct User *u, sqlite3 *db)
{
    char a[NAME_LENGHT];
    int accountId;

    system("clear");
    while (1)
    {
        printf("\n\t\tPlease enter the login and account ID of the user to whom you want to transfer the account.");
        scanLen("\n\t\tLogin: ", a, NAME_LENGHT, 0);

        if (!isUserExist(a, db))
        {
            system("clear");
            printf(INVALIDE_USER);
            continue;
        }
        system("clear");
        getAccountId(u, db, &accountId);
        if (transfer(u, accountId, a, db) == -1)
        {
            failure(u, db, 1);
        }
        success(u, db, 1);
        break;
    }
}
