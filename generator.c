//
// Created by russell on 12.09.16.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "generator.h"
#include "mutex.h"
#include "queue.h"

void *GenerateMessage(void *shStruct) {
    //Генерируем случайное сообщение
    struct threadStruct *sharedStr = (struct threadStruct *) shStruct;
    int length;
    char message[MAXSTRINGSIZE];
    srand(time(NULL) + pthread_self());
    for (; ;) {
        length = (rand() % MAXSTRINGSIZE) + 1;
        for (int i = 0; i < length; i++) {
            message[i] = 65 + (rand() % 57);
        }
        message[length] = '\0';

        if (put(sharedStr, message) < 0) {
            fprintf(stderr, "put() failed\n");
            sleep(1);
            continue;
        }
        if (sharedStr->count == 1) {
            pthread_cond_signal(&sharedStr->cond);
        }
        printf("Message sent\n");
        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}