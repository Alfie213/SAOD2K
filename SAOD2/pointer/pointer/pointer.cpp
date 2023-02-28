#include <iostream>
using namespace std;
typedef unsigned char byte;

void Swap(int *pa, int *pb)
{
	//cout << "*pa is " << *pa << endl;
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void NewSwap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
#pragma region MainSwapping
	int a = 3;
	int b = 5;
	cout << "Before MainSwap a is " << a << " b is " << b << endl;
	int c = a;
	a = b;
	b = c;
	cout << "After MainSwap a is " << a << " b is " << b << endl;
#pragma endregion
#pragma region Swapping
	int x = 5;
	int y = 10;
	cout << "Before Swap " << "x is " << x << " y is " << y << endl;
	Swap(&x, &y);
	cout << "After Swap " << "x is " << x << " y is " << y << endl;
#pragma endregion
#pragma region NewSwapping
	int q = 3;
	int w = 5;
	cout << "Before Swap " << "q is " << q << " w is " << w << endl;
	NewSwap(q, w);
	cout << "After Swap " << "q is " << q << " w is " << w << endl;
#pragma endregion

	

	/*int x = 3;
	int* p = &x;
	cout << x << "" << *p << "" << p << endl;
	p++; cout << p << endl;
	cout << p - &x << endl;

	byte* pb = (byte*)--p;
	for (byte *pt = pb; pt - pb < sizeof(int); pt++)
	{
		cout << (int)*pt << ' ';
	}
	cout << endl;*/
}