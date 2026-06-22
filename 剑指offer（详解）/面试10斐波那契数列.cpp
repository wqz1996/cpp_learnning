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
// 面试题10：斐波那契数列
// 题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
class Solution {
public:
	int fib(int n) {
		int firstfib = 0;
		int secondfib = 1;
		int fibnum;
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		for (int i = 2; i <= n; i++) {
			fibnum = firstfib + secondfib;
			while (fibnum > 1000000007) {//求模运算
				fibnum %= 1000000007;
				secondfib %= 1000000007;
			}
			firstfib = secondfib;
			secondfib = fibnum;	
			
		}
		return fibnum;
	}
};
/****************记忆化搜索************************/
class Solution1 {
public:
	int fib(int n) {
		vector<int> dp(n+1,0);
		dp[0] = 0;
		dp[1] = 1;
		for (int i = 2; i <= n; i++)
			dp[i] = (dp[i - 1] + dp[i - 2]) % 1000000007;
		return dp[n];
	}
};
/****************递归************************/
class Solution2 {
public:
	int fib(int n) {
		if (n <= 0)
			return 0;
		if (n == 1)
			return 1;
		return fib(n - 1) + fib(n - 2);
	}
};
int main()
{
	cout << Solution2().fib(45) << endl;
	return 0;
}

