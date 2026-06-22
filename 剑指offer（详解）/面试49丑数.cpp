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
//面试题 49. 丑数
// 题目：我们把只包含因子 2、3 和 5 的数称作丑数（Ugly Number）。
//求按从小到大的顺序的第 n 个丑数。
/***************传统解法（部分不通过）************************/
class Solution {
private:
	bool isUgly(int n) {//判断是否为丑数
		while (n % 2==0)
			n /= 2;
		while (n % 3==0)
			n /= 3;
		while (n % 5==0)
			n /= 5;
		return n == 1 ? true : false;
	}
public:
	int nthUglyNumber(int n) {
		if (n <= 0)
			return 0;
		int num = 0;
		int uglynum = 0;
		while (uglynum < n) {
			num++;
			if (isUgly(num))
				uglynum++;
		}
		return num;
	}
};
/***************优化解法************************/
class Solution1 {
public:
	int nthUglyNumber(int n) {
		vector<int> dp(n, 0);//保存所有丑数
		dp[0] = 1;//初始计算条件
		int p2 = 0, p3 = 0, p5 = 0;
		for (int i = 1; i < n; i++) {
			//计算*2、*3、*5的最小值优先放入后移动指针
			dp[i] = min(min(dp[p2] * 2, dp[p3] * 3), dp[p5] * 5);
			if (dp[p2] * 2 == dp[i])//判断是乘几得到的dp[i]
				p2++;
			if (dp[p3] * 3 == dp[i])
				p3++;
			if (dp[p5] * 5 == dp[i])
				p5++;
		}
		return dp[n - 1];
	}
	
};
int main()
{
	Solution1().nthUglyNumber(10);
	return 0;
}

