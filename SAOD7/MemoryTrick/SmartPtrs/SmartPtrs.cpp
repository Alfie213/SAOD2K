#include <iostream>
#include <memory>

#include "Test.h"

using namespace std;

shared_ptr<Test> foo()
{
    Test* temp = new Test();
    temp->Val = 5;
    shared_ptr<Test> pt(temp);
    return pt;
}

Test* goo()
{
    Test* temp = new Test();
    temp->Val = 5;
    return temp;
}

int main()
{
    std::cout << "Start\n";

    shared_ptr<Test> t;

    std::cout << "before block\n";
    auto p = foo();
    t = p;
    std::cout << p->Val << endl;
    std::cout << "after block\n";
}