//
// Created by russell on 12.09.16.
//
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "generator.h"
#include "mutex.h"

#define MAXSTRINGSIZE 250
#define MAXSLEEPTIME 5

struct mesStruct {
    long mesType;
    char message[MAXSTRINGSIZE];
};

void *GenerateMessage(void *shStruct) {
    //Генерируем случайное сообщение
    struct threadStruct sharedStruct = *(struct threadStruct *) shStruct;
    int msqID = sharedStruct.msqID;
    int length;
    struct mesStruct mesBuf;
    mesBuf.mesType = 1;
    for (; ;) {
        srand(time(NULL));
        length = (rand() % MAXSTRINGSIZE) + 1;
        for (int i = 0; i < length; i++) {
            mesBuf.message[i] = 65 + (rand() % 57);
        }
        mesBuf.message[length] = '\0';

        //pthread_mutex_lock(&sharedStruct.mutex);
        if (msgsnd(msqID, &mesBuf, strlen(mesBuf.message) + 1, IPC_NOWAIT) < 0) {
            printf("%d, %d, %s, %d\n", msqID, mesBuf.message, mesBuf.message, strlen(mesBuf.message) + 1);
            perror("msgsnd");
            //    pthread_mutex_unlock(&sharedStruct.mutex);
            return -1;
        }
        //pthread_mutex_unlock(&sharedStruct.mutex);
        srand(time(NULL));
        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}