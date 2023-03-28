#include <iostream>
#include "PF.h"
using namespace std;

int main()
{
    PF pf = PF();
    pf.Init("rakaratrakarakarakatakarakara");
    cout << int(pf) << endl;
    for (size_t i = 0; i < int(pf); i++)
    {
        cout << pf[i];
    }
    cout << endl;
    cout << pf.CmpCount() << endl;
    cout << "Hello World!\n";
}