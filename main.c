#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "generator.h"
#include "receiver.h"
#include "queue.h"

int main(int argc, char *argv[]) {
    threadStr sharedStr;
    pthread_mutex_init(&sharedStr.mutex, NULL);
    pthread_cond_init(&sharedStr.recvCond, NULL);
    pthread_cond_init(&sharedStr.sndrCond, NULL);
    sharedStr.count = 0;
    pthread_t threadID;

    pthread_create(&threadID, NULL, GenerateMessage, &sharedStr);
    pthread_create(&threadID, NULL, ReceiveMessage, &sharedStr);
    pthread_create(&threadID, NULL, ReceiveMessage, &sharedStr);
    //pthread_create(&threadID, NULL, ReceiveMessage, &sharedStr);

    pause();
    return 0;
}