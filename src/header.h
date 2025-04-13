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
#include <float.h> 

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

#define NAME_LENGHT 51
#define PASSWORD_LENGHT 51
#define PHONE_LENGHT 21
#define INT_LENGHT 11
#define ACCOUNT_TYPE_LENGHT 11
#define ACCOUNT_ID_LENGHT 11
#define DATE_LENGHT 12
#define COUNTRY_LENGHT 21
#define DEPOSIT_LENGHT 21




typedef struct
{
    char *error_message;
} MyError;

extern MyError my_error;


struct Record
{
    int id;
    int userId;
    int accountId;
    double amount;
    char name[NAME_LENGHT];
    char country[COUNTRY_LENGHT];
    char phone[PHONE_LENGHT];
    char accountType[ACCOUNT_TYPE_LENGHT];
    char date[DATE_LENGHT];
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
int addRecord(struct Record r, sqlite3 *db);
int updateCountry(struct User *u, sqlite3 *db, int accountId);
int updatePhone(struct User *u, sqlite3 *db, int accountId);
int isUserExist(char a[NAME_LENGHT], sqlite3 *db);
int transfer(struct User *u, int accountId, char newOwner[NAME_LENGHT], sqlite3 *db);
int transaction(struct User *u, int accountId, double newAmount, sqlite3 *db);
double getBalance(struct User *u, sqlite3 *db, int accountId);
int getTypeOfAccount(struct User *u, sqlite3 *db, int accountId, char type[ACCOUNT_TYPE_LENGHT]);

// helpers
int isAccountExist(struct User *u, sqlite3 *db, int accountId);
void success(struct User *u, sqlite3 *db, int clear);
void failure(struct User *u, sqlite3 *db, int printErr);
void scanAccountNumber(struct Record *r, struct User *u, sqlite3 *db);
void scanPhoneNumber(struct Record *r);
void scanAmount(struct Record *r, char *typeOfScan);
void scanDate(struct Record *r);
void scanCountry(struct Record *r);
void scanAccountType(struct Record *r);
int isAccountTypeVlid(const char *type);
void printAccountInfo(struct Record r);
int deleteAccount(struct User *u, sqlite3 *db, int accountId);
void checkAccountId(struct User *u, sqlite3 *db, int *accountId);
void printInterest(char accountType[ACCOUNT_TYPE_LENGHT], double amount, char date[DATE_LENGHT]);
void withdraw(struct User *u, sqlite3 *db, int accountId);
void deposit(struct User *u, sqlite3 *db, int accountId);

// tools
int isCountryValid(const char *name);
int isLeapYear(int year);
int n_of_world(char const *s, char c);
int plen(char **spl, const char *s, char c);
int clear(char **spl, int p);
char **split(char const *s, char c);
char *substr(char const *s, unsigned int start, size_t len);
void scanInt(int *result, char *prefix, int start, int end);
void scanLen(char *prefix, char *str, int len, int clear);

#endif