#include <iostream>
#include "Str.h"

using namespace std;

void Test(Str s){}

int main()
{
    Str str = "123";
    cout << str << endl;
    Test(str);
    Str strCopy = str;
    strCopy = "1234";
    str = "12";
    cout << str << " and " << strCopy << endl;
    Str plusStr = str + strCopy;
    cout << "plusStr are " << plusStr << endl;
    str += strCopy;
    cout << "+= are " << str << endl;
    std::cout << "Hello World!\n";
}