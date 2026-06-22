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
//输入一个单向链表，输出该链表中倒数第k个结点，链表的倒数第1个结点为链表的尾指针。
struct ListNode {
	int val;
	ListNode* next;
	ListNode():next(NULL) {};
	ListNode(int x) :val(x), next(NULL) {}
};
ListNode* creatNode(int val) {
	ListNode* node = new ListNode(val);
	return node;
}
ListNode* FindKthtoTail(ListNode* head, int k) {
	if (head == NULL)
		return NULL;
	if (k == 0)
		return NULL;
	ListNode* p1 = head;
	ListNode* p2 = head;
	for (int i = 0; i < k - 1; i++) {
		if (p1->next == NULL)
			return NULL;
		p1 = p1->next;
	}
	while (p1->next != NULL) {
		p1 = p1->next;
		p2 = p2->next;
	}
	return p2;
}
int main() {
	int n;
	while (cin >> n) {
		ListNode* head = new ListNode();
		ListNode* cur = head;
		int val;
		for (int i = 0; i < n; i++) {
			cin >> val;
			cur->next = creatNode(val);
			cur = cur->next;
		}
		head = head->next;
		int k;
		cin >> k;
		cur = FindKthtoTail(head, k);
		if (cur == NULL)
			cout << 0 << endl;
		else
			cout << cur->val << endl;
	
	}
	return 0;
}
