#include <iostream>
using namespace std;

/// <summary>
/// Copy the value of string d to string s.
/// </summary>
void string_copy(char* d, char* s)
{
    for (char* pd = s, *ps = d;*pd != *ps; pd++, ps++)
    {
        *pd = *ps;
    }
}

/// <summary>
/// Returns lenght of the input string (char[]).
/// </summary>
/// <param name="s">Input string</param>
/// <returns>Lenght</returns>
int len(const char* ps)
{
    int lenght = 0;
    //cout << "ps is " << ps << endl;
    for (int i = 0; ps[i] != '\0'; i++)
    {
        lenght++;
    }
    return lenght;
}

int compare(const char* s, const char* t)
{
#pragma region Is it right?
    /*if (s < t) return -1;
    else if (s > t) return 1;
    else return 0;*/
#pragma endregion
    for ((*t == *s) && *s; t++, s++;)
    {
        return *s - *t;
    }
}

void intFunc(const int* pn)
{
    cout << "pn is " << pn << endl;
}

int main()
{
    char str[] = "Hello!";
    char t[32];// = "text";
    //cout << t << endl;
    //for (char* pd = t, *ps = str;*pd++ = *ps++;);
    /*for (char* pd = t, *ps = str;*pd != *ps; pd++, ps++)
    {
        *pd = *ps;
    }*/

    /*string_copy(str, t);
    cout << t << endl;

    cout << len(t) << endl;*/

    /*int a = 5;
    int* pa = &a;
    cout << intFunc(pa) << endl;*/
    
    cout << len(str) << endl;
    cout << compare("Helloo", "H") << endl;
}