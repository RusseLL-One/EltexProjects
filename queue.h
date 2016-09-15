//
// Created by russell on 13.09.16.
//

#ifndef FIRSTTASK_QUEUE_H
#define FIRSTTASK_QUEUE_H

#define QUEUE_SIZE 15
#define MAXSTRINGSIZE 70

typedef struct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    pthread_cond_t recvCond;
    pthread_cond_t sndrCond;
    char queue[QUEUE_SIZE][MAXSTRINGSIZE];
    int count;
} threadStr;

int put(threadStr *sharedStr, char *elem);

char *get(threadStr *sharedStr);

#endif //FIRSTTASK_QUEUE_H
