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

