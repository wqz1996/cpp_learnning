#include <cstddef> // 使用处：第 9 行的 NULL
using namespace std;
//面试题25. 合并两个排序的链表
// 题目：输入两个递增排序的链表，
//合并这两个链表并使新链表中的节点仍然是递增排序的。
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL)
			return l2;
		if (l2 == NULL)
			return l1;
		ListNode* dummyhead = new ListNode(-1);
		ListNode* cur = dummyhead;
		while (l1 != NULL && l2 != NULL) {
			if (l1->val <= l2->val) {
				cur->next = l1;
				cur = cur->next;
				l1 = l1->next;
			}
			else {
				cur->next = l2;
				cur = cur->next;
				l2 = l2->next;
			}
		}
		cur->next = l1 == NULL ? l2 : l1;
		return dummyhead->next;

	}
};
/*******************递归**************************/
class Solution1 {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (l1 == NULL)
			return l2;
		if (l2 == NULL)
			return l1;
		if (l1->val <= l2->val) {
			l1->next = mergeTwoLists(l1->next, l2);
			return l1;
		}
		else {
			l2->next = mergeTwoLists(l2->next, l1);
			return l2;
		}
	}
};
int main()
{

	return 0;
}

