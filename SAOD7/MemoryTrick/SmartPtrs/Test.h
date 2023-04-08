#pragma once
#include <iostream>
using namespace std;
class Test
{
public:
	int Val;

	Test()
	{
		Val = 0;
		cout << "Test created" << endl;
	}

	~Test()
	{
		cout << "Test destroyed" << endl;
	}
};

