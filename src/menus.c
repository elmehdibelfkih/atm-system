#include "header.h"

void mainMenu(struct User *u, sqlite3 *db)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> welcome %s <<--\n", u->name);
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u, db);
        break;
    case 2:
        // TODO: add your **Update account information** function
        break;
    case 3:
        // TODO: add your **Check the details of existing accounts** function
        break;
    case 4:
        // checkAllAccounts(u, db);
        break;
    case 5:
        // TODO: add your **Make transaction** function
        break;
    case 6:
        // TODO: add your **Remove existing account** function
        break;
    case 7:
        // TODO: add your **Transfer owner** function
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
    int err = 0;
    system("clear");
    while (!r)
    {
        printf("\n\n\t\t======= ATM =======\n");
        printf("\n\t\t-->> Feel free to login / register :\n");
        printf("\n\t\t[1]- login\n");
        printf("\n\t\t[2]- register\n");
        printf("\n\t\t[3]- exit\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(u, db, &err)) != 0 || err)
            {
                system("clear");
                printf("\n\nWrong password!! or User Name\n");
                err = 0;
                break;
            }
            r = 1;
            mainMenu(u, db);
            break;
        case 2:
            r = registration(db, u);
            mainMenu(u, db);
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Insert a valid operation!\n");
            option = 0;
            break;
        }
    }
};
