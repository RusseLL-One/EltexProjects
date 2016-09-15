//
// Created by russell on 13.09.16.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    pthread_cond_t recvCond;
    pthread_cond_t sndrCond;
    pthread_t sndrThreadID[15];
    pthread_t recvThreadID[15];
    char queue[QUEUE_SIZE][MAXSTRINGSIZE];
    int count;
} sharedStr = {
        .mutex=PTHREAD_MUTEX_INITIALIZER,
        .recvCond=PTHREAD_COND_INITIALIZER,
        .sndrCond=PTHREAD_COND_INITIALIZER,
        .count=0
};

int put(char *elem) {

    pthread_mutex_lock(&sharedStr.mutex);
    if (sharedStr.count >= QUEUE_SIZE) {
        printf("Generator waiting...\n");
        pthread_cond_wait(&sharedStr.sndrCond, &sharedStr.mutex);
        if (sharedStr.count <= 0) {
            pthread_mutex_unlock(&sharedStr.mutex);
            return -1;
        }
        printf("Generator is good to go\n");
    }
    sharedStr.count++;
    strncpy(sharedStr.queue[sharedStr.count - 1], elem, strlen(elem));
    printf("Message sent! %s\n", elem);
    for (int i = 0; i < sharedStr.count; i++) printf("%d: %s\n", i + 1, sharedStr.queue[i]);
    pthread_mutex_unlock(&sharedStr.mutex);
    pthread_cond_signal(&sharedStr.recvCond);
    return 0;
}

char *get() {
    pthread_mutex_lock(&sharedStr.mutex);
    if (sharedStr.count <= 0) {
        printf("Receiver waiting...\n");
        pthread_cond_wait(&sharedStr.recvCond, &sharedStr.mutex);
        if (sharedStr.count <= 0) {
            pthread_mutex_unlock(&sharedStr.mutex);
            return NULL;
        }
        printf("Receiver is good to go\n");
    }

    char *temp;
    temp = calloc(strlen(sharedStr.queue[0]), sizeof(char));
    strncpy(temp, sharedStr.queue[0], strlen(sharedStr.queue[0]));
    for (int i = 0; i < sharedStr.count - 1; i++) {
        strncpy(sharedStr.queue[i], sharedStr.queue[i + 1], strlen(sharedStr.queue[i + 1]));
    }
    memset(sharedStr.queue[sharedStr.count - 1], 0, strlen(sharedStr.queue[sharedStr.count - 1]));
    sharedStr.count--;
    pthread_mutex_unlock(&sharedStr.mutex);
    pthread_cond_signal(&sharedStr.sndrCond);
    return temp;
}