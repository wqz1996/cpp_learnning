#include <iostream> // 使用处：第 36 行的 cout
using namespace std;
// 面试题10：青蛙跳台阶问题
// 题目：一只青蛙一次可以跳上1级台阶，
//也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。
//f(n)=f(n-1)+f(n-1)
//f(0)=1.f(1)=1,f(2)=2
class Solution {
public:
	int numWays(int n) {
		if (n == 0)
			return 1;
		if (n == 1)
			return 1;
		if (n == 2)
			return 2;
		int firstfib = 1;
		int secondfib = 2;
		int fibN = 0;
		for (int i = 2; i < n; i++) {
			fibN = firstfib + secondfib;
			while (fibN > 1000000007) {
				fibN %= 1000000007;
				secondfib %= 1000000007;
			}

			firstfib = secondfib;
			secondfib = fibN;

		}
		return fibN;
	}
};
int main()
{
	cout << Solution().numWays(44) << endl;
	return 0;
}

