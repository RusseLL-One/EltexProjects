#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "generator.h"
#include "receiver.h"

int main(int argc, char *argv[]) {

    pthread_t threadID;

    pthread_create(&threadID, NULL, GenerateMessage, NULL);
    pthread_create(&threadID, NULL, ReceiveMessage, NULL);
    pthread_create(&threadID, NULL, ReceiveMessage, NULL);
    //pthread_create(&sharedStr.recvThreadID[2], NULL, ReceiveMessage, &sharedStr);

    pause();
    return 0;
}