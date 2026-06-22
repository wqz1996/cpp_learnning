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
/************203移除链表元素*******************/
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};
ListNode* creatList(int arr[], int n) {
	if (n == 0)
		return NULL;
	ListNode* head = new ListNode(arr[0]);
	ListNode* cur = head;
	for (int i = 1; i < n; i++) {
		cur->next = new ListNode(arr[i]);
		cur = cur->next;
	}
	return head;
}
void printList(ListNode* head) {
	ListNode* cur = head;
	while (cur != NULL) {
		cout << cur->val << "->";
		cur = cur->next;
	}
	cout << "NULL" << endl;
}
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		if (head == NULL)//防止上个循环结束后head为空
			return NULL;
		while (head != NULL && head->val == val) {//保证head不为空的情况下循环
			//必须先判断head!=NULL，保证head不是空指针才能判断head->val
			ListNode* delNode = head;
			head = delNode->next;
			delete delNode;
		}
		if (head == NULL)//防止上个循环结束后head为空
			return NULL;
		ListNode* cur = head;
		while (cur->next != NULL) {
			if (cur->next->val == val) {//不是头节点的操作
				ListNode* delNode = cur->next;
				cur->next = delNode->next;
				delete delNode;
			}
			else
				cur = cur->next;
		}
		return head;

	}
	ListNode* removeElements1(ListNode* head, int val) {//虚拟头节点
		ListNode* dummyHead = new ListNode(0);//新建虚拟节点
		dummyHead->next = head;//指向头节点，将头节点作为普通节点进行处理

		ListNode* cur = dummyHead;
		while (cur->next != NULL) {
			if (cur->next->val == val) {//不是头节点的操作
				ListNode* delNode = cur->next;
				cur->next = delNode->next;
				delete delNode;
			}
			else
				cur = cur->next;
		}
		ListNode* retNode = dummyHead->next;
		delete dummyHead;
		return retNode;

	}

};
int main() {
	int arr[] = { 1 };
	int len = sizeof(arr) / sizeof(int);
	ListNode* head = creatList(arr, len);
	printList(head);
	ListNode* head2 = Solution().removeElements(head, 1);
	printList(head2);
	return 0;
}