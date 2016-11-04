#pragma once

#include <queue>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class MyQueue {
public:
    MyQueue();
    // ~MyQueue();
    int pop();
    void push(int);
    
private:
    queue<int> client_list;

    sem_t lock_;
    sem_t size_;
    sem_t avail_;
};
