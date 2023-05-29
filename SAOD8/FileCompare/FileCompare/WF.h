#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

class WF
{
private:
    int* pm;
    int N;
    int M;
    std::vector<std::string> prevVersion, curVersion;

public:
    WF(int n, int m) {
        N = n;
        M = m;
        pm = new int[N * M];
    }

    ~WF() {
        delete[] pm;
    }

    int Rows()const {
        return N;
    }

    int Columns()const {
        return M;
    }

    int Get(int i, int j)const {
        return pm[i * M + j];
    }

    void Set(int i, int j, int val) {
        pm[i * M + j] = val;
    }

    int Min(int a, int b, int c) {
        int min = a;
        if (b < min) {
            min = b;
        }
        if (c < min) {
            min = c;
        }
        return min;
    }

    int LevenshteinDistance(std::string s1, std::string s2) {
        int len1 = s1.length();
        int len2 = s2.length();
        for (int i = 0; i <= len1; i++) {
            Set(i, 0, i);
        }
        for (int j = 0; j <= len2; j++) {
            Set(0, j, j);
        }
        for (int i = 1; i <= len1; i++) {
            for (int j = 1; j <= len2; j++) {
                int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
                Set(i, j, Min(Get(i - 1, j) + 1, Get(i, j - 1) + 1, Get(i - 1, j - 1) + cost));
            }
        }
        return Get(len1, len2);
    }

    std::string GetPrescription() {
        int i = prevVersion.size();
        int j = curVersion.size();
        int min = 0;
        int min_value = 0;
        std::string prescription = "";
        while (i > 0 || j > 0) {
            if (i == 0) {
                prescription = ">>>" + curVersion[j - 1] + prescription;
                j--;
            }
            else if (j == 0) {
                prescription = "<<<" + prevVersion[i - 1] + prescription;
                i--;
            }
            else {
                min_value = Min(Get(i - 1, j), Get(i, j - 1), Get(i - 1, j - 1));
                if (min_value == Get(i - 1, j - 1)) {
                    if (Get(i, j) == Get(i - 1, j - 1)) {
                        prescription = " " + prevVersion[i - 1] + prescription;
                    }
                    else {
                        prescription = "*" + prevVersion[i - 1] + prescription;
                    }
                    i--;
                    j--;
                }
                else if (min_value == Get(i, j - 1)) {
                    prescription = ">>>" + curVersion[j - 1] + prescription;
                    j--;
                }
                else if (min_value == Get(i - 1, j)) {
                    prescription = "<<<" + prevVersion[i - 1] + prescription;
                    i--;
                }
            }
        }
        return prescription;
    }

    void Compare(std::istream& prev, std::istream& current) {
        std::string line;
        std::string prevStr = "";
        std::string currentStr;
        while (getline(prev, line)) {
            prevVersion.push_back(line);
            prevStr += line;
            prevStr += '\n';
        }
        while (getline(current, line)) {
            curVersion.push_back(line);
            currentStr += line;
            currentStr += '\n';
        }

        int distance = LevenshteinDistance(prevStr, currentStr);

        std::cout << "Distance: " << distance << std::endl;
        std::cout << "Prescription: " << GetPrescription() << std::endl;
    }

    std::string PrevLine(int i) const {
        if (i < 0 || i >= prevVersion.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return prevVersion[i];
    }

    std::string CurLine(int i) const {
        if (i < 0 || i >= curVersion.size())
        {
            throw std::out_of_range("Index out of range");
        }
        return curVersion[i];
    }

    std::string istreamToString(std::istream& inputStream) {
        std::ostringstream oss;
        oss << inputStream.rdbuf();
        return oss.str();
    }
};