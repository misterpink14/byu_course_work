/*
 * Deque.h
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#ifndef DEQUE_H_
#define DEQUE_H_

#include "Car.h"


class Deque
{
	private:
		int size;
		Car* DequeHead;
		Car* DequeTail;

	public:
		Deque() : size(0), DequeHead(NULL), DequeTail(NULL) {}
		~Deque(){}


		//Part 4--------------------------------------------------------------
		/**
		 * Adds the current car to the deque on the left side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		bool addToDequeLeft(Car* &Current);

		/**
		 * Adds the current car to the deque on the right side.  After this operation, there should be no current car.
		 * Does nothing if there is no current car or if the deque is already full.
		 *
		 * @return true if the car is successfully added to the deque; false otherwise
		 */
		bool addToDequeRight(Car* &Current);

		/**
		 * Removes the leftmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		bool removeFromDequeLeft(Car* &Current);

		/**
		 * Removes the rightmost car in the deque and makes it the current car.
		 * Does nothing if there is already a current car or if the deque already empty.
		 *
		 * @return true if the car is successfully removed from the deque; false otherwise
		 */
		bool removeFromDequeRight(Car* &Current);

		/**
		 * Returns the ID of the leftmost car in the deque.
		 *
		 * @return the ID of the leftmost car in the deque; -1 if the deque is empty
		 */
		int showTopOfDequeLeft();

		/**
		 * Returns the ID of the rightmost car in the deque.
		 *
		 * @return the ID of the rightmost car in the deque; -1 if the deque is empty
		 */
		int showTopOfDequeRight();

		/**
		 * Returns the number of cars in the deque.
		 *
		 * @return the number of cars in the deque
		 */
		int showSizeOfDeque();

		bool find(int car);

};


#endif /* DEQUE_H_ */
