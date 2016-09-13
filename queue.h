//
// Created by russell on 13.09.16.
//

#ifndef FIRSTTASK_QUEUE_H
#define FIRSTTASK_QUEUE_H

#define QUEUE_SIZE 15

int put(threadStr *sharedStr, char *elem);

char *get(threadStr *sharedStr);

#endif //FIRSTTASK_QUEUE_H
