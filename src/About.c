#include "About.h"

void aboutProgram() {
    system("cls");
    printf(
        "\x1b[45m\x1b[30m O programie \x1b[0m\n\n"
        "\x1b[33mMinibaza danych przechowuj\245ca informacje o wybranych\n"
        "\230rodowiskach programistycznych zosta\210a stworzona w ramach\n"
        "projektu zaliczeniowego z przedmiotu \x1b[96mPodstawy Programowania II\x1b[33m\n"
        "na kierunku informatyka \x1b[96mAkademii Nauk Stosowanych w Elbl\245gu\n\n"
        "\x1b[95mAutor:\n"
        "    \x1b[31mMicha\210 Lewiecki\n"
        "    \x1b[32mStudent I roku informatyki\n"
        "    Indeks: 20197\n"
        "    20197@student.ans-elblag.pl\n\n"
        "\x1b[95mKoordynator przedmiotu:\x1b[32m\n"
        "    \x1b[91mdr hab. in\276. \x1b[31mMaciej Czy\276ak\n"
        "    \x1b[32mProfesor Akademii Nauk Stosowanych\n"
        "    m.czyzak@ans-elblag.pl\n\n\n\n"
        "\x1b[5m\x1b[94mNaci\230nij dowolny klawisz aby kontynuowa\206...\x1b[0m");
    getch();
}
