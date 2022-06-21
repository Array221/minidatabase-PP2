#include "Menu.h"

int spawnMenu(char message[200], int optionsLen, char options[optionsLen][30]) {
    int menuSelection = 0;

    while (1) {
        system("cls");
        printf("%s\n", message);

        for (int i = 0; i < optionsLen; i++) {
            if (menuSelection == i)
                printf("\x1b[0m  \020 ");
            else
                printf("\x1b[90m    ");
            printf(options[i]);
            printf("\x1b[0m\n");
        }
        printf(
            "\n\x1b[36mSterowanie:\n"
            "\x1b[5m\x1b[35m\036 \037\x1b[0m\x1b[32m - \x1b[36mwyb\242r opcji    "
            "\x1b[5m\x1b[35mENTER\x1b[0m\x1b[32m - \x1b[36mpotwierdzenie wyboru\n\x1b[0m");

        switch (getch()) {
            case 0:
            case 224:
                switch (getch()) {
                    case 72:  // ArrowUp
                        menuSelection--;
                        break;
                    case 80:  // ArrowDown
                        menuSelection++;
                        break;
                }
                break;
            case 'Y':
            case 'y':
                menuSelection--;
                break;
            case 'B':
            case 'b':
                menuSelection++;
                break;
            case 13:  // Return
                return menuSelection;
                break;
        }

        if (menuSelection < 0)
            menuSelection = optionsLen - 1;
        else if (menuSelection > optionsLen - 1)
            menuSelection = 0;
    }
}

int spawnMenuYN(char message[200]) {
    char options[2][30] = {
        "Nie",
        "Tak",
    };

    return spawnMenu(message, 2, options);
}
