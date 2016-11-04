/*
 * Stack.h
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#ifndef STACK_H_
#define STACK_H_

#include "Car.h"
using namespace std;

class Stack
{
	private:
		Car* StackHead;
		int size;

	public:
		Stack() : size(0), StackHead(NULL) {}
		~Stack(){}



		//Part 2--------------------------------------------------------------
		/**
		 * Adds the current car to the stack.  After this operation, there should be no current car.
		 * Does nothing if there is no curarent car or if the stack is already full.
		 *
		 * @return true if the car is successfully added to the stack; false otherwise
		 */
		bool addToStack(Car* &Current);

		/**
		 * Removes the first car in the stack and makes it the current car.
		 * Does nothing if there is already a current car or if the stack already empty.
		 *
		 * @return true if the car is successfully removed from the stack; false otherwise
		 */
		bool removeFromStack(Car* &Current);

		/**
		 * Returns the ID of the first car in the stack.
		 *
		 * @return the ID of the first car in the stack; -1 if the stack is empty
		 */
		int showTopOfStack();

		/**
		 * Returns the number of cars in the stack.
		 *
		 * @return the number of cars in the stack
		 */
		int showSizeOfStack();


		bool find(int car);

};





#endif /* STACK_H_ */
