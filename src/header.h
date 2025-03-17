#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>
#include "errors.h"
#include "SQLiteQueries.h"

#define INIT_MENU "\n\n\t\t======= ATM =======\n\n\t\t\
-->> Feel free to login / register :\n\n\t\t\
[1]- login\n\n\t\t\
[2]- register\n\n\t\t\
[3]- exit\n\n"

#define MAIN_MENU "\n\n\t\t======= ATM =======\n\n\n\t\t\
[1]- Create a new account\n\n\t\t\
[2]- Update account information\n\n\t\t\
[3]- Check accounts\n\n\t\t\
[4]- Check list of owned account\n\n\t\t\
[5]- Make Transaction\n\n\t\t\
[6]- Remove existing account\n\n\t\t\
[7]- Transfer ownership\n\n\t\t\
[8]- Exit\n\n"

#define NAME_LENGHT 50
#define PASSWORD_LENGHT 50
#define PHONE_LENGHT 20
#define ACCOUNT_TYPE_LENGHT 10
#define DATE_LENGHT 11


typedef struct
{
    char *error_message;
} MyError;

extern MyError my_error;

struct Date
{
    int month, day, year;
};

struct Record
{
    char name[NAME_LENGHT];
    char country[PASSWORD_LENGHT];
    char accountType[ACCOUNT_TYPE_LENGHT];
    int id;
    char phone[PHONE_LENGHT];
    int userId;
    int accountId;
    double amount;
    char date[DATE_LENGHT];
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[NAME_LENGHT];
    char password[PASSWORD_LENGHT];
};

// authentication functions
void loginMenu(char a[NAME_LENGHT], char pass[PASSWORD_LENGHT]);
int registration(sqlite3 *db, struct User *u);
int getPassword(struct User *u, sqlite3 *db, char password[PASSWORD_LENGHT]);
int getId(struct User *u, sqlite3 *db, int *err);

// mainMenu function
void createNewAcc(struct User *u, sqlite3 *db);
void updateAccount(struct User *u, sqlite3 *db);
void checkExistingAccounts(struct User *u, sqlite3 *db);
void makeTransaction(struct User *u, sqlite3 *db);
void removeExistingAccount(struct User *u, sqlite3 *db);
void transferAccount(struct User *u, sqlite3 *db);
void checkAllAccounts(struct User *u, sqlite3 *db);

// menus functions
void mainMenu(struct User *u, sqlite3 *db);
void initMenu(struct User *u, sqlite3 *db);

// data base function
void intiDataBase(sqlite3 **db);
int addUser(char *name, char *passWord, sqlite3 *db);
void addRecord(struct Record r, sqlite3 *db);
int updateCountry(struct User *u, sqlite3 *db, int accountId);
int updatePhone(struct User *u, sqlite3 *db, int accountId);

// helpers
int isAccountExist(struct User *u, sqlite3 *db, int accountId);
void success(struct User *u, sqlite3 *db, int clear);
void failure(struct User *u, sqlite3 *db, int printErr);
int scanAccountNumber(struct Record *r, struct User *u, sqlite3 *db);
void scanPhoneNumber(struct Record *r);
void scanDeposit(struct Record *r);
void scanDate(struct Record *r);
int isLeapYear(int year);
void scanCountry(struct Record *r);
void scanAccountType(struct Record *r);
int isCountryValid(const char *name);
int isAccountTypeVlid(const char *type);
void printAccountInfo(struct Record r);
int deleteAccount(struct User *u, sqlite3 *db, int accountId);

// tools
int n_of_world(char const *s, char c);
int plen(char **spl, const char *s, char c);
int clear(char **spl, int p);
char **split(char const *s, char c);
char *substr(char const *s, unsigned int start, size_t len);
void scanInt(int *result, char *prefix, int start, int end);

#endif