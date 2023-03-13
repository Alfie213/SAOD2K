#pragma once
#include <iostream>
//#include "Test.h"
using namespace std;

template <typename T>
class AggregateT
{
public:
	T m_objTest;

	AggregateT() : m_objTest(9)
	{
		cout << "Created AggregateT" << endl;
	}

	~AggregateT()
	{
		cout << "Destroyed AggregateT" << endl;
	}
};