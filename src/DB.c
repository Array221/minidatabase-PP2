#include "DB.h"

int checkDBName(char fileName[]) {
    int flag   = 0;
    char *baza = strstr(fileName, "baza");
    char *dat  = strstr(fileName, ".dat");

    if (baza && dat && (dat > baza))
        if (isdigit(*(dat - 1)))
            if (strlen(fileName) == 9 || (strlen(fileName) == 10 && isdigit(*(dat - 2))))
                flag = 1;

    return flag;
}

void createDB(dbFile *db) {
    char name[60], fullName[60] = "databases/";
    struct stat dir;

    system("cls");
    printf(
        "\x1b[104m\x1b[30m Tworzenie nowej bazy danych \x1b[0m\n\n"
        "\x1b[33mPodaj nazw\251 pliku bazy danych: \x1b[94m");
    scanf("%s", name);
    fflush(stdin);
    printf("\x1b[0m");
    strcat(fullName, name);

    system("cls");

    if (!(stat("databases/", &dir) == 0 && S_ISDIR(dir.st_mode)))
        mkdir("databases");

    if (!checkDBName(name)) {
        printf(
            "\x1b[104m\x1b[30m Tworzenie nowej bazy danych \x1b[0m\n\n"
            "\x1b[94m\"%s\"\x1b[91m to niepoprawny format nazwy\n\n"
            "\x1b[33mNazwa powinna by\206 w postaci \x1b[94mbazaXX.dat\x1b[33m\n"
            "(gdzie \x1b[94mXX\x1b[33m to liczba z zakresu od 1 do 99)\n\n"
            "\x1b[5m\x1b[36mNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
            name);
        getch();
    } else if (access(fullName, F_OK)) {
        printf(
            "\x1b[104m\x1b[30m Tworzenie nowej bazy danych \x1b[0m\n\n"
            "\x1b[33mTworzenie pliku \x1b[94m%s\x1b[0m",
            fullName);
        FILE *tmp = fopen(fullName, "wb");
        fclose(tmp);

        db->pointer = fopen(fullName, "r+b");
        strcpy(db->name, name);
        db->isOpen = 1;
        sleep(1);
        system("cls");

        printf(
            "\x1b[104m\x1b[30m Tworzenie nowej bazy danych \x1b[0m\n\n"
            "\x1b[32mBaza \x1b[94m%s\x1b[32m zosta\210a pomy\230lnie utworzona.\x1b[33m\n\n"
            "\x1b[5m\x1b[36mNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
            name);
        getch();
    } else {
        printf(
            "\x1b[104m\x1b[30m Tworzenie nowej bazy danych \x1b[0m\n\n"
            "\x1b[91mBaza \x1b[94m%s\x1b[91m ju\276 istnieje\n\n"
            "\x1b[5m\x1b[36mNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
            name);
        getch();
    }
}

void deleteDB(dbFile *db) {
    system("cls");
    char name[60], fullName[60] = "databases/";
    strcat(fullName, db->name);
    strcpy(name, db->name);
    printf(
        "\x1b[101m\x1b[30m Usuwanie bazy danych \x1b[0m\n\n"
        "\x1b[33mUsuwanie pliku \x1b[94m%s\x1b[0m",
        fullName);

    closeDB(db);
    remove(fullName);

    sleep(1);
    system("cls");

    printf(
        "\x1b[101m\x1b[30m Usuwanie bazy danych \x1b[0m\n\n"
        "\x1b[32mBaza \x1b[94m%s\x1b[32m zosta\210a pomy\230lnie usuni\251ta."
        "\x1b[5m\x1b[36m\n\nNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
        name);
    getch();
}

void openDB(dbFile *db) {
    char name[60], fullName[60] = "databases/";

    system("cls");
    printf(
        "\x1b[103m\x1b[30m Otwieranie bazy danych \x1b[0m\n\n"
        "\x1b[33mPodaj nazw\251 pliku bazy danych: \x1b[94m");
    scanf("%s", name);
    fflush(stdin);
    printf("\x1b[0m");
    strcat(fullName, name);

    system("cls");
    if (!checkDBName(name)) {
        printf(
            "\x1b[103m\x1b[30m Otwieranie bazy danych \x1b[0m\n\n"
            "\x1b[94m\"%s\"\x1b[91m to niepoprawny format nazwy\n\n"
            "\x1b[33mNazwa powinna by\206 w postaci \x1b[94mbazaXX.dat\x1b[33m\n"
            "(gdzie \x1b[94mXX\x1b[33m to liczba z zakresu od 1 do 99)\n\n"
            "\x1b[5m\x1b[36mNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
            name);
        getch();
    } else if (!access(fullName, F_OK)) {
        printf(
            "\x1b[103m\x1b[30m Otwieranie bazy danych \x1b[0m\n\n"
            "\x1b[33mOtwieranie pliku \x1b[94m%s\x1b[0m",
            fullName);
        db->pointer = fopen(fullName, "r+b");
        strcpy(db->name, name);
        db->isOpen = 1;
        sleep(1);
    } else {
        printf(
            "\x1b[103m\x1b[30m Otwieranie bazy danych \x1b[0m\n\n"
            "\x1b[91mBaza \x1b[94m%s\x1b[91m nie istnieje\n\n"
            "\x1b[5m\x1b[94mNaci\230nij dowolny klawisz, aby kontynuowa\206...\x1b[0m",
            name);
        getch();
    }
}

void closeDB(dbFile *db) {
    fclose(db->pointer);
    db->isOpen = 0;
    strcpy(db->name, "");
}

int loadDB(dbFile *db, ide **array) {
    fseek(db->pointer, 0, SEEK_END);
    int len = ftell(db->pointer) / sizeof(ide);
    fseek(db->pointer, 0, SEEK_SET);

    ide tmp;
    *array = (ide *)calloc(len, sizeof(ide));

    for (int i = 0; i < len; i++) {
        fread(&tmp, sizeof(ide), 1, db->pointer);
        (*array)[i] = tmp;
    }

    fseek(db->pointer, 0, SEEK_SET);

    return len;
}

void saveDB(dbFile *db, int len, ide *array) {
    char fullName[60] = "databases/";
    strcat(fullName, db->name);

    // Funkcja truncate nie działała w żadnej możliwej konfiguracji,
    // więc usuwanie rozwiązałem w inny sposób
    db->pointer = freopen(fullName, "wb", db->pointer);

    fwrite(array, sizeof(ide), len, db->pointer);

    db->pointer = freopen(fullName, "r+b", db->pointer);
}
