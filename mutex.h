//
// Created by russell on 12.09.16.
//

#ifndef FIRSTTASK_MUTEX_H
#define FIRSTTASK_MUTEX_H

struct threadStruct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    int msqID;
};

#endif //FIRSTTASK_MUTEX_H
