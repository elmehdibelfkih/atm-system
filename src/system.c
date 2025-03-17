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
        printf("%s", my_error.error_message);
        failure(u, db, 1);
    }
    scanPhoneNumber(&r);
    scanCountry(&r);
    scanDeposit(&r);
    scanAccountType(&r);
    strcpy(r.name, u->name);
    r.userId = getId(u, db, &err);
    addRecord(r, db);
    success(u, db, 1);
}

void updateAccount(struct User *u, sqlite3 *db)
{
    int accountId;
    int option;
    int tmp;
    int ret;

    system("clear");
    while (1)
    {
        printf("\n\n\t\tPlease enter the Account ID you wish to modify or update.\n"
               "\t\tEnsure the ID is correct and exists in the system.\n");
        printf("\t\tTo view all available accounts, return to the main menu by entering -1.\n");
        scanInt(&accountId, "Account ID: ", -1, INT_MAX);
        if (accountId == -1)
        {
            mainMenu(u, db);
        }
        tmp = isAccountExist(u, db, accountId);
        if (tmp == -1)
        {
            failure(u, db, 1);
        }
        else if (!tmp)
        {
            system("clear");
            printf("\t\tAccount ID does not exist. Please enter a valid account.\n");
            continue;
        }
        else
        {
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
        break;
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
    (void)u;
    (void)db;
}

void makeTransaction(struct User *u, sqlite3 *db)
{
    (void)u;
    (void)db;
}

void removeExistingAccount(struct User *u, sqlite3 *db)
{
    int accountId;
    int tmp;

    system("clear");
    while (1)
    {
        printf("\n\n\t\tPlease enter the Account ID you wish to delete.\n"
               "\t\tEnsure the ID is correct and exists in the system.\n");
        printf("\t\tTo view all available accounts, return to the main menu by entering -1.\n");
        scanInt(&accountId, "Account ID: ", -1, INT_MAX);
        if (accountId == -1)
        {
            mainMenu(u, db);
        }
        tmp = isAccountExist(u, db, accountId);
        if (tmp == -1)
        {
            failure(u, db, 1);
        }
        else if (!tmp)
        {
            system("clear");
            printf("\t\tAccount ID does not exist. Please enter a valid account.\n");
            continue;
        }
        else
        {
            deleteAccount(u, db, accountId);
            success(u, db, 1);
        }
        break;
    }
}

void transferAccount(struct User *u, sqlite3 *db)
{
    (void)u;
    (void)db;
}
