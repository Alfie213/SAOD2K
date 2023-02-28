#include <iostream>
using namespace std;

void rotate(int a[], int n)
{
	int x = a[0];
	for (int i = 1; i < n; i++)
		a[i - 1] = a[i];
	a[n - 1] = x;
}

void Protate(int a[], int n)
{
	int* pa = a;
	int first = *pa;
	for (int* pi = pa + 1; pi - pa < n; pi++)
	{
		*(pi - 1) = *pi;
	}
	*(pa + n - 1) = first;
}

void ClockRotate(int a[], int n, bool clockwise = false)
{
	int x;
	if (clockwise)
	{
		x = a[n - 1];
		for (int i = n - 2; i + n + 1 > n; i--)
			a[i + 1] = a[i];
		a[0] = x;
	}
	else
	{
		x = a[0];
		for (int i = 1; i < n; i++)
			a[i - 1] = a[i];
		a[n - 1] = x;
	}

}

void ClockProtate(int a[], int n, bool clockwise = false)
{
	int* pa;
	if (clockwise)
	{
		pa = a + n - 1;
		int last = *pa;
		for (int* pi = pa - 1; pa - pi < n; pi--)
		{
			*(pi + 1) = *pi;
		}
		*a = last;
	}
	else
	{
		pa = a;
		int first = *pa;
		for (int* pi = pa + 1; pi - pa < n; pi++)
		{
			*(pi - 1) = *pi;
		}
		*(pa + n - 1) = first;
	}
}


int main()
{
	int a[5]{ 1,5,10,15,20 };

	for (int i = 0; i < 5; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl;

	for (int* p = a; p - a < 5; p++)
	{
		cout << *p << ' ';
		//cout << "p is " << p << ". *p is " << *p << endl;
	}
	cout << endl;

	cout << "Start" << endl;
	ClockProtate(a, 5, true);
	for (int* p = a; p - a < 5; p++)
	{
		cout << *p << ' ';
	}
}