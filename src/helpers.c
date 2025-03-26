#include "header.h"

void success(struct User *u, sqlite3 *db, int clear)
{
    int option;
    if (clear)
    {
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
    char input[ACCOUNT_ID_LENGHT];
    char *endptr;
    long num;
    int ret;

    system("clear");
    while (1)
    {
        // printf("\nEnter the account number: ");
        // if (!fgets(input, sizeof(input), stdin))
        // {
        //     system("clear");

        //     printf("%s", ERROR_READING);
        //     continue;
        // }

        // input[strcspn(input, "\n")] = 0;
        scanLen("\nEnter the account number: ", input,  ACCOUNT_ID_LENGHT);
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
        {
            system("clear");

            printf("%s", INVALID_INPUT);
            continue;
        }
        num = strtol(start, &endptr, 10);
        if (*endptr != '\0')
        {
            system("clear");
            printf("%s", INVALID_NUMBER_INPUT);
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            system("clear");

            printf("%s", OUT_OF_RANGE);
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            system("clear");
            printf("%s", OVER_FLOW);
            continue;
        }
        if (num < 1)
        {
            system("clear");
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
            system("clear");
            printf("%s", ACCOUNT_DUP);
            continue;
        }
        break;
    }
    return 1;
}

void scanPhoneNumber(struct Record *r)
{
    char input[PHONE_LENGHT];

    while (1)
    {
        system("clear");
        scanLen("\nEnter the phone number: ", input,  PHONE_LENGHT);
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
        if (length < 7 || length > PHONE_LENGHT)
        {
            printf("%s", INVALID_PHONE_LENGTH);
            continue;
        }

        strncpy(r->phone, input, PHONE_LENGHT);
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
        break;
    }
}

void scanCountry(struct Record *r)
{
    system("clear");
    scanLen("\nEnter the country:", r->country, COUNTRY_LENGHT);

    while (!isCountryValid(r->country))
    {
        system("clear");
        printf("%s", INVALID_COUNTRY);
        scanLen("\nEnter the country:", r->country, COUNTRY_LENGHT);
    }
}

void scanAccountType(struct Record *r)
{
    char *msg = "\nChoose the type of account:\n\t-> savings\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:";
    system("clear");
    scanLen(msg, r->accountType, ACCOUNT_TYPE_LENGHT);
    while (!isAccountTypeVlid(r->accountType))
    {
        system("clear");
        printf("%s", INVALID_ACCOUNT_TYPE);
        scanLen(msg, r->accountType, ACCOUNT_TYPE_LENGHT);
    }
}

int isAccountTypeVlid(const char *type)
{
    const size_t typesCount = 5;

    const char *types[] = {
        "savings", "current", "fixed01", "fixed02", "fixed03"};

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

void getAccountId(struct User *u, sqlite3 *db, int *accountId)
{
    int tmp;

    system("clear");
    while (1)
    {
        printf("\n\n\t\tPlease enter the Account ID you wish to modify or update.\n"
               "\t\tEnsure the ID is correct and exists in the system.\n");
        printf("\t\tTo view all available accounts, return to the main menu by entering -1.\n");
        scanInt(accountId, "Account ID: ", -1, INT_MAX);
        if (*accountId == -1)
        {
            mainMenu(u, db);
        }
        tmp = isAccountExist(u, db, *accountId);
        if (tmp == -1)
        {
            failure(u, db, 1);
        }
        else if (!tmp)
        {
            system("clear");
            printf(INVALIDE_ACCOUNT_ID);
            continue;
        }
        break;
    }
}

// savings: interest rate 7%
// fixed01(1 year account): interest rate 4%
// fixed02(2 year account): interest rate 5%
// fixed03(3 year account): interest rate 8%
void printInterest(char accountType[ACCOUNT_TYPE_LENGHT], double amount, char date[DATE_LENGHT])
{
    double tmp;
    char **dateTmp;

    dateTmp = split(date, '/');
    if (strcmp(accountType, "current") == 0)
    {
        printf("You will not get interests because the account is of type current\n");
        clear(dateTmp, 3);
        return;
    }
    else if (strcmp(accountType, "savings") == 0)
    {
        tmp = amount * 7 / 100 / 12;
    }
    else if (strcmp(accountType, "fixed01") == 0)
    {
        tmp = amount * 4 / 100 / 12;
    }
    else if (strcmp(accountType, "fixed02") == 0)
    {
        tmp = amount * 5 / 100 / 12;
    }
    else if (strcmp(accountType, "fixed03") == 0)
    {
        tmp = amount * 8 / 100 / 12;
    }

    printf("You will get $%.2f as interest on day %s of every month\n", tmp, dateTmp[0]);
    clear(dateTmp, 3);
}