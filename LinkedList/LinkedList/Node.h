#pragma once
using namespace std;

template <typename T>
class Node
{
private:
	T value;
	Node<T>* next;
public:
	Node(T value) // Default: T value = nullptr doesn't work.
	{
		this->value = value;
		next = nullptr;
	}

	inline T GetValue()
	{
		return value;
	}

	inline T* GetValueAds()
	{
		return &value;
	}

	inline void SetValue(T value)
	{
		this->value = value;
	}

	inline Node<T>* GetNext()
	{
		return next;
	}

	inline void SetNext(Node<T>* node)
	{
		next = node;
	}

	~Node()
	{
		//cout << "Disabled " << value << endl;
	}
};

