#include "header.h"

void stayOrReturn(int notGood, void f(struct User u), struct User *u, sqlite3 *db)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(*u); // FIXME
        else if (option == 1)
            mainMenu(u, db);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u, db);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void createNewAcc(struct User *u, sqlite3 *db) // creat new account to an exist user
{
    struct Record r; // the entred data
    int err = 0;

    system("clear");
    printf("\t\t\t===== New record =====\n");

    scanDate(&r);
    scanAccountNumber(&r, u, db);
    printf("\nEnter the country:");
    scanf("%s", r.country);
    scanPhoneNumber(&r);
    scanDeposit(&r);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);
    strcpy( r.name , u->name);
    r.userId = getId(u, db, &err);
    addRecord(r, db);
    success(u, db); // success message
}


// void checkAllAccounts(struct User u, sqlite3 *db)
// {
//     char userName[100];
//     struct Record r;

//     FILE *pf = fopen(RECORDS, "r");

//     system("clear");
//     printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
//     while (getAccountFromFile(pf, userName, &r))
//     {
//         if (strcmp(userName, u.name) == 0)
//         {
//             printf("_____________________\n");
//             printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
//                    r.accountNbr,
//                    r.deposit.day,
//                    r.deposit.month,
//                    r.deposit.year,
//                    r.country,
//                    r.phone,
//                    r.amount,
//                    r.accountType);
//         }
//     }
//     fclose(pf);
//     success(u, db);
// }
