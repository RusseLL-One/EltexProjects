//
// Created by russell on 12.09.16.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "generator.h"
#include "queue.h"

void *GenerateMessage(void *thrStr) {
    int length;
    char message[MAXSTRINGSIZE];
    threadStr *sharedStr = (threadStr *) thrStr;
    for (; ;) {
        srand(time(NULL) + pthread_self());
        length = (rand() % MAXSTRINGSIZE) + 1;
        for (int i = 0; i < length; i++) {
            message[i] = 65 + (rand() % 57);
        }
        /*int letter = rand() % 57;
        for (int i = 0; i < length; i++) {
            message[i] = 65 + letter;
        }*/
        message[length] = '\0';

        if (put(sharedStr, message) < 0) {
            fprintf(stderr, "put() failed\n");
            sleep(1);
            continue;
        }

        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}