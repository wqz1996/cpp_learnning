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
/*************343整数拆分******************/
//给定整数n，将其拆分为至少两个正整数和
//使得这些数乘积最大，求最大乘积
class Solution {//记忆化搜索法
private:
	vector<int> mem;//记录已经计算过的最大乘积
	int max3(int a, int b, int c) {
		return max(a, max(b, c));

	}
	int breakInteger(int n) {//递归函数，记忆化搜索
		if (n == 1)
			return 1;
		if (mem[n] != -1)
			return mem[n];
		int res = -1;
		for (int i = 1; i <= n - 1; i++) {//i+(n-i)
			res=max3(res, i*(n-i),i * breakInteger(n - i));//将分割为两部分与分割成两部分以上取最大
			
		}
		mem[n] = res;
		return res;
	}
public:
	int integerBreak(int n) {
		assert(n >= 2);
		mem = vector<int>(n + 1, -1);
		return breakInteger(n);
	}
};
class Solution {//动态规划
private:
	int max3(int a, int b, int c) {
		return max(a, max(b, c));

	}
public:
	int integerBreak(int n) {
		assert(n >= 2);
		vector<int> mem(n + 1, -1);//将数字i分割至少两份后得到的乘积
		mem[1] = 1;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= i - 1; j++) {//将i分割为j+（i-j）
				//mem[i-j]表示i-j的最大值已经在之前计算完成
				//mem[i]数字i分割后组成乘积最大值
				mem[i] = max3(mem[i] , j * (i - j), j * mem[i - j]);


			}
		}
		return mem[n];

	}
};
int main()
{
	
	return 0;

}

