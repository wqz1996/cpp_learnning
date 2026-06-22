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
//面试题44. 数字序列中某一位的数字
// 题目：数字以0123456789101112131415…的格式序列化到一个字符序列中。
//在这个序列中，第5位（从下标0开始计数）是5，第13位是1，第19位是4，等等。
//请写一个函数，求任意第n位对应的数字。
class Solution {
private:
	int countofIneget(int digit) {//返回digit位数的个数，如一位数10个，两位数90个
		if (digit == 1)
			return 10;
		int num = pow(10, digit-1);
		return 9 * num;
	}
	int digitAtIndex(int digit,int n) {//返回digit位数的个数，如一位数10个，两位数90个
		int num = beginofdigit(digit) + n / digit;//第n位是在num数字中的一位
		int restright =digit - n % digit;//从右向左移动
		for (int i = 1; i < restright; i++) {//移动restright-1位
			num /= 10;
		}
		return num % 10;//返回最后一位
	}
	int beginofdigit(int digit) {//返回digit位数开始数字，如两位数10开始
		if (digit == 1)
			return 0;
		return (int)pow(10, digit - 1);
	}
public:
	int findNthDigit(int n) {
		if (n < 0)
			return -1;
		int digit = 1;//几位数
		while (1) {
			int num=countofIneget(digit);
			if (n < (long)num * digit)//long防止乘法计算溢出
				return digitAtIndex(digit,n);
			n -= digit * num;//刨除不可能的位数
			digit++;//计算下一个位数是否成立
		}

	}
};
int main()
{

	return 0;
}

