#include "header.h"

int main()
{
    struct User u;
    sqlite3 *db;
    intiDataBase(&db);
    initMenu(&u, db);
    mainMenu(u, db);
    sqlite3_close(db);
    return 0;
}
