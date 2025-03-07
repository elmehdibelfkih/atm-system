#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char a[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n");
    printf("\n\t\t\t\t\t User Login: ");
    fgets(a, 50, stdin);
    a[strcspn(a, "\n")] = 0;

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    printf("\n\t\t\t\t\t Enter the password to login: ");
    fgets(pass, 50, stdin);
    pass[strcspn(pass, "\n")] = 0;

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

int registration(sqlite3 *db, struct User *u) {
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t      Bank Management System\n");
    printf("\n\n\n\t\t\t\t   ======= registration =======\n");
    printf("\n\t\t\t\t\t User Login: ");
    fgets(u->name, sizeof(u->name), stdin);
    u->name[strcspn(u->name, "\n")] = 0;


    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
    printf("\n\t\t\t\t\t Enter the password: ");
    fgets(u->password, sizeof(u->password), stdin);
    u->password[strcspn(u->password, "\n")] = 0;

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
    system("clear");
    return addUser(u->name, u->password, db);
}