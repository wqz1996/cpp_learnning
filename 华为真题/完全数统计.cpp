#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
//它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
//例如：28，它有约数1、2、4、7、14、28，除去它本身28外，其余5个数相加，1 + 2 + 4 + 7 + 14 = 28。
//给定函数count(int n), 用于计算n以内(含n)完全数的个数。计算范围, 0 < n <= 500000
//返回n以内完全数的个数。 异常情况返回 - 1
using namespace std;
bool perfectnum(int n) {//判断n是否是完全数
	int sum = 0;
	for (int i = 1; i < n ; i++) {
		if (n % i== 0) {
			sum += i;
			
		}
	}
	if (sum == n)
		return true;
	else
		return false;
		
}
int count(int n) {//统计从1-n的完全数个数
	int res = 0;
	for (int i = 1; i <= n; i++) {
		if (perfectnum(i))
			res++;
	}
	return res;
}
int main() {
	int n;

	while (cin >> n) {
		cout << count(n) << endl;
	}
	
	return 0;
}

