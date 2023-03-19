#pragma once
#include "Node.h"

using namespace std;

template <typename T>
class LinkedList
{
private:
	Node<T>* head;
	size_t count;
public:
	LinkedList();
	~LinkedList();

	void print();

	void push_back(T value);
	void push_front(T value);
	void insert(size_t idx, T value);
	void pop_back();
	void pop_front();
	void remove_at(size_t index);
	T& operator[](const size_t index);
	T const& operator[](const size_t index) const;
	size_t size() const;
	bool empty() const;
	void clear();
	T front() const;
	T back() const;
};

template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	count = 0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
	cout << "List was deleted" << endl;
}

template <typename T>
void LinkedList<T>::print()
{
	if (head == nullptr)
	{
		cout << "List is empty!" << endl;
		return;
	}
	//cout << "Hi. I'm List! Values: ";
	if (count == 1)
	{
		cout << head->GetValue() << endl;
		return;
	}
	Node<T>* tmp = head;
	do
	{
		cout << tmp->GetValue() << " -> ";
		tmp = tmp->GetNext();
	} while (tmp->GetNext() != head);
	cout << tmp->GetValue();
	cout << endl;
	//cout << endl << "End of print()" << endl;
}

template <typename T>
void LinkedList<T>::push_back(T value)
{
	if (head == nullptr)
	{
		push_front(value);
		return;
	}
	else
	{
		Node<T>* tmp = head;
		while (tmp->GetNext() != head)
		{
			tmp = tmp->GetNext();
		}
		tmp->SetNext(new Node<T>(value));
		tmp->GetNext()->SetNext(head);
	}
	count++;
}

template <typename T>
void LinkedList<T>::push_front(T value)
{
	if (head == nullptr)
	{
		head = new Node<T>(value);
		head->SetNext(head);
	}
	else
	{
		Node<T>* oldHead = head;
		head = new Node<T>(value);
		head->SetNext(oldHead);
		Node<T>* tmp = oldHead;
		while (tmp->GetNext() != oldHead)
		{
			tmp = tmp->GetNext();
		}
		tmp->SetNext(head);
	}
	count++;
}

template <typename T>
void LinkedList<T>::insert(size_t idx, T value)
{
	if (idx > count)
	{
		cout << "Index not found" << endl;
		return;
	}
	if (idx == 0)
	{
		push_front(value);
		return;
	}
	Node<T>* tmp = head;
	for (size_t i = 0; i < idx - 1; i++)
	{
		tmp = tmp->GetNext();
	}
	Node<T>* next = tmp->GetNext();
	tmp->SetNext(new Node<T>(value));
	tmp->GetNext()->SetNext(next);
	count++;
}

template <typename T>
void LinkedList<T>::pop_back()
{
	Node<T>* tmp = head;
	for (size_t i = 0; i < count - 2; i++)
	{
		tmp = tmp->GetNext();
	}
	delete tmp->GetNext();
	tmp->SetNext(head);
	count--;
}

template <typename T>
void LinkedList<T>::pop_front()
{
	Node<T>* del = head;
	head = head->GetNext();
	delete del;
	count--;
	Node<T>* tmp = head;
	for (size_t i = 0; i < count - 1; i++)
	{
		tmp = tmp->GetNext();
	}
	tmp->SetNext(head);
}

template <typename T>
void LinkedList<T>::remove_at(size_t index)
{
	if (index > count - 1)
	{
		cout << "Index not found" << endl;
		return;
	}
	if (index == 0)
	{
		pop_front();
		return;
	}
	Node<T>* tmp = head;
	for (size_t i = 0; i < index - 1; i++)
	{
		tmp = tmp->GetNext();
	}
	Node<T>* del = tmp->GetNext();
	tmp->SetNext(tmp->GetNext()->GetNext());
	delete del;
	count--;
}

template <typename T>
T& LinkedList<T>::operator[](const size_t index) // Set
{
	if (index > count - 1)
	{
		cout << "Wrong index" << endl;
		throw new exception("Wrong index");
	}
	Node<T>* tmp = head;
	for (size_t i = 0; i < index; i++)
	{
		tmp = tmp->GetNext();
	}
	return *(tmp->GetValueAds());
}

template <typename T>
T const& LinkedList<T>::operator[](const size_t index) const // Get
{
	if (index > count - 1)
	{
		cout << "Wrong index" << endl;
		throw new exception("Wrong index");
	}
	Node<T>* tmp = head;
	for (size_t i = 0; i < index; i++)
	{
		tmp = tmp->GetNext();
	}
	return tmp->GetValue();
}

template <typename T>
size_t LinkedList<T>::size()const
{
	return count;
}

template <typename T>
bool LinkedList<T>::empty()const
{
	return count == 0;
}

template <typename T>
void LinkedList<T>::clear()
{
	Node<T>* tmp = head;
	Node<T>* del;
	for (size_t i = 0; i < count; i++)
	{
		del = tmp;
		tmp = tmp->GetNext();
		delete del;
	}
	head = nullptr;
	count = 0;
}

template <typename T>
T LinkedList<T>::front()const
{
	return head->GetValue();
}

template <typename T>
T LinkedList<T>::back()const
{
	Node<T>* tmp = head;
	for (size_t i = 0; i < count - 1; i++)
	{
		tmp = tmp->GetNext();
	}
	return tmp->GetValue();
}