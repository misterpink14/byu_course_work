#pragma once
#include "BankInterface.h"
#include "Bank.h"

class Factory
{
public:
	Factory(void);

	BankInterface* createBank();

	~Factory(void);
};

