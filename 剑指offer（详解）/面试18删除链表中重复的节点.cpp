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
// 面试题18：删除链表中重复的节点
// 题目：在一个排序的链表中，存在重复的结点，
//请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。
//例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};
ListNode* creat_node(int data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));//分配内存空间
	node->val = data;
	node->next = NULL;
	return node;
}
void Printlist(ListNode* node) {
	ListNode* head = node;
	if (head == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (head->next != NULL) {
		cout << head->val << "->";
		head = head->next;
	}
	cout << head->val << "->NULL" << endl;
}
class Solution {
public:
	ListNode* deleteDuplication(ListNode* pHead) {
		if (pHead == NULL || pHead->next == NULL)
			return pHead;
		ListNode* dummyhead = new ListNode(-1);
		dummyhead->next = pHead;
		ListNode* cur = pHead;
		ListNode* pre = dummyhead;
		while (cur!= NULL) {
			if (cur->next != NULL &&cur->next->val == cur->val) {//判断条件顺序不能颠倒
				cur = cur->next;
				while (cur->next != NULL && cur->next->val == cur->val)//找到cur的下一个节点不等于cur
					cur = cur->next;
				cur = cur->next;//cur指向第一个不等于cur的节点
				pre->next = cur;//链接pre和cur
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
		return dummyhead->next;

	}
};

int main()
{
	vector<int> arr{ 1,1,2,2,5,5 };
	ListNode* head = new ListNode(0);
	ListNode* cur = head;
	for (auto i : arr) {
		cur->next = creat_node(i);
		cur = cur->next;
	}
	Printlist(head->next);
	ListNode* newhead=Solution().deleteDuplication(head->next);
	Printlist(newhead);
	return 0;
}

