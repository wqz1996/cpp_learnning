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
// 面试题19. 正则表达式匹配
// 题目：请实现一个函数用来匹配包含'. '和'*'的正则表达式。
//模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符
//可以出现任意次（含0次）。在本题中，匹配是指字符串的所有字符匹配整个模式。
//例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但与"aa.a"和"ab*a"均不匹配。
/****************递归*******************/
class Solution {
public:
	bool isMatch(string s, string p) {
		if (p.empty())//匹配字符为空后
			return s.empty();//若s为空则完全匹配，否则无法匹配
		bool firstMatch = (!s.empty() && (s[0] == p[0] || p[0] == '.'));//p[0]和s[0]相等或者p[0]是'.'
		if (p.size()>=2 && p[1] == '*') {
			// isMatch(s, p.substr(2))表示*前面匹配0个s[0]字符，s与p第三个字符继续匹配
			//(firstMatch && isMatch(s.substr(1), p))第一个字符匹配，从s第二个字符继续与p进行下一轮匹配
			return (isMatch(s, p.substr(2)) || (firstMatch && isMatch(s.substr(1), p)));
		}
		else {
			return firstMatch && isMatch(s.substr(1), p.substr(1));//先判断firstMatch，避免超出范围
		}
	}
};
/*************动态规划*************************/
class Solution {
public:
	bool isMatch(string s, string p) {
		if (p.empty()) {
			return s.empty();
		}

		// 前面加某一相同字符，
		// 防止 (ab, c*ab) 这样的匹配，
		// 避免复杂的初始化操作
		s = " " + s;
		p = " " + p;
		int m = s.size(), n = p.size();

		// 定义记忆数组，并初始化为false
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

		// 设添加的字符为真
		dp[0][0] = true;
		//dp[i][j]表示s长度为i的子串与p长度为j的子串的匹配度，(i,j)对应的索引时dp[i-1][j-1]
		// 记忆数组能保持字符串上一个字符的状态
		// 因此可以对下一个字符进行判断
		for (int i = 1; i < m + 1; i++) {
			for (int j = 1; j < n + 1; j++) {
				// 不带 '*' 号时的匹配
				if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else if (p[j - 1] == '*') {
					// 考虑 '*' 时的两种情况
					if (s[i - 1] != p[j - 2] && p[j - 2] != '.') {//s当前字符与p前一个字符不等，且p前一个字符不是'.'
						dp[i][j] = dp[i][j - 2]; //则p[j - 2]字符不能出现，dp状态取决于p[j - 2]之前的字符
					}
					else {
						dp[i][j] = dp[i][j - 2] || dp[i][j - 1] || dp[i - 1][j];//若s当前字符与p前一个字符相等，或者p前一个字符是'.'，让p[j-2]出现0，1，多次都可以
					}
				}
			}

		}
		// 返回最后字符的匹配状态
		return dp[m][n];
	}
};
int main()
{
	
	return 0;
}

