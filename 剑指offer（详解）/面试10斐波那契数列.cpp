#include <iostream> // 使用处：第 54 行的 cout
#include <vector> // 使用处：第 33 行的 vector
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

