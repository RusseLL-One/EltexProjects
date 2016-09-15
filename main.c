#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "generator.h"
#include "receiver.h"
#include "mutex.h"

int main(int argc, char *argv[]) {
    struct threadStruct sharedStr; // Создание структуры, содержащую мьютексы
    pthread_mutex_init(&sharedStr.mutex, NULL);
    pthread_cond_init(&sharedStr.recvCond, NULL);
    pthread_cond_init(&sharedStr.sndrCond, NULL);
    sharedStr.count = 0;


    pthread_create(&sharedStr.sndrThreadID[0], NULL, GenerateMessage, &sharedStr);
    pthread_create(&sharedStr.recvThreadID[0], NULL, ReceiveMessage, &sharedStr);
    pthread_create(&sharedStr.recvThreadID[1], NULL, ReceiveMessage, &sharedStr);
    //pthread_create(&sharedStr.recvThreadID[2], NULL, ReceiveMessage, &sharedStr);

    pause();
    return 0;
}