#include "Overview.h"

void overview(dbFile *db) {
    ide *array;
    int len = loadDB(db, &array), ptr = 0, exitflag = 0;

    while (!exitflag) {
        system("cls");

        if (len) {
            printf(
                "\x1b[104m\x1b[30m Przegl\245d bazy danych \x1b[0m\n\n"
                "\x1b[33mNazwa:\x1b[0m     \x1b[96m%s\x1b[0m\n"
                "\x1b[33mAutor:\x1b[0m     \x1b[96m%s\x1b[0m\n"
                "\x1b[33mWersja:\x1b[0m    \x1b[96m%s\x1b[0m\n"
                "\x1b[33mLicencja:\x1b[0m  \x1b[96m%s\x1b[0m\n\n"
                "\x1b[107m\x1b[30m [%i/%i] \x1b[0m\n",
                array[ptr].name, array[ptr].author, array[ptr].version, array[ptr].license, ptr + 1, len);
        } else {
            printf(
                "\x1b[104m\x1b[30m Przegl\245d bazy danych \x1b[0m\n\n"
                "\n\x1b[33mBaza danych jest pusta.\n\x1b[0m\n\n"
                "\x1b[107m\x1b[30m [0/0] \x1b[0m\n");
        }

        printf(
            "\n\n\x1b[36mSterowanie:\n"
            "\x1b[5m\x1b[35mD\x1b[0m\x1b[32m - \x1b[36mdodaj rekord       "
            "\x1b[5m\x1b[35m\021 \020\x1b[0m\x1b[32m      - \x1b[36mwyb\242r rekordu\n"
            "\x1b[5m\x1b[35mU\x1b[0m\x1b[32m - \x1b[36musu\344 rekord        "
            "\x1b[5m\x1b[35mHOME \x1b[0m\x1b[32m/ \x1b[5m\x1b[35m\036\x1b[0m\x1b[32m - "
            "\x1b[36mprzejd\253 na pocz\245tek bazy\n"
            "\x1b[5m\x1b[35mM\x1b[0m\x1b[32m - \x1b[36mmodyfikuj rekord   "
            "\x1b[5m\x1b[35mEND  \x1b[0m\x1b[32m/ \x1b[5m\x1b[35m\037\x1b[0m\x1b[32m - "
            "\x1b[36mprzejd\253 na koniec bazy\n"
            "\x1b[5m\x1b[35mS\x1b[0m\x1b[32m - \x1b[36msortowanie bazy    "
            "\x1b[5m\x1b[35mESC\x1b[0m\x1b[32m      - \x1b[36mpowr\242t do menu\x1b[0m\n");

        switch (getch()) {
            case 0:
            case 224:
                switch (getch()) {
                    case 77:  // ArrowRight
                        ptr++;
                        break;
                    case 75:  // ArrowLeft
                        ptr--;
                        break;
                    case 71:  // HOME
                    case 72:  // ArrowUp
                        ptr = 0;
                        break;
                    case 79:  // END
                    case 80:  // ArrowDown
                        ptr = len - 1;
                        break;
                }
                break;
            case 'b':
            case 'B':
                ptr++;
                break;
            case 'y':
            case 'Y':
                ptr--;
                break;
            case 'g':
            case 'G':
                ptr = 0;
                break;
            case 'h':
            case 'H':
                ptr = len - 1;
                break;
            case 'd':
            case 'D':
                addRecord(&len, &array);
                saveDB(db, len, array);
                ptr = len - 1;
                break;
            case 'u':
            case 'U':
                deleteRecord(&len, &array, ptr);
                saveDB(db, len, array);
                break;
            case 'm':
            case 'M':
                modifyRecord(&array[ptr]);
                saveDB(db, len, array);
                break;
            case 's':
            case 'S':
                sortMenu(len, array);
                saveDB(db, len, array);
                break;
            case 27:
                exitflag = 1;
                break;
        }

        if (ptr < 0)
            ptr = 0;
        else if (ptr >= len)
            ptr = len - 1;
    }

    free(array);
}

void addRecord(int *len, ide **array) {
    (*len)++;
    *array = (ide *)realloc(*array, (*len) * sizeof(ide));

    system("cls");
    printf(
        "\x1b[42m\x1b[30m Dodawanie rekordu \x1b[0m\n\n"
        "\x1b[33mPodaj dane nowego rekordu\n"
        "\x1b[33mNazwa:     \x1b[96m");
    scanf("%s", (*array)[(*len) - 1].name);
    fflush(stdin);
    printf("\x1b[33mAutor:     \x1b[96m");
    scanf("%s", (*array)[(*len) - 1].author);
    fflush(stdin);
    printf("\x1b[33mWersja:    \x1b[96m");
    scanf("%s", (*array)[(*len) - 1].version);
    fflush(stdin);
    printf("\x1b[33mLicencja:  \x1b[96m");
    scanf("%s", (*array)[(*len) - 1].license);
    fflush(stdin);
}

void deleteRecord(int *len, ide **array, int delInd) {
    char message[200] = "\x1b[41m\x1b[30m Usuwanie rekordu \x1b[0m\n\n";
    strcat(message, "\x1b[33mNazwa:     \x1b[96m");
    strcat(message, (*array)[delInd].name);
    strcat(message, "\n\x1b[33mAutor:     \x1b[96m");
    strcat(message, (*array)[delInd].author);
    strcat(message, "\n\x1b[33mWersja:    \x1b[96m");
    strcat(message, (*array)[delInd].version);
    strcat(message, "\n\x1b[33mLicencja:  \x1b[96m");
    strcat(message, (*array)[delInd].license);
    strcat(message, "\n\n\x1b[33mCzy na pewno chcesz usun\245\206 ten rekord?\x1b[0m");

    if (spawnMenuYN(message)) {
        ide tmp              = (*array)[(*len) - 1];
        (*array)[(*len) - 1] = (*array)[delInd];
        (*array)[delInd]     = tmp;
        (*len)--;
        *array = (ide *)realloc(*array, (*len) * sizeof(ide));
    }
}

void modifyRecord(ide *record) {
    system("cls");

    char fields[4][30] = {"Nazwa:     ", "Autor:     ", "Wersja:    ", "Licencja:  "};
    strcat(fields[0], record->name);
    strcat(fields[1], record->author);
    strcat(fields[2], record->version);
    strcat(fields[3], record->license);

    int fieldIndex = spawnMenu(
        "\x1b[43m\x1b[30m Edycja rekordu \x1b[0m\n\n"
        "\x1b[33mWybierz pole do modyfikacji:\x1b[0m",
        4, fields);
    system("cls");

    printf(
        "\x1b[43m\x1b[30m Edycja rekordu \x1b[0m\n\n"
        "\x1b[33mNazwa:     \x1b[96m%s\n"
        "\x1b[33mAutor:     \x1b[96m%s\n"
        "\x1b[33mWersja:    \x1b[96m%s\n"
        "\x1b[33mLicencja:  \x1b[96m%s\n\n"
        "\x1b[33mPodaj now\245 warto\230\206 pola\n\n",
        record->name, record->author, record->version, record->license);

    switch (fieldIndex) {
        case 0:
            printf("\x1b[33mNazwa:     \x1b[96m");
            scanf("%s", &record->name);
            break;
        case 1:
            printf("\x1b[33mAutor:     \x1b[96m");
            scanf("%s", &record->author);
            break;
        case 2:
            printf("\x1b[33mWersja:    \x1b[96m");
            scanf("%s", &record->version);
            break;
        case 3:
            printf("\x1b[33mLicencja:  \x1b[96m");
            scanf("%s", &record->license);
            break;
    }

    printf("\x1b[0m");
}
