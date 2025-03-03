#include "header.h"


int isAccountExist(struct User *u, sqlite3 *db, int accountNbr)
{
    struct Record cr; // tmp to store data from the record file

    (void)cr;
    (void)u;
    (void)db;
    (void)accountNbr;
    return 0;
}

void success(struct User *u, sqlite3 *db)
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

void scanAccountNumber(struct Record *r, struct User *u, sqlite3 *db)
{
    char input[50]; // Buffer for user input
    char *endptr;
    long num;

    while (getchar() != '\n');
    while (1)
    {
        printf("\nEnter the account number: ");
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.\n");
            continue;
        }

        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
        {
            printf("1❌ Invalid input! Please enter a valid account number.\n");
            continue;
        }
        num = strtol(start, &endptr, 10);
        if (*endptr != '\0')
        {
            printf("2❌ Invalid input! Only numbers are allowed.\n");
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("3❌ Error: Number out of range.\n");
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("4❌ Error: Integer overflow/underflow.\n");
            continue;
        }
        r->accountNbr = (int)num;
        // TODO: check if the account s already exist
        if (isAccountExist(u, db, r->accountNbr))
        {
            printf("5❌ Error: This account already exists. Please enter a different number.\n");
            continue;
        }
        break;
    }
}