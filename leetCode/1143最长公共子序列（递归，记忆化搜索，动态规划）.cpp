#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
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

