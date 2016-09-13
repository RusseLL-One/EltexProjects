//
// Created by russell on 12.09.16.
//
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#include "receiver.h"
#include "mutex.h"
#include "queue.h"

void *ReceiveMessage(void *shStruct) {
    srand(time(NULL) + pthread_self());
    sleep(rand() % 10);
    struct threadStruct *sharedStr = (struct threadStruct *) shStruct;
    int counter = 0;
    char *message;

    for (; ;) {
        if ((message = get(sharedStr)) == NULL) {
            fprintf(stderr, "get() failed\n");
            pthread_cond_wait(&sharedStr->cond, &sharedStr->mutex);
            continue;
        }
        counter++;
        printf("Message received! ID=%d Counter=%d %s\n", (int) pthread_self(), counter, message);

        free(message);
        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}