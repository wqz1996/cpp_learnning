#include <iostream> // cout, endl：第 24 行首次使用
#include <cstddef> // NULL：第 8 行首次使用
using namespace std;
/************206反转链表*******************/
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
		cur->next = new ListNode(arr[i]);//创建新节点
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
void deletelist(ListNode* head) {
	ListNode* cur = head;
	while (cur != NULL) {
		ListNode* deleteNode = cur;
		cur = cur->next;
		delete deleteNode;

	}

}
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* pre = NULL;
		ListNode* cur = head;
		while (cur != NULL) {

			ListNode* next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;

		}
		head = pre;
		return head;

	}
};
int main() {
	int arr[] = { 1,2,3,4,5 };
	int len = sizeof(arr) / sizeof(int);
	ListNode* head = creatList(arr, len);
	printList(head);
	ListNode* head2 = Solution().reverseList(head);
	printList(head2);
	deletelist(head2);
	return 0;
}