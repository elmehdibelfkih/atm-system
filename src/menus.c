#include "header.h"

// the main menu of the programme
void mainMenu(struct User *u, sqlite3 *db)
{
    int option;

    system("clear");
    printf("\n\t\t-->> welcome %s <<--\n", u->name);
    printf(MAIN_MENU);
    scanInt(&option, "option: ", 1, 8);

    switch (option)
    {
    case 1:
        createNewAcc(u, db);
        break;
    case 2:
        updateAccount(u, db);
        break;
    case 3:
        checkExistingAccounts(u, db);
        break;
    case 4:
        checkAllAccounts(u, db);
        break;
    case 5:
        makeTransaction(u, db);
        break;
    case 6:
        removeExistingAccount(u, db);
        break;
    case 7:
        transferAccount(u, db);
        break;
    case 8:
        initMenu(u, db);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

// the user menu that contains all functions of the user
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
