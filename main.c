#include <stdio.h>

struct { // Mutex для синхронизации очереди
    pthread_mutex_t mutex;
    int msqID;
} sharedStruct = {
        PTHREAD_MUTEX_INITIALIZER
};

int main(int argc, char *argv[]) {

    return 0;
}