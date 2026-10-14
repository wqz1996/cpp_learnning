#include <cstddef> // 使用处：第 9 行的 NULL
using namespace std;
//面试题24. 反转链表
// 题目：定义一个函数，输入一个链表的头节点，
//反转该链表并输出反转后链表的头节点。
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
/****************传统思路************************/
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		if (head == NULL)
			return NULL;
		if (head->next == NULL)
			return head;
		ListNode* pre = NULL;
		ListNode* cur = head;
		while (cur != NULL) {
			ListNode* next = cur->next;
			cur->next = pre;
			pre = cur;
			cur = next;
		}
		return pre;
	}
};
int main()
{

	return 0;
}

