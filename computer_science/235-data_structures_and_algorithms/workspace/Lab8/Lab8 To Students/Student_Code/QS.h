/*
 * QS.h
 *
 *  Created on: Jun 11, 2014
 *      Author: misterpink14
 */

#ifndef QS_H_
#define QS_H_

#include "QSInterface.h"
#include <sstream>


class QS : public QSInterface
{
	private:
		int* q;
		int size;
		int pos;


		void LeftShift(int& start, int& stop)
		{
			if(start == stop)
			{
				return;
			}
			q[start] = q[start+1];

			LeftShift(++start, stop);
		}

		void RightShift(int& start, int& stop)
		{
			if(start == stop)
			{
				return;
			}
			q[start] = q[start-1];

			RightShift(--start, stop);
		}


		void doit(int& i, int& r, int& p)
		{
			int temp;
			if (i < p)
			{
				if(q[i] > q[p])
				{
					temp = q[i];
					int start = i;
					int stop = p;
					LeftShift(start, stop);
					q[p] = temp;
					p--;
					doit(i, r, p);
					return;
				}
				else
				{
					i++;
					doit(i, r, p);
					return;
				}
			}
			else if (r > p)
			{
				if(q[r] < q[p])
				{
					temp = q[r];
					int start = r;
					int stop = p;
					RightShift(start, stop);
					q[p] = temp;
					p++;
					i++;
					doit(i, r, p);
					return;
				}
				else
				{
					r--;
					doit(i, r, p);
					return;
				}
			}
			else
			{
				return;
			}
		}



		void sortAll(int l, int r)
		{

			int p = medianOfThree(l, r);
			if (r == p || l == p || r == l)
			{
				return;
			}
			p = partition(l, r, p);
			// go left
			sortAll(l, p);

			// go right
			sortAll(p, r);
		}


	public:
		QS()
		{
			q = NULL;
			size = 0;
			pos = 0;
		}
		virtual ~QS(){clear();}

		/*
		 * sortAll()
		 *
		 * Sorts elements of the array.  After this method is called, every
		 * element in the array is less than or equal to the following element.
		 *
		 * Does nothing if the array is empty.
		 */
		void sortAll()
		{
			int l = 0;
			int r = (size-1);

			sortAll(l, r);


			return;
		}

		/*
		 * medianOfThree()
		 *
		 * Performs median-of-three pivot selection from among the values in
		 * the array between the two given indices. Median-of-three pivot
		 * selection will sort the first, middle, and last elements in a given
		 * array with respect to each other. After this method is called,
		 * data[first] <= data[middle] <= data[last], where middle =
		 * (first + last)/2.
		 *
		 * Returns -1 if the array is empty, if either of the given integers
		 * is out of bounds, or if the first integer is not less than the second
		 * integer.
		 *
		 * @param left
		 * 		the left boundary for the subarray from which to find a pivot
		 * @param right
		 * 		the right boundary for the subarray from which to find a pivot
		 * @return
		 *		the index of the pivot; -1 if provided with invalid input
		 */
		int medianOfThree(int left, int right)
		{
			if (q == NULL || left < 0 || left > right || right > (size-1) || right == left)
			{
				return -1;
			}
			else
			{
				int center = (left+right)/2;
				int temp;

				if(q[left] > q[right])
				{
					temp = q[left];
					q[left] = q[right];
					q[right] = temp;
				}
				if(q[left] > q[center])
				{
					temp = q[left];
					q[left] = q[center];
					q[center] = temp;
				}
				if(q[center] > q[right])
				{
					temp = q[center];
					q[center] = q[right];
					q[right] = temp;
				}

				return center;
			}
		}

		/*
		 * Partitions a subarray around a pivot value selected according to
		 * median-of-three pivot selection.
		 *
		 * The values which are smaller than the pivot should be placed to the left
		 * of the pivot; the values which are larger than the pivot should be placed
		 * to the right of the pivot.
		 *
		 * Does nothing and returns -1 if the array is null, if either of the
		 * given integers is out of bounds, or if the first integer is not less than
		 * the second integer, or if the pivot is not between the two boundaries.
		 *
		 * @param left
		 * 		the left boundary for the subarray to partition
		 * @param right
		 * 		the right boundary for the subarray to partition
		 * @param pivotIndex
		 * 		the index of the pivot in the subarray
		 * @return
		 *		the pivot's ending index after the partition completes; -1 if
		 * 		provided with bad input
		 */
		int partition(int left, int right, int pivotIndex)
		{
			if(q == NULL || left < 0 || right > (size-1) || left >= right || pivotIndex > right || pivotIndex < left)
			{
				return -1;
			}

			doit(left, right, pivotIndex);

			return pivotIndex;
		}

		/*
		 * Gets the array of values and puts them into a string. For example: if my array
		 * looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
		 * with no trailing comma.
		 *
		 * Does nothing and returns null, if the array is null or empty.
		 *
		 * @return
		 *		the string representation of the current array
		 */
		string getArray()
		{
			stringstream out;
			for(unsigned i = 0; i < pos; i++)
			{
				out << q[i];
				if ( i < (pos-1))
				{
					out << ",";
				}
			}
			return out.str();
		}

		/*
		 * Gets the current size of the current array.
		 *
		 * @return
		 * 		the current size
		 */
		int getSize()
		{
			return size;
		}

		/*
		 * Adds the given value to the array.
		 */
		void addToArray(int value)
		{
			if(size == 0 || size == pos)
			{
				return;
			}
			q[pos] = value;
			pos++;
		}

		/*
		 * Creates an array of with the given size.
		 *
		 * Returns false if the given value is non-positive, true otherwise.
		 *
		 * @param
		 *		size of array
		 * @return
		 *		true if the array was created, false otherwise
		 */
		bool createArray(int size)
		{
			if(size < 1)
			{
				return false;
			}
			q = new int[size];
			this->size = size;
			return true;
		}

		/*
		 * Clears the array.
		 */
		void clear()
		{
			if (size == 0)
				return;

			delete[] q;
			q = NULL;
			size = 0;
			pos = 0;
		}
};


#endif /* QS_H_ */
