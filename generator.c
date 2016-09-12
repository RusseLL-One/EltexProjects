//
// Created by russell on 12.09.16.
//
#include <stdlib.h>
#include <time.h>
#include "generator.h"

#define MAXSTRINGSIZE 250

struct mesStruct {
    long mesType;
    char message[MAXSTRINGSIZE];
};

void GenerateMessage() {
    //Генерируем случайное сообщение
    struct mesStruct mesBuf;
    int length;
    char *message;
    srand(time(NULL));
    length = (rand() % MAXSTRINGSIZE) + 1;
    message = calloc(length, sizeof(char));
    for (int i = 0; i < length; i++) {
        message[i] = 65 + (rand() % 57);
    }
    message[length] = '\0';
}