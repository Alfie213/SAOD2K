#include <iostream>
#include <vector>
using namespace std;

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void bubble_sort_inc(int array[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i -1; j++)
		{
			if (array[j] > array[j+1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

void bubble_sort_dec(int array[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (array[j] < array[j + 1])
			{
				Swap(array[j], array[j + 1]);
			}
		}
	}
}

//void bubble_sort_inc_VEC(int *array, int n)
//{
//	for (int i = 0; i < n - 1; i++)
//	{
//		for (int j = 0; j < n - i - 1; j++)
//		{
//			if (array[j] > array.at(j + 1))
//			{
//				int temp = array.at(j);
//				array.at(j) = array.at(j + 1);
//				array.at(j + 1) = temp;
//				//Swap(array.at(j), array.at(j + 1));
//			}
//		}
//	}
//}

int main(int argc, char* argv[])
{
#pragma region DebugArg
	cout << "There are " << argc << " argc" << endl;
	for (int i = 0; i < argc; i++)
	{
		cout << "argv is " << argv[i] << endl;
	}
#pragma endregion

	int* a = new int[argc-2];


	//int* start = a;

	cout << "argv[2] is " << argv[2] << endl;
	cout << "(int)argv[2] is " << (int)argv[2] << endl;
	cout << "(atoi)argv[2] is " << atoi(argv[2]) << endl;

	//vector<int> array{ };
	for (int i = 2; i < argc; i++)
	{
		a[i-2] = atoi(argv[i]);
	//	array.push_back(atoi(argv[i]));
	//	cout << *a << " ravno " << atoi(argv[i]) << endl;
	}

	bubble_sort_inc(a, argc - 2);

	for (int i = 0; i < argc-2; i++)
	{
		cout << *(a+i) << '\t';
	}
	delete [] a;

	/*cout << "a = " << *(--a) << endl;
	for (int i = 0; i < argc-2; i++)
	{
		cout << *start++ << '\t';
	}*/

	/*for (int i = 0; i < argc; i++)
	{
		cout << a[i] << '\t';
	}*/

	/*vector<int> array { 8,5,12,53,28 };
	bubble_sort_dec(array, 5);

	for (int i = 0; i < 5; i++)
	{
		cout << array[i] << '\t';
	}*/


	//// Сосчитаем количество элементов для нашего массива. Нулевой и первый индекс пропускаем (в первом системный путь, во втором inc/dec).
	//int count = 0;
	//for (int i = 2; i < argc; i++) count++;
	//const int length = count;

	////////vector<int> array;
	////////for (int i = 2; i < argc; i++) array.push_back(atoi(argv[i]));
	/////////*for (int i = 0; i < array.size(); i++)
	////////{
	////////	cout << array[i] << endl;
	////////}*/

	////////int size = array.size();
	////////int** some = new int* [size];
	////////int mas[some]
}



	/*if (argv[2] == "inc")
	{
		int 
	}
	else if (argv[2] == "dec")
	{

	}
	else cout << "Wrong expression" << endl;*/

	//////int mas[5]{ 8,5,12,53,28 };
	////////int mas[6]{ 4,1,2,12,4,0 };

	//////bubble_sort_dec(mas, 5);

	//////for (int i = 0; i < 5; i++)
	//////{
	//////	cout << mas[i] << '\t';
	//////}
	///////*int x = 5; int y = 10;
	//////Swap(x, y);
	//////cout << x << y << endl;*/