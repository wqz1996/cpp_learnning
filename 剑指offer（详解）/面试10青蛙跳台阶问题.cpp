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

