#include "Sort.h"

void swapIDE(ide *a, ide *b) {
    ide tmp = *a;
    *a      = *b;
    *b      = tmp;
}

void sortMenu(int len, ide array[len]) {
    char fields[4][30] = {"Nazwa", "Autor", "Wersja", "Licencja"};
    char orders[2][30] = {"Rosn\245co", "Malej\245co"};

    int field = spawnMenu(
        "\x1b[106m\x1b[30m Sortowanie bazy danych \x1b[0m\n\n"
        "\x1b[33mWybierz pole wed\210ug kt\242rego baza ma by\206 sortowana:\x1b[0m",
        4, fields);
    int order = spawnMenu(
        "\x1b[106m\x1b[30m Sortowanie bazy danych \x1b[0m\n\n"
        "\x1b[33mWybierz porz\245dek sortowania:\x1b[0m",
        2, orders);

    sortArray(len, array, field, order);

    system("cls");
    printf(
        "\x1b[106m\x1b[30m Sortowanie bazy danych \x1b[0m\n\n"
        "\x1b[32mBaza zosta\210a posortowana pomy\230lnie.\n\n"
        "\x1b[5m\x1b[94mNaci\230nij dowolny klawisz aby kontynuowa\206...\x1b[0m");
    getch();
}

void sortArray(int len, ide array[len], short int field, short int order) {
    ide tmp;

    for (int i = 0; i < len; i++)
        for (int j = 0; j < len - i - 1; j++) {
            switch (field) {
                case 0:
                    if ((!order && (strcmp(array[j].name, array[j + 1].name) > 0)) ||
                        (order && (strcmp(array[j].name, array[j + 1].name) < 0)))
                        swapIDE(&array[j], &array[j + 1]);
                    break;
                case 1:
                    if ((!order && (strcmp(array[j].author, array[j + 1].author) > 0)) ||
                        (order && (strcmp(array[j].author, array[j + 1].author) < 0)))
                        swapIDE(&array[j], &array[j + 1]);
                    break;
                case 2:
                    if ((!order && (strcmp(array[j].version, array[j + 1].version) > 0)) ||
                        (order && (strcmp(array[j].version, array[j + 1].version) < 0)))
                        swapIDE(&array[j], &array[j + 1]);
                    break;
                case 3:
                    if ((!order && (strcmp(array[j].license, array[j + 1].license) > 0)) ||
                        (order && (strcmp(array[j].license, array[j + 1].license) < 0)))
                        swapIDE(&array[j], &array[j + 1]);
                    break;
            }
        }
}
