#include <algorithm> // 使用处：第 20 行的 max(
#include <iostream> // 使用处：第 58 行的 cout
#include <string> // 使用处：第 10 行的 string
#include <vector> // 使用处：第 9 行的 vector
using namespace std;
/*************1143最长公共子序列******************/
class Solution {
private:
	vector<vector<int>> mem;
	int getlongest(string& s1, string& s2, int m, int n) {
		if (m < 0 || n < 0)
			return 0;

		if (mem[m][n] != -1)
			return mem[m][n];

		if (s1[m] == s2[n])
			mem[m][n] = 1 + getlongest(s1, s2, m - 1, n - 1);
		else
			mem[m][n] = max(getlongest(s1, s2, m - 1, n), getlongest(s1, s2, m, n - 1));

		return mem[m][n];

	}
public:
	/*********************记忆化搜索*************************/
	int longestCommonSubsequence(string& text1, string& text2) {
		if (text1.size() == 0 || text2.size() == 0)
			return 0;
		
		int len1 = text1.size();
		int len2 = text2.size();
		mem = vector<vector<int>>(len1, vector<int>(len2, -1));
		return getlongest(text1, text2, len1 - 1, len2 - 1);
	}
	/*********************动态规划*************************/
	int longestCommonSubsequenceDP(string& text1, string& text2) {
		int len1=text1.size();
		int len2 = text2.size();
		if (len1 == 0 || len2 == 0)
			return 0;

		vector<vector<int>> mem(len1 + 1, vector<int>(len2 + 1, 0));
		for(int i=0;i<len1;i++)
			for (int j = 0; j < len2; j++) {
				if (text1[i] == text2[j])
					mem[i + 1][j + 1] = 1 + mem[i][j];
				else
					mem[i + 1][j + 1] = max(mem[i + 1][j], mem[i][j + 1]);
			}
		return mem[len1][len2];
	}
};
int main()
{
	string s1{ "pmjghexybyrgzczy" };
	string s2{ "hafcdqbgncrcbihkd" };
	cout << Solution().longestCommonSubsequenceDP(s1, s2);
	return 0;
}

