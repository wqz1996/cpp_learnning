#include<algorithm>//包含堆操作
#include <cstdint> // 使用处：第 13 行的 uint32_t
#include <iostream> // 使用处：第 56 行的 cout
using namespace std;
// 面试题15: 二进制中1的个数
// 题目：请实现一个函数，输入一个整数，输出该数二进制表示中 1 的个数。
//例如，把 9 表示成二进制是 1001，有 2 位是 1。
//因此，如果输入 9，则该函数输出 2。
/*********************传统解法*************************/
//当负数时，左移会始终保持第一位是1，陷入死循环
class Solution {
public:
	int hammingWeight(uint32_t n) {
		int count = 0;
		while (n != 0) {
			if ((n & 1) == 1) {
				count++;
			}
			n >>= 1;
		}
		return count;
	}
};
/*********************优化解法*************************/
//不移动原数据，移动与运算的数据
class Solution1 {
public:
	int hammingWeight(uint32_t n) {
		int count = 0;
		uint32_t flag = 1;
		while (flag != 0)
		{
			if ((n & flag) != 0) {
				count++;
			}
			flag <<= 1;
		}
		return count;
	}
};
/*********************最优化解法*************************/
//数据中有几个1则移动几次
class Solution2 {
public:
	int hammingWeight(uint32_t n) {
		int count = 0;
		while (n != 0) {
			count++;
			n &= (n - 1);
		}
		return count;
	}
};
int main()
{
	cout << Solution2().hammingWeight(9) << endl;

	return 0;
}

