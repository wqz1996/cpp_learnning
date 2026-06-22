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
/*************70 爬楼梯******************/
//共n阶楼梯，一次可以上一阶或者两阶，共有多少种不同的爬楼梯方法
/***************递归方法************************/
//class Solution {
//private:
//	int calcWay(int n) {
//		if (n == 1)
//			return 1;
//
//		if (n == 2)
//			return 2;
//
//		return calcWay(n - 1) + calcWay(n - 2);
//	}
//public:
//	int climbStairs(int n) {
//		assert(n > 0);
//		return calcWay(n);
//	}
//};
//class Solution {
//private:
//	vector<int> mem;
//	int calcWay(int n) {
//		if (n == 0 || n == 1)
//			return 1;
//		if (mem[n] == -1)
//			mem[n] = calcWay(n - 1) + calcWay(n - 2);
//
//		return mem[n];
//	}
//public:
//	int climbStairs(int n) {
//		mem = vector<int>(n + 1, -1);
//		return calcWay(n);
//	}
//};
//
///***************动态规划************************/
//class Solution {
//public:
//	int climbStairs(int n) {
//		vector<int> mem(n + 1, -1);
//		mem[0] = 1;
//		mem[1] = 1;
//		for (int i = 2; i <= n; i++) {
//			mem[i] = mem[i - 1] + mem[i - 2];
//		}
//		return mem[n];
//	}
//};
class Solution {
public:
	int climbStairs(int n) {
		vector<int> mem(n + 1, -1);
		mem[0] = 1;
		mem[1] = 1;
		mem[2] = 2;
		for (int i = 3; i <= n; i++) {
			mem[i] = mem[i - 1] + mem[i - 2];
		}
		return mem[n];
	}
};
int main()
{

	cout<<Solution().climbStairs(1);
	return 0;

}

