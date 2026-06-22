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
//面试题45. 把数组排成最小的数
// 题目：给定一个数字，我们按照如下规则把它翻译为字符串：
//0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，
//25 翻译成 “z”。一个数字可能有多个翻译。请编程实现一个函数，
//用来计算一个数字有多少种不同的翻译方法。
/************最简单的方法*************/
class Solution {
public:
	int translateNum(int num) {
		if (num < 10) return 1;
		//num%100取后两位，
		return (num % 100 < 10 || num % 100 > 25) ? translateNum(num / 10) : translateNum(num / 10) + translateNum(num / 100);
	}
};
/************动态规划（存疑）************/
class Solution1 {
	bool judgerange(char s1, char s2) {
		char str[2] = { s1,s2 };
		string s=str;
		int num = stoi(s);
		return num <= 25 && num >= 10;
	}
public:
	int translateNum(int num) {
		string s = to_string(num);
		int n = s.size();
		vector<int> dp(n);
		if (n <= 1)
			return n;
		dp[0] = 1;
		dp[1] = judgerange(s[0], s[1]) ? 2 : 1;
		for (int i = 2; i < n; i++) {
			dp[i] = judgerange(s[i - 1], s[i]) ? dp[i-2]+dp[i-1] : dp[i-1];
		}
		return dp[n - 1];
	}
};
int main()
{
	Solution1().translateNum(1402);

	return 0;
}

