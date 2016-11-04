/*
 * Tool.h
 *
 *  Created on: Jun 10, 2014
 *      Author: misterpink14
 */

#ifndef TOOL_H_
#define TOOL_H_

#include <string>
#include <vector>
//template<class ItemType>

void printVector(std::vector<std::string> out)
{
	for(unsigned i = 0; i < out.size(); i++)
	{
		std::cout << i << ": " << out[i] << std::endl;
	}
}



#endif /* TOOL_H_ */
