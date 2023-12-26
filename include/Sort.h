#ifndef SORT
#define SORT

#include <string.h>
#include <windows.h>
#include "IDE.h"
#include "Menu.h"

void swapIDE(ide *a, ide *b);
void sortMenu(int len, ide array[len]);
void sortArray(int len, ide array[len], short int field, short int order);

#endif
