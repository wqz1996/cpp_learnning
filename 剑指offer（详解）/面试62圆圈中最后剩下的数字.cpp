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
//面试题61. 扑克牌中的顺子
// 0,1,,n-1这n个数字排成一个圆圈，从数字0开始，每次从这个圆圈里删除第m个数
//字。求出这个圆圈里剩下的最后一个数字。
//例如，0、1、2、3、4这5个数字组成一个圆圈，从数字0开始每次删除第3个数字，
//则删除的前4个数字依次是2、0、4、1，因此最后剩下的数字是3。
/***********传统解法用环形链表模拟圆圈********************/
class Solution {
public:
	int lastRemaining(int n, int m) {
		list<int> crcle;
		for (int i = 0; i < n; i++)//将数据存入链表中
			crcle.push_back(i);
		list<int>::iterator cur=crcle.begin();//指向链表头节点
		while (crcle.size() > 1) {//多余一个元素时
			for (int i = 1; i < m; i++) {
				cur++;
				if (cur == crcle.end())//指向末尾后指向第一个节点
					cur = crcle.begin();
			}
			list<int>::iterator next = ++cur;//判断下一个节点是否到达尾节点
			if (next == crcle.end())//下一个节点为end则到末尾了，回到begin循环遍历
				next = crcle.begin();
			--cur;//返回待删除节点
			crcle.erase(cur);//删除节点
			cur = next;//

		}
		return *cur;
	}
};
//自己写的，LeetCode不能通过，复杂度过高
class Solution {
public:
	int lastRemaining(int n, int m) {
		list<int> crcle;
		for (int i = 0; i < n; i++) {
			crcle.push_back(i);//将0-n-1的值放在链表中
		}
		list<int>::iterator cur = crcle.begin();//cur指向第一个元素
		while (crcle.size() > 1) {//删除元素直至剩下一个
			for (int i = 0; i < m - 1; i++) {//cur已经指向第一个，再向后移动m-1即可
				cur = cur == (--crcle.end()) ? crcle.begin() : ++cur;//crcle.end()指向的是最后一个元素的下一个位置，因此需要--操作，当cur指向最后一个元素则返回开头实现循环链表结构
			}
			list<int>::iterator temp = cur;//缓存待删除的元素
			cur = cur == (--crcle.end()) ? crcle.begin() : ++cur;//cur指向待删除的下一个元素作为起始
			crcle.erase(temp);//删除待删除元素
		}
		return *cur;//返回最后剩下的一个元素
	}
};
/***********递归解决*******************/
class Solution {
public:
	int lastRemaining(int n, int m) {
		if (n == 1)
			return 0; 
		return (lastRemaining(n - 1, m) + m) % n;
	}
};
/***********循环*******************/
class Solution {
public:
	int lastRemaining(int n, int m) {
		int last = 0;
		for (int i = 2; i <= n; i++)
			last = (last + m) % i;
		return last;
	}
};
int main()
{

	return 0;
}

