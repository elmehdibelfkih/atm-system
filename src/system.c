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
    success(u, db);
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
        if (accountId == -1) {
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
                success(u, db);
            }
            else if (option == 2)
            {
                ret = updatePhone(u, db, accountId);
                if (ret == -1)
                {
                    failure(u, db, 1);
                }
                success(u, db);
            }
        }
        break;
    }
}

void checkAllAccounts(struct User *u, sqlite3 *db)
{
    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u->name);
    // while (getAccountFromFile(pf, userName, &r))
    // {
    //     if (strcmp(userName, u.name) == 0)
    //     {
    //         printf("_____________________\n");
    //         printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
    //                r.accountId,
    //                r.deposit.day,
    //                r.deposit.month,
    //                r.deposit.year,
    //                r.country,
    //                r.phone,
    //                r.amount,
    //                r.accountType);
    //     }
    // }
    success(u, db);
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
    (void)u;
    (void)db;
}

void transferAccount(struct User *u, sqlite3 *db)
{
    (void)u;
    (void)db;
}
