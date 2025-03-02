#include "header.h"

// char *getDate() {

// }

int isAccountExist(struct User u, sqlite3 *db, int accountNbr)
{
    struct Record cr; // tmp to store data from the record file

    (void)cr;
    (void)u;
    (void)db;
    (void)accountNbr;
    return 0;
}

void success(struct User u, sqlite3 *db)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u, db);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

int isAccDataValide(struct Record r)
{
    (void)r;
    return 0;
}
