#include <iostream>
#include <fstream>

#include "WF.h"

int main()
{
    /*std::cout << "Hello World!\n";
    std::ifstream prev("TestData/prev.txt");
    std::ifstream cur("TestData/cur.txt");
    WF wf(prev.size());
    wf.Compare(prev, cur);*/

    std::vector<std::string> prevVersion, curVersion;

    std::ifstream prev("TestData/prev.txt");
    if (!prev) {
        std::cerr << "Error: could not open file" << "\n";
        return 0;
    }

    std::ifstream cur("TestData/cur.txt");
    if (!cur) {
        std::cerr << "Error: could not open file" << "\n";
        return 0;
    }

    WF wf(sizeof(cur), sizeof(prev));
    wf.Compare(prev, cur);
    /*std::cout << wf.GetPrescription() << std::endl;
    std::cout << wf.LevenshteinDistance("123", "1dsl23") << std::endl;*/
    return 0;
}