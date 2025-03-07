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



typedef struct {
    char* error_message;
} MyError;

extern MyError my_error;

struct Date
{
    int month, day, year;
};

struct Record
{
    char name[50];
    char country[50];
    char accountType[10];
    int id;
    int phone;
    int userId;
    int accountId;
    double amount;
    char date[11];
    struct Date deposit;
    struct Date withdraw;
};

struct User
{
    int id;
    char name[50];
    char password[50];
};

// authentication functions
void loginMenu(char a[50], char pass[50]);
int registration(sqlite3 *db, struct User *u);
int getPassword(struct User *u, sqlite3 *db, char password[50]);
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

// helpers
int isAccountExist(struct User *u, sqlite3 *db, int accountId);
int isAccDataValide(struct Record r);
void success(struct User *u, sqlite3 *db);
void scanAccountNumber(struct Record *r, struct User *u, sqlite3 *db);
void scanPhoneNumber(struct Record *r);
void scanDeposit(struct Record *r);
void scanDate(struct Record *r);
int isLeapYear(int year);
void scanCountry(struct Record *r);
void scanAccountType(struct Record *r);
int isCountryValid(const char *name);
int isAccountTypeVlid(const char *type);

// tools
int n_of_world(char const *s, char c);
int plen(char **spl, const char *s, char c);
int clear(char **spl, int p);
char **split(char const *s, char c);
char *substr(char const *s, unsigned int start, size_t len);
void scanInt(int *result);

#endif