#include <cstddef> // NULL：第 18 行首次使用
using namespace std;
/*************21合并两个有序链表*****************************/
//将两个升序链表合成一个新的升序链表
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		ListNode* newhead = new ListNode(-1);
		ListNode* prev = newhead;
		while (l1 != NULL && l2 != NULL) {
			if (l1->val <= l2->val) {
				prev->next = l1;
				l1 = l1->next;
			}
			else {
				prev->next = l2;
				l2 = l2->next;

			}
			prev = prev->next;
		}
		prev->next = l1 == NULL ? l2 : l1;
		return newhead->next;
		

	}
};
int main()
{

	return 0;
}

