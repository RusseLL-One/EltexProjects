#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "generator.h"
#include "receiver.h"
#include "mutex.h"

int main(int argc, char *argv[]) {
    struct threadStruct sharedStr; // Создание структуры, содержащую мьютексы
    pthread_mutex_init(&sharedStr.mutex, NULL);
    pthread_cond_init(&sharedStr.cond, NULL);
    sharedStr.count = 0;
    pthread_create(&sharedStr.SndrThreadID[0], NULL, GenerateMessage, &sharedStr);
    pthread_create(&sharedStr.RecvThreadID[0], NULL, ReceiveMessage, &sharedStr);
    pthread_create(&sharedStr.RecvThreadID[1], NULL, ReceiveMessage, &sharedStr);
    pthread_create(&sharedStr.RecvThreadID[2], NULL, ReceiveMessage, &sharedStr);

    sleep(100);
    return 0;
}