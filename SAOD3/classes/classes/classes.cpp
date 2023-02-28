#include <iostream>
#include <cmath>

#include "Complex.h"

using namespace std;

int main()
{
    Complex a[3]{ 1, 4, Complex(3,1) };
    for (Complex* pa = a; pa - a < 3; pa++)
    {
        cout << *pa << '\t';
    }

    cout << endl << endl;
    Complex* pc = new Complex(1, 2);
    cout << *pc << endl;
    cout << pc -> Re << endl;
    cout << pc -> Im << endl;
    delete(pc);
    //std::cout << "Hello World!\n";
}