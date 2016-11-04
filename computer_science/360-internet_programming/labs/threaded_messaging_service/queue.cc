#include "queue.h"


MyQueue::MyQueue()
{
	client_list = queue<int>();
	sem_init(&lock_, 0, 1);
	sem_init(&size_, 0, 0);
	sem_init(&avail_, 0, 10);
}

void 
MyQueue::push(int i)
{
	sem_wait(&avail_);
	sem_wait(&lock_);
	client_list.push(i);
	sem_post(&lock_);
	sem_post(&size_);
}

int 
MyQueue::pop()
{
	sem_wait(&size_);
	sem_wait(&lock_);
	int i = client_list.front();
	client_list.pop();
	sem_post(&lock_);
	sem_post(&avail_);
	return i;
}
