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
// 面试题6：从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。

/************在线IDE*****************/

struct ListNode {
	int val;
	struct ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		stack<int> s;
		ListNode* node;
		vector<int> array;
		node = head;
		while (node != NULL) {
			s.push(node->val);
			node = node->next;
		}
		while (!s.empty()) {
			array.push_back(s.top());
			s.pop();
		}
		return array;
	}
};
int main()
{
	
	return 0;

}



