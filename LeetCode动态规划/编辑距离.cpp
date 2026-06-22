#include <algorithm> //包含堆操作
#include <iostream>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <string>
#include <cmath>
#include <stack>  //栈
#include <queue>  //队列
#include <vector> //不注重插入和删除效率
#include <list>	  //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <deque>  //双端队列，兼顾随即存取，和两端数据的插入删除
#include <ctime>
#include < unordered_map>
#include < unordered_set>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
// 编辑距离
// 将一个字符串删除、插入、替换变成目标字符串，最少次数
//(动态规划)
// dp[i][j]代表word1前i个字符 -> word2前j个字符所需要的最少操作次数
// dp[i][j]=word1[i]==word2[j]?dp[i-1][j-1]:min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1])+1;
// dp[i - 1][j]和dp[i][j-1]对应对word1或2进行插入或删除，对word1插入相当于对word2删除，
// dp[i-1][j-1]相当于替换操作
int editdistance(string w1, string w2)
{
	int len1 = w1.size();
	int len2 = w2.size();
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
	for (int i = 0; i <= len1; i++)
		dp[i][0] = i;
	for (int i = 0; i <= len2; i++)
		dp[0][i] = i;
	for (int i = 1; i <= len1; i++)
	{
		for (int j = 1; j <= len2; j++)
		{
			dp[i][j] = w1[i - 1] == w2[j - 1] ? dp[i - 1][j - 1] : min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
		}
	}
	return dp[len1][len2];
}

// DP method，近期使用的
// 对A删除等价于对B插入，同理对B删除等价于对A插入
// 对A替换和对B替换是等价的
// 本质有效的操作只有如下三种
// 1.对A插入
// 2.对B插入
// 3.对A替换
// dp[i][j]代表word1前i个字符-> word2前j个字符所需要的最少操作次数
// 状态转移方程
// 1.A和B最后一个字母相同
// dp[i][j] = min(dp[i][j-1]+1,dp[i-1][j]+1,dp[i-1][j-1])
// 2.A和B最后一个字母不相同
// dp[i][j] = 1 + min(dp[i][j-1],dp[i-1][j],dp[i-1][j-1])
class Solution1
{
public:
	int minDistance(string word1, string word2)
	{

		int len1 = word1.length();
		int len2 = word2.length();
		if (!len1 || !len2)
			return len1 + len2;
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));
		for (int i = 0; i <= len1; i++)
		{ // B为空，将B执行i次插入
			dp[i][0] = i;
		}
		for (int j = 0; j <= len2; j++)
		{ // A为空，将A
			dp[0][j] = j;
		}

		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				int insert_A = dp[i][j - 1] + 1;														// 在A末尾加一个字符
				int insert_B = dp[i - 1][j] + 1;														// 在B末尾加一个字符
				int replace_A = word1[i - 1] == word2[j - 1] ? dp[i - 1][j - 1] : dp[i - 1][j - 1] + 1; // 末尾字符相等则不用修改，否则替换A末尾字符
				dp[i][j] = min(insert_A, min(insert_B, replace_A));										// 在三种操作中取最小的操作数
			}
		}
		return dp[len1][len2];
	}
};

int main()
{
	string s1 = "horse";
	string s2 = "ros";
	int len = editdistance(s1, s2);
	return 0;
}