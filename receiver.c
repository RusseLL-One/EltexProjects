//
// Created by russell on 12.09.16.
//
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "receiver.h"
#include "queue.h"

void *ReceiveMessage(void *thrStr) {
    srand(time(NULL) + pthread_self());
    sleep(rand() % 3);
    int counter = 0;
    char *message;
    threadStr *sharedStr = (threadStr *) thrStr;
    for (; ;) {
        if ((message = get(sharedStr)) == NULL) {
            fprintf(stderr, "get() failed\n");
            sleep(1);
            continue;
        }
        counter++;

        printf("Message received! ID=%d Counter=%d %s\n", abs(pthread_self()) % 10, counter, message);
        free(message);
        sleep((rand() % MAXSLEEPTIME) + 1);
    }
}