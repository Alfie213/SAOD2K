#pragma once
#include <iostream>
using namespace std;

class Test
{
public:
	static int nCount;
	Test()
	{
		nCount++;
		cout << "Created Test" << endl;
		cout << "Test nCount = " << nCount << endl;
	}

	Test(int n)
	{
		nCount++;
		cout << "Created PARAMETRIZED Test" << endl;
		cout << "Test nCount = " << nCount << endl;
	}

	Test(const Test& obj)
	{
		nCount++;
		cout << "Created Test" << endl;
		cout << "Test nCount = " << nCount << endl;
	}

	~Test()
	{
		nCount--;
		cout << "Destroyed Test" << endl;
		cout << "Test nCount = " << nCount << endl;
	}
};

