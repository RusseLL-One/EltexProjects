//
// Created by russell on 12.09.16.
//

#ifndef FIRSTTASK_MUTEX_H
#define FIRSTTASK_MUTEX_H

#define QUEUE_SIZE 15
#define MAXSTRINGSIZE 70

typedef struct threadStruct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    pthread_cond_t recvCond;
    pthread_cond_t sndrCond;
    pthread_t sndrThreadID[15];
    pthread_t recvThreadID[15];
    char queue[QUEUE_SIZE][MAXSTRINGSIZE];
    int count;
} threadStr;

#endif //FIRSTTASK_MUTEX_H
