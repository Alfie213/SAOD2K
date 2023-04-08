#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> someVec;
	for (size_t i = 0; i < 1000; i++)
	{
		if (someVec.size() == someVec.capacity())
		{
			someVec.push_back(1);
			cout << someVec.size() << " / " << someVec.capacity() << endl;
			continue;
		}
		someVec.push_back(1);
	}
}