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
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
 };
ListNode* creatlist(int val) {//新建一个值为val的节点
	ListNode* node = new ListNode(val);
	node->next = NULL;
	return node;
}
void printlist(ListNode* head) {//打印链表
	ListNode* node = head;
	if (node == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (node->next != NULL) {
		cout << node->val << "->";
		node = node->next;
	}
	cout << node->val << "->" << "NULL" << endl;

}
ListNode* getLoopNode(ListNode* head) {//找到链表的入环节点，无环链表返回NULL
	if (head == NULL || head->next == NULL || head->next->next == NULL)
		return NULL;
	ListNode* slow = head->next;
	ListNode* fast = head->next->next;
	while (slow != fast) {
		if (fast->next == NULL || fast->next->next == NULL)
			return NULL;
		slow = slow->next;
		fast = fast->next->next;
	}
	fast = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}
/*************无环链表相交问题*************/
ListNode* judgeNoloop(ListNode* headA,ListNode* headB) {
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
	cur1 = n > 0 ? headA : headB;
	cur2 = cur1 == headA ? headB : headA;
	n = abs(n);
	while (n != 0) {
		cur1 = cur1->next;
		n--;
	}
	while (cur1 != cur2) {
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return cur1;

}
/*************两个有环链表相交问题（有环和无环链表不能相交）*************/
ListNode* judgeBothloop(ListNode* headA, ListNode* headB) {
	if (headA->next == NULL || headB == NULL)
		return NULL;
	ListNode* loop1 = getLoopNode(headA);
	ListNode* loop2 = getLoopNode(headB);
	if (loop1 == loop2) {
		ListNode* cur1 = headA;
		ListNode* cur2 = headB;
		int n = 0;
		while (cur1 != loop1) {
			cur1 = cur1->next;
			n++;
		}
		while (cur2 != loop1) {
			cur2 = cur2->next;
			n--;
		}
		cur1 = n > 0 ? headA : headB;
		cur2 = cur1 == headA ? headB : headA;
		n = abs(n);
		while (n != 0) {
			cur1 = cur1->next;
			n--;
		}
		while (cur1 != cur2) {
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;
	}
	else {
		ListNode* cur1 = loop1->next;
		while (cur1 != loop1) {
			if (cur1 == loop2)
				return loop1;
			cur1 = cur1->next;
		}
		return NULL;
	}
}
ListNode* getintersectNode(ListNode* headA, ListNode* headB) {
	if (headA == NULL || headB == NULL)
		return NULL;
	ListNode* loop1 = getLoopNode(headA);
	ListNode* loop2 = getLoopNode(headB);
	if (loop1 == NULL && loop2 == NULL)
		return judgeNoloop(headA, headB);
	if (loop1 != NULL && loop2 != NULL)
		return judgeBothloop(headA, headB);
	return NULL;
}
int main()
{
	vector<int> arr{ 1,2,3,4,5 };
	ListNode* head = new ListNode(-1);
	ListNode* cur = head;
	for (int i = 0; i < arr.size(); i++) {
		cur->next = creatlist(arr[i]);
		cur = cur->next;
	}
	
	
	return 0;
}

