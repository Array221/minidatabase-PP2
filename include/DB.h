#ifndef DB_H
#define DB_H

#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <windows.h>
#include "IDE.h"

typedef struct {
    FILE *pointer;
    char name[50];
    short int isOpen;
} dbFile;

int checkDBName(char fileName[]);
void createDB(dbFile *db);
void deleteDB(dbFile *db);
void openDB(dbFile *db);
void closeDB(dbFile *db);
int loadDB(dbFile *db, ide **array);
void saveDB(dbFile *db, int len, ide *array);

#endif
