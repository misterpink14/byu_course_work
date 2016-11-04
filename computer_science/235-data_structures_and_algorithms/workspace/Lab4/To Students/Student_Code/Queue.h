/*
 * Queue.h
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "Car.h"

class Queue
{
	private:
		int size;
		Car* QueueHead;
		Car* QueueTail;


	public:
		Queue() : size(0), QueueHead(NULL), QueueTail(NULL) {}
		~Queue(){}

		//Part 3--------------------------------------------------------------
		/**
		 * Adds the current car to the queue.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the queue is already full.
		 *
		 * @return true if the car is successfully added to the queue; false otherwise
		 */
		bool addToQueue(Car* &Current);

		/**
		 * Removes the first car in the queue and makes it the current car.
		 * Does nothing if there is already a current car or if the queue already empty.
		 *
		 * @return true if the car is successfully removed from the queue; false otherwise
		 */
		bool removeFromQueue(Car* &Current);

		/**
		 * Returns the ID of the first car in the queue.
		 *
		 * @return the ID of the first car in the queue; -1 if the queue is empty
		 */
		int showTopOfQueue();

		/**
		 * Returns the number of cars in the queue.
		 *
		 * @return the number of cars in the queue
		 */
		int showSizeOfQueue();

		bool find(int car);


};



#endif /* QUEUE_H_ */
