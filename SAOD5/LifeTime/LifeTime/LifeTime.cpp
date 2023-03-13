#include <iostream>

#include "Test.h"
#include "Child.h"
#include "Aggregate.h"
#include "AggregateT.h"

using namespace std;

void Func(Test test)
{
    cout << "Func() is running" << endl;
}
int main()
{
    cout << "Hello!" << endl;
    //Child somech = Child(9);
    AggregateT<Child> agT = AggregateT<Child>();
    //AggregateT<Test> agT = AggregateT<Test>();
    cout << "Bye!" << endl;
#pragma region First
    /*cout << "Before creating" << endl;
    Test* h = new Test();
    cout << "After creating" << endl;
    cout << "Before destroying" << endl;
    delete h;
    cout << "After destroying" << endl;*/
#pragma endregion
}