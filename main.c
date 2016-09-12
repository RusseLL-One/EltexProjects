#include <stdio.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>
#include "generator.h"
#include "receiver.h"
#include "mutex.h"

int main(int argc, char *argv[]) {
    struct threadStruct sharedStruct; // Создание структуры, содержащую мьютексы
    pthread_mutex_init(&sharedStruct.mutex, NULL);

    pthread_t threadID;
    int msqID; //ID очереди сообщений
    int msgflg = IPC_CREAT | 0666; //Флаги очереди сообщений
    key_t key = 21; //Ключ очереди сообщений

    if ((msqID = msgget(key, msgflg)) < 0) { //Создание очереди сообщений
        perror("msgget");
        return -1;
    }
    printf("msgget: msgget succeeded: msqid = %d\n", msqID);
    sharedStruct.msqID = msqID;

    pthread_create(&threadID, NULL, GenerateMessage, &sharedStruct);
    pthread_create(&threadID, NULL, ReceiveMessage, &sharedStruct);
    pthread_create(&threadID, NULL, ReceiveMessage, &sharedStruct);
    pthread_create(&threadID, NULL, ReceiveMessage, &sharedStruct);

    sleep(50);
    msgctl(msqID, IPC_RMID, NULL);
    return 0;
}