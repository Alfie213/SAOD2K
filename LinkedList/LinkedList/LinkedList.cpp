#include <iostream>
#include "LinkedList.h"
using namespace std;

int main()
{
    LinkedList<char> lst;
    cout << boolalpha << lst.empty() << endl;

    for (int i = 0; i < 5; i++)
        lst.push_back(char('a' + i));

    lst.print();

    for (int i = 0; i < 5; i++)
        lst.insert(0, char('z' - i));

    lst.print();

    for (size_t i = 0; i != lst.size(); i++)
        lst[i] = char('a' + i);

    lst.print();

    lst.pop_back();
    lst.pop_front();

    lst.print();

    lst.remove_at(5);
    lst.insert(3, 'o');

    lst.print();

    lst.clear();

    lst.push_back('q');
    lst.push_back('w');

    cout << lst.size() << ' ' << boolalpha << lst.empty() << endl;
    //cout << "End of main()" << endl;
    //std::cout << "Hello World!\n";
}