#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <time.h>
#include <unistd.h>
struct Date
{
    int month, day, year;
};

struct Record
{
    char name[100];
    char country[100];
    char accountType[10];
    int id;
    int phone;
    int userId;
    int accountNbr;
    double amount;
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
const char *getPassword(struct User u, sqlite3 *db);

// system function
void createNewAcc(struct User u, sqlite3 *db);
void checkAllAccounts(struct User u, sqlite3 *db);

// menus functions
void mainMenu(struct User u, sqlite3 *db);
void initMenu(struct User *u, sqlite3 *db);

// data base functions
void intiDataBase(sqlite3 **db);
int addUser(char *name, char *passWord, sqlite3 *db);

// helpers
int isAccountExist(struct User u, sqlite3 *db, int accountNbr);
int isAccDataValide(struct Record r);
void success(struct User u, sqlite3 *db);
char *getDate();

#endif