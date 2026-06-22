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
//输入一个单向链表和一个节点的值，从单向链表中删除等于该值的节点，删除后如果链表中无节点则返回空指针。
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() :next(NULL) {}
	ListNode(int x) :val(x),next(NULL) {}
};
int main() {
	int n, head_value;
	while (cin >> n >> head_value) {
		ListNode* p, * q, * head = new ListNode(head_value);
		q = head;
		for (int i = 0; i < n - 1; i++) {
			int x, y;
			cin >> x >> y;
			p = new ListNode(x);
			while (q) {
				if (q->val == y) {
					p->next = q->next;
					q->next = p;
					break;
				}
				else
					q = q->next;
			}
			q = head;
		}
		int denum;
		cin >> denum;
		ListNode* dummyhead = new ListNode(0);
		dummyhead->next = head;
		ListNode* pre = dummyhead;
		ListNode* cur = head;
		while (cur != NULL) {
			if (cur->val == denum) {
				pre->next = cur->next;
				delete cur;
				break;
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
		cur = dummyhead->next;
		while (cur) {
			cout << cur->val << ' ';
			cur = cur->next;
		}
		cout << endl;
	}
	return 0;
}
/*int main() {
	int n;
	int headval;
	int delnode;
	int node1, node2;
	while (cin >> n >> headval) {
		ListNode* head = new ListNode(headval);
		ListNode* q = new ListNode();
		ListNode* p = new ListNode();
		q = head;
		for (int i = 0; i < n - 1; i++) {
			cin >> node1 >> node2;
			p = new ListNode(node1);
			while (q != NULL) {
				if (q->val == node2) {
					p->next = q->next;
					q->next = p;
					break;
				}
				q = q->next;
			}
			q = head;
		}
		cin >> delnode;
		ListNode* dummyhead = new ListNode(0);
		dummyhead->next = head;
		ListNode* pre = dummyhead;
		ListNode* cur = head;
		while (cur != NULL) {
			if (cur->val == delnode) {
				pre->next = cur->next;
				delete cur;
				break;
			}
			else {
				pre = cur;
				cur = cur->next;
			}		
		}
		cur = dummyhead->next;
		while (cur != NULL) {
			cout << cur->val << ' ';
			cur = cur->next;
		}
		cout<<endl;
	}



	return 0;
}*/

