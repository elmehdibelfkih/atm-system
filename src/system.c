#include "header.h"

void createNewAcc(struct User *u, sqlite3 *db) // creat new account to an exist user
{
    struct Record r;
    int err = 0;

    system("clear");
    printf("\t\t\t===== New record =====\n");

    scanDate(&r);
    scanAccountNumber(&r, u, db);
    scanPhoneNumber(&r);
    scanCountry(&r);
    scanDeposit(&r);
    scanAccountType(&r);
    strcpy(r.name, u->name);
    r.userId = getId(u, db, &err);
    addRecord(r, db);
    success(u, db);
}

void updateAccount(struct User *u, sqlite3 *db){
    (void)u;
    (void)db;

    printf("Please enter the Account ID you wish to modify or update. Ensure the ID is correct and exists in the system.\n");
    printf("account ID: ");
}


void checkAllAccounts(struct User *u, sqlite3 *db)
{
    // char userName[100];
    // struct Record r;

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
