#pragma once
#include <iostream>
#include "Test.h"
using namespace std;

class Child:public Test
{
public:
	Child()
	{
		nCount++;
		cout << "Created Child" << endl;
		cout << "Child nCount = " << nCount << endl;
	}

	Child(int n):Test(n)
	{
		nCount++;
		cout << "Created PARAMETRIZED Child" << endl;
		cout << "Child nCount = " << nCount << endl;
	}

	~Child()
	{
		nCount--;
		cout << "Destroyed Child" << endl;
		cout << "Child nCount = " << nCount << endl;
	}
};