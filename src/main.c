#include "DB.h"
#include "MainMenu.h"

int main() {
    dbFile db = {NULL, "", 0};

    mainMenu(&db);

    return 0;
}
