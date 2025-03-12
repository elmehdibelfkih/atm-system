#include "header.h"

void mainMenu(struct User *u, sqlite3 *db)
{
    int option;

    system("clear");
    printf("\n\t\t-->> welcome %s <<--\n\n", u->name);
    printf(MAIN_MENU);
    // scanInt(&option);
    scanInt(&option, "option: ", 1, 8);

    switch (option)
    {
    case 1:
        createNewAcc(u, db);
        break;
    case 2:
        // TODO: add your **Update account information** function
        updateAccount(u, db);
        break;
    case 3:
        // TODO: add your **Check the details of existing accounts** function
        // checkExistingAccounts(u, db);
        break;
    case 4:
        checkAllAccounts(u, db);
        break;
    case 5:
        // TODO: add your **Make transaction** function
        // makeTransaction(u, db);
        break;
    case 6:
        // TODO: add your **Remove existing account** function
        // removeExistingAccount(u, db);
        break;
    case 7:
        // TODO: add your **Transfer owner** function
        // transferAccount(u, db);
        break;
    case 8:
        initMenu(u, db);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void initMenu(struct User *u, sqlite3 *db)
{
    int r = 0;
    int option;
    char tmpPass[PASSWORD_LENGHT];
    int ret = 0;
    system("clear");
    while (!r)
    {
        printf(INIT_MENU);
        // scanInt(&option);
        scanInt(&option, "option: ", 1, 3);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            ret = getPassword(u, db, tmpPass);
            if (ret == -1)
            {
                system("clear");
                printf("%s\n", my_error.error_message);
                continue;
            }
            if (ret == 1 || strcmp(u->password, tmpPass) != 0)
            {
                system("clear");
                printf(LOGIN_FATAL);
                break;
            }
            r = 1;
            mainMenu(u, db);
            break;
        case 2:
            r = registration(db, u);
            if (!r)
            {
                printf("%s", my_error.error_message);
                continue;
            }
            mainMenu(u, db);
            break;
        case 3:
            exit(0);
            break;
        default:
            system("clear");
            printf("Insert a valid operation!\n");
            option = 0;
            break;
        }
    }
};
