#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

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
        const int m = prevVersion.size();
        const int n = curVersion.size();

        std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

        // Инициализация первой строки и первого столбца
        for (int i = 0; i <= m; ++i) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; ++j) {
            dp[0][j] = j;
        }

        // Заполнение матрицы расстояний
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (prevVersion[i - 1] == curVersion[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = 1 + std::min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
                }

                // Проверяем операцию транспозиции
                if (i > 1 && j > 1 && prevVersion[i - 1] == curVersion[j - 2] && prevVersion[i - 2] == curVersion[j - 1]) {
                    dp[i][j] = std::min(dp[i][j], dp[i - 2][j - 2] + 1);
                }
            }
        }

        // Восстановление редакционного предписания
        int i = m;
        int j = n;
        std::string prescription;

        while (i > 0 && j > 0) {
            if (prevVersion[i - 1] == curVersion[j - 1]) {
                --i;
                --j;
            }
            else if (dp[i][j] == dp[i - 1][j - 1] + 1) {
                prescription += "Replace " + prevVersion[i - 1] + " with " + curVersion[j - 1] + "\n";
                --i;
                --j;
            }
            else if (dp[i][j] == dp[i - 1][j] + 1) {
                prescription += "Delete " + prevVersion[i - 1] + "\n";
                --i;
            }
            else if (dp[i][j] == dp[i][j - 1] + 1) {
                prescription += "Insert " + curVersion[j - 1] + "\n";
                --j;
            }
            else if (i > 1 && j > 1 && dp[i][j] == dp[i - 2][j - 2] + 1 && prevVersion[i - 1] == curVersion[j - 2] && prevVersion[i - 2] == curVersion[j - 1]) {
                prescription += "Transpose " + prevVersion[i - 1] + " and " + prevVersion[i - 2] + "\n";
                i -= 2;
                j -= 2;
            }
        }

        // Добавляем оставшиеся операции в редакционное предписание
        while (i > 0) {
            prescription += "Delete " + prevVersion[i - 1] + "\n";
            --i;
        }

        while (j > 0) {
            prescription += "Insert " + curVersion[j - 1] + "\n";
            --j;
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
        std::cout << "Prescription:" << std::endl << GetPrescription() << std::endl;
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