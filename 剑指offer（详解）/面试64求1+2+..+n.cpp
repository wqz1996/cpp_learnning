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
using namespace std;
//面试题64. 求1+2+…+n
// 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case
//等关键字及条件判断语句（A?B:C）。
/*********递归************/
//利用&&和||的特性，A&&B，当A为false则不执行B作为递归终止条件
class Solution {
public:
	int sumNums(int n) {
		n&& (n += sumNums(n - 1));//n==0时,n为false，则不执行&&后面语句
		return n;
	}
};
/*********位运算实现快速乘*********/
class Solution {
private:
	int quickMulti(int A, int B) {
		int res = 0;
		while (B != 0) {
			if ((B & 1) == 1)//判断B最后一位是否是1
				res += A;
			A <<= 1;//A向左移
			B >>= 1;//B向右移
		}
		return res;
	}
public:
	int sumNums(int n) {
		return quickMulti(n, (n + 1)) >> 1;
	}
};
int main()
{

	return 0;
}

