#include <cstddef> // 使用处：第 8 行的 NULL
#include <iostream> // 使用处：第 24 行的 cout
using namespace std;
/************237删除链表中的节点*******************/
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
	void deleteNode(ListNode* node) {
		if (node == NULL)
			return;
		if (node->next == NULL) {
			delete node;
			node = NULL;
			return;
		}
		node->val = node->next->val;
		ListNode* delNode = node->next;
		node->next = delNode->next;
		delete delNode;
		return;

	}
};
int main() {
	int arr[] = { 1,2,3,4,5 };
	int len = sizeof(arr) / sizeof(int);
	int k = 0;
	ListNode* head = creatList(arr, len);
	printList(head);
	ListNode* delNode = head->next->next;
	Solution().deleteNode(delNode);
	printList(head);
	return 0;
}