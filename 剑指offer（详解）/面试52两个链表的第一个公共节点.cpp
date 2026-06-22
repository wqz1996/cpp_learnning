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
//面试题52. 两个链表的第一个公共节点
// 题目：输入两个链表，找出它们的第一个公共节点。
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		ListNode* cur1 = headA;
		ListNode* cur2 = headB;
		int n = 0;
		while (cur1 != NULL) {
			cur1 = cur1->next;
			n++;
		}
		while (cur2 != NULL) {
			cur2 = cur2->next;
			n--;
		}
		//计算链表长度差
		cur1 = n > 0 ? headA : headB;//cur1指向长的链表
		cur2 = cur1 == headA ? headB : headA;//cur2指向另一个链表
		n = abs(n);
		while (n > 0) {//长的链表先走n步
			cur1 = cur1->next;
			n--;
		}
		while (cur1 != cur2) {//同时走直到相遇即为第一个公共节点
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;

	}
};
int main()
{

	return 0;
}

