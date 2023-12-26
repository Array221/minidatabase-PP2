#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "DB.h"
#include "Menu.h"
#include "Sort.h"

void overview(dbFile *db);
void addRecord(int *len, ide **array);
void deleteRecord(int *len, ide **array, int delInd);
void modifyRecord(ide *record);

#endif
