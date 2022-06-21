#include "MainMenu.h"

void mainMenu(dbFile *db) {
    int menu, exitFlag = 0;
    char msg[200];

    do {
        strcpy(msg, "\x1b[102m\x1b[30m Minibaza danych \x1b[0m\n\n");

        if (db->isOpen) {
            strcat(msg, "\x1b[33mOtwarty plik: \x1b[94m");
            strcat(msg, db->name);
            strcat(msg, "\x1b[36m\n\nMenu g\210\242wne:\x1b[0m");

            char options[6][30] = {
                "Przegl\245daj baz\251 danych", "Sortuj baz\251 danych", "Usu\344 baz\251 danych",
                "Zamknij baz\251 danych",       "O programie",           "Wyj\230cie",
            };

            menu = spawnMenu(msg, 6, options);
            switch (menu) {
                case 0:
                    overview(db);
                    break;
                case 1: {  // Blok kodu, żeby zmienne zostały pod koniec zniszczone
                    ide *array;
                    int len = loadDB(db, &array);

                    sortMenu(len, array);

                    saveDB(db, len, array);
                    free(array);
                } break;
                case 2:
                    strcpy(msg, "\x1b[101m\x1b[30m Usuwanie bazy danych \x1b[0m\n\n");
                    strcat(msg, "\x1b[33mCzy napewno chcesz usun\245\206 plik \x1b[94m");
                    strcat(msg, db->name);
                    strcat(msg, "\x1b[33m?\x1b[0m");
                    if (spawnMenuYN(msg) == 1)
                        deleteDB(db);
                    break;
                case 3:
                    closeDB(db);
                    break;
                case 4:
                    aboutProgram();
                    break;
                case 5:
                    closeDB(db);
                    system("cls");
                    return;
            }
        } else {
            strcat(msg, "\x1b[36mMenu g\210\242wne:\x1b[0m");
            char options[4][30] = {
                "Otw\242rz baz\251 danych",
                "Utw\242rz now\245 baz\251 danych",
                "O programie",
                "Wyj\230cie",
            };

            menu = spawnMenu(msg, 4, options);
            switch (menu) {
                case 0:
                    openDB(db);
                    break;
                case 1:
                    createDB(db);
                    break;
                case 2:
                    aboutProgram();
                    break;
                case 3:
                    system("cls");
                    return;
            }
        }
    } while (!exitFlag);
}
