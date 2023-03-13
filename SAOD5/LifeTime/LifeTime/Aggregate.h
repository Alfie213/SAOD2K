#pragma once
#include <iostream>
#include "Test.h"
using namespace std;

class Aggregate
{
public:
	Test m_objTest;

	Aggregate()
	{
		cout << "Created Aggregate" << endl;
	}

	~Aggregate()
	{
		cout << "Destroyed Aggregate" << endl;
	}
};