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
#include<assert.h>
#include<set>
#include<map>
using namespace std;
void swap1(int& a, int& b) {//使用加减运算不使用额外变量交换ab值
	a = a + b;//a为sum
	b = a - b;//sum-b等于a的值，此时b为a
	a = a - b;//sum-a=b
}
void swap2(int& a, int& b) {//使用异或运算不使用额外变量交换ab值
	a = a ^ b;//a为sum是a和b所有为1的位全部置1
	b = a ^ b;//取b中与sum不同的则是a中所有的1，此时b为a
	a = a ^ b;//再取sum中与a不同的位，则是b
}
void swap3(int& a, int& b) {//使用异或运算不使用额外变量交换ab值
	int temp = a;
	a = b;
	b = temp;
}
int main() {

	
	int a = 3;
	int b = 4;
	swap2(a, b);
	cout << a <<' '<< b << endl;
	return 0;
}