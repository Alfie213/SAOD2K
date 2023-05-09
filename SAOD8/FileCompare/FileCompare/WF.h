#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

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

	void Compare(std::istream& prev, std::istream& current) {
		std::string line;
		while (std::getline(prev, line)) {
			prevVersion.push_back(line);
		}
		while (std::getline(current, line)) {
			curVersion.push_back(line);
		}
		int n = prevVersion.size();
		int m = curVersion.size();
		std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
		for (int i = 0; i <= n; i++) {
			dp[i][0] = i;
		}
		for (int j = 0; j <= m; j++) {
			dp[0][j] = j;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (prevVersion[i - 1] == curVersion[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = 1 + std::min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
				}
			}
		}
		std::cout << "Distance: " << dp[n][m] - 1 << std::endl;
	}

	std::string Prescription() const {
		std::vector<std::string> script;
		int i = Rows() - 1;
		int j = Columns() - 1;
		while (i > 0 || j > 0) {
			if (i > 0 && j > 0 && Get(i - 1, j - 1) == Get(i, j)) {
				i--;
				j--;
				script.push_back("M");
			}
			else if (i > 0 && Get(i - 1, j) == Get(i, j) - 1) {
				i--;
				script.push_back("D");
			}
			else if (j > 0 && Get(i, j - 1) == Get(i, j) - 1) {
				j--;
				script.push_back("I");
			}
			else {
				i--;
				j--;
				script.push_back("S");
			}
		}
		std::reverse(script.begin(), script.end());
		std::string result;
		for (const auto& op : script) {
			result += op;
		}
		return result;
	}

	int Rows()const {
		return N;
	}

	int Columns()const {
		return M;
	}

	int Get(int i, int j)const {
		return pm[i, j];
	}

	void Set(int i, int j, int val) {
		pm[i, j] = val;
	}
};