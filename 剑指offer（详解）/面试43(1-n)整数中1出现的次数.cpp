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
//面试题43. 1～n整数中1出现的次数
// 题目：输入一个整数 n ，求1～n这n个整数的十进制表示中1出现的次数。
//例如，输入12，1～12这些整数中包含1 的数字有1、10、11和12，1一共出现了5次。
class Solution {
public:
	int countDigitOne(int n) {
		long digit = 1;
		int res = 0;
		int high = n / 10;//取高位数字
		int cur = n % 10;//取当前位
		int low = 0;//取低位
		while (high != 0 || cur != 0) {
			if (cur == 0) {//当前为0，取决与高位
				res += high * digit;
			}
			else if(cur==1){//当前为为1，取决与高位+低位
				res += high * digit + low + 1;
			}
			else {//当前为大于1，取决与高位和当前位
				res += (high + 1) * digit;
			}
			low += cur * digit;
			cur = high % 10;
			high /= 10;
			digit *= 10;
		}
		return res;
	}
};
int main()
{

	return 0;
}

