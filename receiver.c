//
// Created by russell on 12.09.16.
//

#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "receiver.h"
#include "mutex.h"

#define MAXSTRINGSIZE 250

struct mesStruct {
    long mesType;
    char message[MAXSTRINGSIZE];
};

void *ReceiveMessage(void *shStruct) {
    // key_t key = 21;
    struct threadStruct sharedStruct = *(struct threadStruct *) shStruct;
    int counter = 0;
    struct mesStruct mesBuf;
    int msqID = sharedStruct.msqID;
    /*if ((msqID = msgget(key, 0666)) < 0) {
        perror("msgget");
        return;
    }*/
    for (; ;) {
        //pthread_mutex_lock(&sharedStruct.mutex);
        if (msgrcv(msqID, &mesBuf, MAXSTRINGSIZE, 1, 0) < 0) {
            perror("msgrcv");
            //    pthread_mutex_unlock(&sharedStruct.mutex);
            return -1;
        }
        // pthread_mutex_unlock(&sharedStruct.mutex);
        counter++;
        printf("Message received! Counter=%d\n", counter);

        sleep(1);
        /*srand(time(NULL));
        sleep((rand() % MAXSLEEPTIME) + 1);*/
    }
}