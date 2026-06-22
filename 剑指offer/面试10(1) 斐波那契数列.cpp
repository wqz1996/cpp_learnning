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
using namespace std;
// 面试题10：斐波那契数列
// 题目：写一个函数，输入n，求斐波那契（Fibonacci）数列的第n项。
class Solution {
public:
	int Fibonacci(int n) {
		int begin[2] = { 0,1 };
		if (n < 2)
			return begin[n];
		long fibfirst = 0;
		long fibsecond = 1;
		int fibn = 0;
		for (int i = 2; i <= n; i++) {
			fibn = fibfirst + fibsecond;
			fibfirst = fibsecond;
			fibsecond = fibn;
		}
		return fibn;
	}
};
/*******************递归***************/
int Fibn(int n) {
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibn(n - 1) + Fibn(n - 2);
}
int main()
{

	return 0;

}



