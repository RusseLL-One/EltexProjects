//
// Created by russell on 12.09.16.
//

#ifndef FIRSTTASK_MUTEX_H
#define FIRSTTASK_MUTEX_H

#define QUEUE_SIZE 15

typedef struct threadStruct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_t SndrThreadID[15];
    pthread_t RecvThreadID[15];
    char *queue[QUEUE_SIZE];
    int count;
} threadStr;

#endif //FIRSTTASK_MUTEX_H
