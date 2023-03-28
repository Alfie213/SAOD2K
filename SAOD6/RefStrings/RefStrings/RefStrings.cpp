#include <iostream>
#include "Str.h"

using namespace std;

int main()
{
    Str s("hi");
    s[0] = 'k';
    std::cout << s << endl;
    Str* cpy = new Str(s);
    cpy->operator[](0) = 'q';
    cout << "s is " << s << endl;
    cout << "cpy is " << *cpy << endl;

    cout << "Hello World!\n";
    delete cpy;
}