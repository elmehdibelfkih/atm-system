#include "header.h"

void success(struct User *u, sqlite3 *db, int clear)
{
    int option;
    if (clear) {
        system("clear");
    }
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanInt(&option, "option: ", 0, 1);
    system("clear");
    if (option == 1)
    {
        mainMenu(u, db);
    }
    else if (option == 0)
    {
        initMenu(u, db);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void failure(struct User *u, sqlite3 *db, int printErr)
{
    int option;
    system("clear");
    printf("\n❌ failure!\n\n");
    if (printErr)
    {
        printf("%s", my_error.error_message);
    }
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanInt(&option, "option: ", 0, 1);
    system("clear");
    if (option == 1)
    {
        mainMenu(u, db);
    }
    else if (option == 0)
    {
        initMenu(u, db);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

int scanAccountNumber(struct Record *r, struct User *u, sqlite3 *db)
{
    char input[50];
    char *endptr;
    long num;
    int ret;

    while (1)
    {
        system("clear");
        printf("\nEnter the account number: ");
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("%s", ERROR_READING);
            continue;
        }

        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
        {
            printf("%s", INVALID_INPUT);
            continue;
        }
        num = strtol(start, &endptr, 10);
        if (*endptr != '\0')
        {
            printf("%s", INVALID_NUMBER_INPUT);
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("%s", OUT_OF_RANGE);
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("%s", OVER_FLOW);
            continue;
        }
        if (num < 1) {
            printf("%s", INVALIDE_ACCOUNT_ID_RANGE);
            continue;
        }
        r->accountId = (int)num;
        ret = isAccountExist(u, db, r->accountId);
        if (ret == -1)
        {
            return -1;
        }
        if (ret)
        {
            printf("%s", ACCOUNT_DUP);
            continue;
        }
        break;
    }
    return 1;
}

void scanPhoneNumber(struct Record *r)
{
    char input[50];

    while (1)
    {
        system("clear");
        printf("\nEnter the phone number: ");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("%s", ERROR_READING);
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        int length = 0;
        int has_plus = (input[0] == '+');
        for (int i = has_plus; input[i] != '\0'; i++)
        {
            if (!isdigit(input[i]) && input[i] != ' ' && input[i] != '-')
            {
                printf("%s", INVALID_NUMBER_INPUT);
                goto retry;
            }
            if (isdigit(input[i]))
                length++;
        }

        if (length < 7 || length > 15)
        {
            printf("%s", INVALID_PHONE_LENGTH);
            continue;
        }

        strncpy(r->phone, input, 15);
        r->phone[14] = '\0';
        break;

    retry:;
    }
}

void scanDeposit(struct Record *r)
{
    char input[50];
    char *endptr;
    double num;

    while (1)
    {
        system("clear");
        printf("\nEnter amount to deposit: $");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("%s", ERROR_READING);
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;

        if (*start == '\0')
        {
            printf("%s", INVALID_INPUT);

            continue;
        }
        errno = 0;
        num = strtod(start, &endptr);
        if (*endptr != '\0')
        {
            printf("%s", INVALID_NUMBER_INPUT);

            continue;
        }
        if ((num == HUGE_VAL || num == -HUGE_VAL) && errno == ERANGE)
        {
            printf("%s", OUT_OF_RANGE);
            continue;
        }
        r->amount = num;
        break;
    }
}

void scanDate(struct Record *r)
{
    char input[20];
    int month, day, year;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (1)
    {
        system("clear");
        printf("\nEnter today's date(mm/dd/yyyy):");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("%s", ERROR_READING);
            continue;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%d/%d/%d", &month, &day, &year) != 3)
        {
            printf("%s", INVALID_DATE_FORMAT);
            continue;
        }
        if (year < 1900 || year > 2200)
        {
            printf("%s", INVALID_YEAR);
            continue;
        }
        if (month < 1 || month > 12)
        {
            printf("%s", INVALID_MONTH);
            continue;
        }
        if (month == 2 && isLeapYear(year))
        {
            daysInMonth[2] = 29;
        }
        if (day < 1 || day > daysInMonth[month])
        {
            printf("%s", INVALID_DAY);
            continue;
        }
        snprintf(r->date, sizeof(r->date), "%02d/%02d/%04d", month, day, year);
        r->deposit.day = day;
        r->deposit.month = month;
        r->deposit.year = year;
        break;
    }
}

void scanCountry(struct Record *r)
{
    system("clear");
    printf("\nEnter the country:");
    fgets(r->country, sizeof(r->country), stdin);
    r->country[strcspn(r->country, "\n")] = 0;
    while (!isCountryValid(r->country))
    {
        system("clear");
        printf("%s", INVALID_COUNTRY);
        printf("Enter the country:");
        fgets(r->country, sizeof(r->country), stdin);
        r->country[strcspn(r->country, "\n")] = 0;
    }
}

void scanAccountType(struct Record *r)
{
    system("clear");
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    fgets(r->accountType, sizeof(r->accountType), stdin);
    r->accountType[strcspn(r->accountType, "\n")] = 0;
    while (!isAccountTypeVlid(r->accountType))
    {
        system("clear");
        printf("%s", INVALID_ACCOUNT_TYPE);
        printf("Choose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
        fgets(r->accountType, sizeof(r->accountType), stdin);
        r->accountType[strcspn(r->accountType, "\n")] = 0;
    }
}

int isAccountTypeVlid(const char *type)
{
    const size_t typesCount = 5;

    const char *types[] = {
        "saving", "current", "fixed01", "fixed02", "fixed03"};

    for (size_t i = 0; i < typesCount; i++)
    {
        if (strcmp(types[i], type) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void printAccountInfo(struct Record r)
{
    printf("\nAccount ID: %d\nDeposit Date: %s \ncountry: %s \nPhone number: %s \nAmount deposited: $ %.2f \nType Of Account: %s\n\n",
           r.accountId,
           r.date,
           r.country,
           r.phone,
           r.amount,
           r.accountType);
}