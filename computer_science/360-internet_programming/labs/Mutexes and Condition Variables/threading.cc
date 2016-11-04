// Includes
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
			// pthread_mutex_lock(&mutex);
		}

		int 
		getV()
		{
			// pthread_mutex_unlock(&mutex);
			return v;
		}

		void
		initMutex()
		{
			pthread_mutex_init(&mutex, NULL);
			pthread_cond_init(&cond, NULL);
		}


		pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
		pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	private:

		long v;
};

int
main (int argc, char ** argv)
{
	pthread_t thA, thB;

	Example c;
	c.initMutex();
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

	// for (int i = 0; i < 10; i++)
	{

		int r = random() % 100 + 1;
		cout << "Storing " << r << endl;

		pthread_mutex_lock(&c->mutex); 
		c->setV(r);
		
		pthread_mutex_unlock(&c->mutex); 
		pthread_cond_signal(&c->cond);
	}
}

void *
reading(void *vptr)
{
	int r = 100;
	// usleep(r);
	int val = 0;
	Example* c;

	c = (Example*) vptr;
	int prev = c->getV();

	// for (int i = 0; i < 10; i++)
	{
		pthread_mutex_lock(&c->mutex);
		while (prev == c->getV())
		{
			pthread_cond_wait(&c->cond, &c->mutex); 
		}  
		prev = c->getV();
		pthread_mutex_unlock(&c->mutex);
		// usleep(r);
		cout << "Reading " << c->getV() << endl;

	}
}

