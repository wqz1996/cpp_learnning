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
//面试题22.链表中倒数第k个节点
// 题目：输入一个链表，输出该链表中倒数第k个节点。为了符合大多数人的习惯，
//本题从1开始计数，即链表的尾节点是倒数第1个节点。
//例如，一个链表有6个节点，从头节点开始，
//它们的值依次是1、2、3、4、5、6。这个链表的倒数第3个节点是值为4的节点
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
/****************传统思路************************/
class Solution {
public:
	ListNode* getKthFromEnd(ListNode* head, int k) {
		if (head == NULL)
			return head;
		ListNode* cur = head;
		int count = 0;
		while (cur != NULL) {
			count++;
			cur = cur->next;
		}
		if (k > count)
			return NULL;
		cur = head;
		for (int i = 0; i < count - k ; i++) {
			cur = cur->next;
		}
		return cur;

	}
};
/****************只遍历一次************************/
class Solution {
public:
	ListNode* getKthFromEnd(ListNode* head, int k) {
		ListNode* p1 = head;
		ListNode* p2 = head;
		if (head == NULL || k == 0)//特判
			return NULL;
		for (int i = 0; i < k-1 ; i++) {//先让p2移动k-1位，p1和p2之间间距为k
			if (p2->next == NULL)//p2->next为空，说明k-1大于总长度
				return NULL;
			p2 = p2->next;//否则让p2继续移动
				
		}
		while (p2->next != NULL) {//k=1时，p1指向最后一个节点
			p1 = p1->next;//同时移动p1和p2
			p2 = p2->next;
		}
		return p1;

	}
};
int main()
{

	return 0;
}

