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
/************24两两交换链表中的节点*******************/
 struct ListNode {
      int val;
      ListNode *next;
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
	 ListNode* swapPairs(ListNode* head) {
		 ListNode* dummyhead = new ListNode(0);
		 dummyhead->next = head;//虚拟头节点。指向head
		 ListNode* p = dummyhead;
		 while (p->next && p->next->next) {
			 ListNode* node1 = p->next;
			 ListNode* node2 = node1->next;
			 ListNode* next = node2->next;
			 node2->next = node1;
			 node1->next = next;
			 p->next = node2;
			 p = node1;

		 }
		 ListNode* retNode = dummyhead->next;
		 delete dummyhead;
		 return retNode;
	 }
 };
int main() {
	int arr[] = { 1,2,3,4,5 };
	int len = sizeof(arr) / sizeof(int);
	ListNode* head = creatList(arr, len);
	printList(head);
	ListNode* head2 = Solution().swapPairs(head);
	printList(head2);
	return 0;
} 