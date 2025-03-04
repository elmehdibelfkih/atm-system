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
    char input[50];
    char *endptr;
    long num;

    while (getchar() != '\n')
        ;
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
            printf("❌ Invalid input! Only numbers are allowed.\n");
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.\n");
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("❌ Error: Integer overflow/underflow.\n");
            continue;
        }
        r->accountNbr = (int)num;
        // TODO: check if the account s already exist
        if (isAccountExist(u, db, r->accountNbr))
        {
            printf("❌ Error: This account already exists. Please enter a different number.\n");
            continue;
        }
        break;
    }
}

void scanPhoneNumber(struct Record *r)
{
    char input[50];
    char *endptr;
    long num;

    while (getchar() != '\n')
        ;
    while (1)
    {
        printf("\nEnter the phone number:");
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
            printf("❌ Invalid input! Only numbers are allowed.\n");
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.\n");
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("❌ Error: Integer overflow/underflow.\n");
            continue;
        }
        r->phone = (int)num;
        break;
    }
}

void scanDeposit(struct Record *r)
{
    char input[50];
    char *endptr;
    double num;

    while (getchar() != '\n')
        ;

    while (1)
    {
        printf("\nEnter amount to deposit: $");

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
            printf("❌ Invalid input! Please enter a valid amount.\n");
            continue;
        }
        errno = 0;
        num = strtod(start, &endptr);
        if (*endptr != '\0')
        {
            printf("❌ Invalid input! Only numbers are allowed.\n");
            continue;
        }
        if ((num == HUGE_VAL || num == -HUGE_VAL) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.\n");
            continue;
        }
        r->amount = num;
        break;
    }
}

int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void scanDate(struct Record *r)
{
    char input[20];
    int month, day, year;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Days in each month

    while (getchar() != '\n')
        ;

    while (1)
    {
        printf("\nEnter today's date(mm/dd/yyyy):");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.\n");
            continue;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%2d/%2d/%4d", &month, &day, &year) != 3)
        {
            printf("❌ Invalid format! Please enter in MM/DD/YYYY format.\n");
            continue;
        }
        if (year < 1900 || year > 2200)
        {
            printf("❌ Invalid year!.\n");
            continue;
        }
        if (month < 1 || month > 12)
        {
            printf("❌ Invalid month! Enter a value between 1 and 12.\n");
            continue;
        }
        if (month == 2 && isLeapYear(year))
        {
            daysInMonth[2] = 29;
        }
        if (day < 1 || day > daysInMonth[month])
        {
            printf("❌ Invalid day! Enter a valid day for the given month.\n");
            continue;
        }
        snprintf(r->date, sizeof(r->date), "%02d/%02d/%04d", month, day, year);
        r->deposit.day = day;
        r->deposit.month = month;
        r->deposit.year = year;
        break;
    }
}