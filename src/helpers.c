#include "header.h"

int isAccountExist(struct User *u, sqlite3 *db, int accountId)
{
    // struct Record cr; // tmp to store data from the record file
    // char *sql = "SELECT * FROM records WHERE name = '?' AND accountId = '?'";
    // sqlite3_stmt *stmt;

    // if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    // {
    //     exit(1); // FIXME: avoid using exit
    // }

    // (void)cr;
    (void)u;
    (void)db;
    (void)accountId;
    return 0;
}

void success(struct User *u, sqlite3 *db)
{
    int option;
    system("clear");
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanInt(&option);
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

    while (1)
    {
        system("clear");
        printf("\nEnter the account number: ");
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.");
            continue;
        }

        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
        {
            printf("❌ Invalid input! Please enter a valid account number.");
            continue;
        }
        num = strtol(start, &endptr, 10);
        if (*endptr != '\0')
        {
            printf("❌ Invalid input! Only numbers are allowed.");
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.");
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("❌ Error: Integer overflow/underflow.");
            continue;
        }
        r->accountId = (int)num;
        // TODO: check if the account s already exist
        if (isAccountExist(u, db, r->accountId))
        {
            printf("❌ Error: This account already exists. Please enter a different number.");
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

    while (1)
    {
        system("clear");
        printf("\nEnter the phone number:");
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.");
            continue;
        }

        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;
        if (*start == '\0')
        {
            printf("❌ Invalid input! Please enter a valid account number.");
            continue;
        }
        num = strtol(start, &endptr, 10);
        if (*endptr != '\0')
        {
            printf("❌ Invalid input! Only numbers are allowed.");
            continue;
        }
        if ((num == LONG_MAX || num == LONG_MIN) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.");
            continue;
        }
        if (num > INT_MAX || num < INT_MIN)
        {
            printf("❌ Error: Integer overflow/underflow.");
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

    while (1)
    {
        system("clear");
        printf("\nEnter amount to deposit: $");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.");
            continue;
        }
        input[strcspn(input, "\n")] = 0;
        char *start = input;
        while (isspace((unsigned char)*start))
            start++;

        if (*start == '\0')
        {
            printf("❌ Invalid input! Please enter a valid amount.");
            continue;
        }
        errno = 0;
        num = strtod(start, &endptr);
        if (*endptr != '\0')
        {
            printf("❌ Invalid input! Only numbers are allowed.");
            continue;
        }
        if ((num == HUGE_VAL || num == -HUGE_VAL) && errno == ERANGE)
        {
            printf("❌ Error: Number out of range.");
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
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (1)
    {
        system("clear");
        printf("\nEnter today's date(mm/dd/yyyy):");

        if (!fgets(input, sizeof(input), stdin))
        {
            printf("❌ Error reading input. Please try again.");
            continue;
        }
        input[strcspn(input, "\n")] = 0;

        if (sscanf(input, "%2d/%2d/%4d", &month, &day, &year) != 3)
        {
            printf("❌ Invalid format! Please enter in MM/DD/YYYY format.");
            continue;
        }
        if (year < 1900 || year > 2200)
        {
            printf("❌ Invalid year!.");
            continue;
        }
        if (month < 1 || month > 12)
        {
            printf("❌ Invalid month! Enter a value between 1 and 12.");
            continue;
        }
        if (month == 2 && isLeapYear(year))
        {
            daysInMonth[2] = 29;
        }
        if (day < 1 || day > daysInMonth[month])
        {
            printf("❌ Invalid day! Enter a valid day for the given month.");
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
        printf("❌ Invalid country! Enter a valid country.\n");
        printf("the country must be lowercase.\n");
        printf("Enter the country:");
        fgets(r->country, sizeof(r->country), stdin);
        r->country[strcspn(r->country, "\n")] = 0;
    }
}

int isCountryValid(const char *name)
{
    const char *countries[] = {
        "afghanistan", "albania", "algeria", "andorra", "angola", "antigua and barbuda",
        "argentina", "armenia", "australia", "austria", "azerbaijan", "bahamas", "bahrain",
        "bangladesh", "barbados", "belarus", "belgium", "belize", "benin", "bhutan", "bolivia",
        "bosnia and herzegovina", "botswana", "brazil", "brunei", "bulgaria", "burkina faso",
        "burundi", "cabo verde", "cambodia", "cameroon", "canada", "central african republic",
        "chad", "chile", "china", "colombia", "comoros", "congo", "costa rica", "croatia",
        "cuba", "cyprus", "czech republic", "democratic republic of the congo", "denmark",
        "djibouti", "dominica", "dominican republic", "ecuador", "egypt", "el salvador",
        "equatorial guinea", "eritrea", "estonia", "eswatini", "ethiopia", "fiji", "finland",
        "france", "gabon", "gambia", "georgia", "germany", "ghana", "greece", "grenada",
        "guatemala", "guinea", "guinea-bissau", "guyana", "haiti", "honduras", "hungary",
        "iceland", "india", "indonesia", "iran", "iraq", "ireland", "israel", "italy",
        "ivory coast", "jamaica", "japan", "jordan", "kazakhstan", "kenya", "kiribati",
        "kuwait", "kyrgyzstan", "laos", "latvia", "lebanon", "lesotho", "liberia", "libya",
        "liechtenstein", "lithuania", "luxembourg", "madagascar", "malawi", "malaysia",
        "maldives", "mali", "malta", "marshall islands", "mauritania", "mauritius",
        "mexico", "micronesia", "moldova", "monaco", "mongolia", "montenegro", "morocco",
        "mozambique", "myanmar", "namibia", "nauru", "nepal", "netherlands", "new zealand",
        "nicaragua", "niger", "nigeria", "north korea", "north macedonia", "norway",
        "oman", "pakistan", "palau", "palestine", "panama", "papua new guinea", "paraguay",
        "peru", "philippines", "poland", "portugal", "qatar", "romania", "russia", "rwanda",
        "saint kitts and nevis", "saint lucia", "saint vincent and the grenadines", "samoa",
        "san marino", "sao tome and principe", "saudi arabia", "senegal", "serbia", "seychelles",
        "sierra leone", "singapore", "slovakia", "slovenia", "solomon islands", "somalia",
        "south africa", "south korea", "south sudan", "spain", "sri lanka", "sudan", "suriname",
        "sweden", "switzerland", "syria", "taiwan", "tajikistan", "tanzania", "thailand",
        "timor-leste", "togo", "tonga", "trinidad and tobago", "tunisia", "turkey", "turkmenistan",
        "tuvalu", "uganda", "ukraine", "united arab emirates", "united kingdom", "united states",
        "uruguay", "uzbekistan", "vanuatu", "vatican city", "venezuela", "vietnam",
        "yemen", "zambia", "zimbabwe"};
    const size_t countries_count = 196;

    for (size_t i = 0; i < countries_count; i++)
    {
        if (strcmp(countries[i], name) == 0)
        {
            return 1;
        }
    }
    return 0;
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
        printf("❌ Invalid account type! Enter a valid account type.\n");
        printf("the account type must be lowercase.\n");
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