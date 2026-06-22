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
//面试题65. 不用加减乘除做加法
// 写一个函数，求两个整数之和，要求在函数体内不得使用 
//“+”、“-”、“*”、“/” 四则运算符号。
//使用二进制位运算进行加法求解，每一位用异或求解该位是0或1
//进位用与运算求解
class Solution {
public:
	int add(int a, int b) {
		int carry = 0;
		int sum = 0;//或者sum初始为a，return sum即可
		while (b != 0) {//直至无进位产生
			sum = a ^ b;//异或求无进位的和
			carry = (unsigned int)(a & b) << 1;//与运算后左移一位得进位的值
			a = sum;
			b = carry;
		}
		return a;//当b==0时，如果return sum则return 0
		
	}
};
int main()
{

	return 0;
}

