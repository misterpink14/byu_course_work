#ifndef PARAMETER_CPP_
#define PARAMETER_CPP_


#include "Token.h"



class Parameter
{
public:
	Kind K;
	string Value;
	
	Parameter() {}

	string toStr()
	{
		if (K == Kind::STRING)
		{
			return "'" + Value + "'";
		}
		return Value;
	}
};

#endif
