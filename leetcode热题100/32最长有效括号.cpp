#include <algorithm> //包含堆操作
#include <iostream>
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
/************32最长有效括号********************/
// 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
class Solution1
{
public:
	// 贪心算法：使用left记录'(' right记录')'，每当left和right相等时，记录当前left+right为最长的有效括号
	// 正向遍历时，当right>left时，将left和right都置零
	// 反向遍历时，当left>right时，将left和right都置零
	int longestValidParentheses(string s)
	{
		int res = 0;
		int left = 0, right = 0;
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '(')
			{
				left++;
			}
			else if (s[i] == ')')
			{
				right++;
			}
			else
			{
				throw invalid_argument("invalid input");
			}
			if (left == right)
			{
				res = max(res, left + right);
			}
			else if (right > left)
			{
				left = right = 0;
			}
		}
		left = right = 0;
		for (int i = s.length() - 1; i >= 0; i--)
		{
			if (s[i] == '(')
			{
				left++;
			}
			else if (s[i] == ')')
			{
				right++;
			}
			else
			{
				throw invalid_argument("invalid input");
			}
			if (left == right)
			{
				res = max(res, left + right);
			}
			else if (left > right)
			{
				left = right = 0;
			}
		}
		return res;
	}
};

class Solution2
{
public:
	// 用栈实现
	// 具体做法是我们始终保持栈底元素为当前已经遍历过的元素中「最后一个没有被匹配的右括号的下标」，
	// 这样的做法主要是考虑了边界条件的处理，栈里其他元素维护左括号的下标：

	// 对于遇到的每个 ‘(’，我们将它的下标放入栈中
	// 对于遇到的每个 ‘)’，我们先弹出栈顶元素表示匹配了当前右括号：
	// 如果栈为空，说明当前的右括号为没有被匹配的右括号，我们将其下标放入栈中来更新我们之前提到的
	// 「最后一个没有被匹配的右括号的下标」
	// 如果栈不为空，当前右括号的下标减去栈顶元素即为「以该右括号为结尾的最长有效括号的长度」
	// 我们从前往后遍历字符串并更新答案即可。

	int longestValidParentheses(string s)
	{
		int res = 0;
		stack<int> stk;
		stk.push(-1); // 栈顶用于记录最后一个未配对的右括号，为防止第一个就是左括号，给赋值一个-1
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] == '(')
			{
				stk.push(i); // 碰到左括号将其索引压入栈中
			}
			else if (s[i] == ')')
			{
				stk.pop(); // 每当碰到一个右括号，弹出栈顶元素
				if (stk.empty())
				{
					stk.push(i);
				}
				else
				{
					res = max(res, i - stk.top());
				}
			}
		}
		return res;
	}
};

class Solution3
{
public:
	// 动态规划 dp[i] 表示以下标i结尾的最长有效括号的长度
	// 以'('结尾的有效子串定为0，有效子串一定以')'结尾

	// 1. s[i-1] = '(' 且 s[i] = ')'
	// 最后一个和倒数第二个已经构成了一个有效括号，因此只需判断i-2的有效括号长度加上当前的长度为2的有效括号即可
	// 递推表达式 dp[i] = dp[i-2] + 2
	// 2. s[i-1] = ')' 且 s[i] = ')' 如果s[i-dp[i-1]-1] = '('
	// 递推表达式 dp[i] = dp[i-1] + dp[i - dp[i-1] - 2] + 2
	int longestValidParentheses(string s)
	{
		int res = 0;
		int n = s.length();
		vector<int> dp(n, 0);
		for (int i = 1; i < n; i++)
		{
			if (s[i] == ')')
			{
				if (s[i - 1] == '(')
				{
					dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
				}
				else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(')
				{
					dp[i] = dp[i - 1] +
							((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
				}
				res = max(res, dp[i]);
			}
		}
		return res;
	}
};
int main()
{

	return 0;
}