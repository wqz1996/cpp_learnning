#include <cstddef> // 使用处：第 9 行的 NULL
#include <cmath> // 使用处：第 28 行的 abs
using namespace std;
//面试题52. 两个链表的第一个公共节点
// 题目：输入两个链表，找出它们的第一个公共节点。
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
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
		//计算链表长度差
		cur1 = n > 0 ? headA : headB;//cur1指向长的链表
		cur2 = cur1 == headA ? headB : headA;//cur2指向另一个链表
		n = abs(n);
		while (n > 0) {//长的链表先走n步
			cur1 = cur1->next;
			n--;
		}
		while (cur1 != cur2) {//同时走直到相遇即为第一个公共节点
			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return cur1;

	}
};
int main()
{

	return 0;
}

