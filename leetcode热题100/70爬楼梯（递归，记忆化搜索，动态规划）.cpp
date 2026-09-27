#include <iostream> // cout：第 71 行首次使用
#include <vector> // vector：第 58 行首次使用
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

