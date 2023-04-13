#pragma once
#include <exception>
#include <string.h>
#include <stdexcept>
using namespace std;

class PF
{
	int* pv;
	int n;
	bool initialized;
	int counter;
public:
	PF()
	{
		pv = new int[1] {0};
		n = 1;
		initialized = false;
	}

	~PF()
	{
		delete[] pv;
	}

	void Init(const char* s)
	{
		if (initialized) return;
		counter = 0;
		n = strlen(s);
		delete[] pv;
		pv = new int[n];
		initialized = true;
		
		pv[0] = 0;
		for (size_t i = 1; i < n; ++i)
		{
			int j = pv[i - 1];
			while (j > 0 && s[i] != s[j])
			{
				j = pv[j - 1];
				counter++;
			}
			if (s[i] == s[j]) ++j;
			pv[i] = j;
			counter++;
		}

		/*int k = 0;
		pv[0] = 0;
		for (size_t i = 1; i < n; i++)
		{
			if (s[i + 1] == s[k])
			{
				pv[i + 1] = k + 1;
			}
			else
			{
				if (k == 0)
				{
					pv[i + 1] = 0;
				}
				else
				{
					k = pv[k - 1];
				}
			}
		}*/
	}

	inline int CmpCount()
	{
		return counter;
	}

	operator int() const
	{
		return n;
	}

	int operator [] (int i) const
	{
		if (i < 0 or i >= n) throw out_of_range("Index out of range");
		return pv[i];
	}
};

