// Includes
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>

using namespace std;

// Void pointer
void *storing(void *);
void *reading(void *);


class Example
{
	public:

		void
		setV(int val)
		{
			v = val;
		}

		int 
		getV()
		{
			return v;
		}

		void
		initSem()
		{
			sem_init(&sem1,0,1);
			sem_init(&sem2,0,0);
		}

		sem_t sem1;
		sem_t sem2;

	private:

		long v;
};

int
main (int argc, char ** argv)
{
	pthread_t thA, thB;

	Example c;
	c.initSem();
	c.setV(0);
	srandom(time(0));


	pthread_create(&thA, NULL, &storing, &c);
	pthread_create(&thB, NULL, &reading, &c);
	
	pthread_join(thA, NULL);
	pthread_join(thB, NULL);

	exit(0);
}

void *
storing(void *vptr)
{
	long val = 0;
	Example* c;

	c = (Example*) vptr;

	{
		sem_wait(&c->sem1);
		int r = random() % 100 + 1;
		cout << "Storing " << r << endl;
		c->setV(r);
		sem_post(&c->sem2);
	}
}

void *
reading(void *vptr)
{
	int r = 100;
	usleep(r);
	int val = 0;
	Example* c;

	c = (Example*) vptr;
	int prev = c->getV();

	{
		sem_wait(&c->sem2);
		prev = c->getV();
		cout << "Reading " << c->getV() << endl;
		sem_post(&c->sem1);

	}
}

