//
// Created by russell on 13.09.16.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "mutex.h"
#include "queue.h"

int put(threadStr *sharedStr, char *elem) {
    pthread_mutex_lock(&sharedStr->mutex);
    if (sharedStr->count >= QUEUE_SIZE) {
        pthread_mutex_unlock(&sharedStr->mutex);
        return -1;
    }
    sharedStr->queue[sharedStr->count] = calloc(strlen(elem), sizeof(char));
    strcpy(sharedStr->queue[sharedStr->count], elem);
    sharedStr->count++;
    pthread_mutex_unlock(&sharedStr->mutex);
    return 0;
}

char *get(threadStr *sharedStr) {
    pthread_mutex_lock(&sharedStr->mutex);
    if (sharedStr->count <= 0) {
        pthread_mutex_unlock(&sharedStr->mutex);
        return NULL;
    }
    char *temp;
    temp = calloc(strlen(sharedStr->queue[0]), sizeof(char));
    strcpy(temp, sharedStr->queue[0]);
    sharedStr->count--;
    for (int i = 0; i < sharedStr->count - 1; i++) {
        strcpy(sharedStr->queue[i], sharedStr->queue[i + 1]);
    }
    memset(sharedStr->queue[sharedStr->count], 0, sizeof(char));
    for (int i = 0; i < sharedStr->count; i++) printf("%d: %s\n", i + 1, sharedStr->queue[i]);
    pthread_mutex_unlock(&sharedStr->mutex);
    return temp;
}