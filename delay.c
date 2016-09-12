//
// Created by russell on 12.09.16.
//
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAXSLEEPTIME 10

void Delay() {
    srand(time(NULL));
    sleep((rand() % MAXSLEEPTIME) + 1);
}