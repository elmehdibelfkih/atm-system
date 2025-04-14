#include <termios.h>
#include "header.h"


void loginMenu(char a[NAME_LENGHT], char pass[PASSWORD_LENGHT])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n");
    scanLen("\n\t\t\t\t\t User Login: ", a, NAME_LENGHT, 0);

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
    scanLen("\n\t\t\t\t\t Enter the password to login: ", pass, PASSWORD_LENGHT, 0);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return exit(1);
    }
};

int registration(sqlite3 *db, struct User *u)
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t      Bank Management System\n");
    printf("\n\n\n\t\t\t\t   ======= registration =======\n");

    scanLen("\n\t\t\t\t\t User Login: ", u->name, NAME_LENGHT, 0);

    tcgetattr(fileno(stdin), &oflags);
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
    scanLen("\n\t\t\t\t\t Enter the password: ", u->password, PASSWORD_LENGHT, 0);

    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        exit(1);
    }
    system("clear");
    return addUser(u->name, u->password, db);
}