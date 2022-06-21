#ifndef MENU_H
#define MENU_H

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

int spawnMenu(char message[200], int optionsLen, char options[optionsLen][30]);
int spawnMenuYN(char message[200]);

#endif
