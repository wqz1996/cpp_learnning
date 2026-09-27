#include <iostream> // cout、endl：main 输出两种归并排序结果
#include <cstddef> // NULL：第 8 行首次使用
using namespace std;
/*************148排序链表*****************************/
 struct ListNode {
    int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 /**********时间复杂度O(N*logN)空间复杂度O(logN)******************************************/
class Solution {
private:
	/***************任意两个链表的归并排序****************************/
	ListNode* mergeTwoList(ListNode* L1, ListNode* L2) {
		//其中一个到了末尾后，返回另一个节点的指针
		if (L1 == NULL)
			return L2;
		if (L2 == NULL)
			return L1;
		if (L1->val < L2->val) {
			L1->next = mergeTwoList(L1->next, L2);//L1的下一个节点时L1->next与L2的排序结果
			return L1;
		}
		else {
			L2->next = mergeTwoList(L2->next, L1);
			return L2;
		}

	}
public:
	ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next == NULL)
			return head;
		ListNode* pre = head;
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast != NULL && fast->next != NULL) {//快指针到末尾时，慢指针在中点
			pre = slow;//保存慢指针上一个节点
			slow = slow->next;//慢指针
			fast = fast->next->next;//快指针
		}
		//从中点位置将链表切断head->O->O->NULL  slow->O->O->NULL
		pre->next = NULL;
		return mergeTwoList(sortList(head), sortList(slow));//递归完成所有排序过程
	}
};
/********************************************************/
class Solution1 {
private:
	/***************升序链表排序****************************/
	ListNode* mergeTwoList(ListNode* L1, ListNode* L2) {
		ListNode* dummyhead = new ListNode(-1);
		ListNode* cur = dummyhead;
		while (L1 != NULL && L2 != NULL) {
			if (L1->val <= L2->val) {
				cur->next = L1;
				L1 = L1->next;
			}
			else {
				cur->next = L2;
				L2 = L2->next;
			}
			cur = cur->next;
		}
		cur->next = L1 == NULL ? L2 : L1;
		return dummyhead->next;
	}
public:
	ListNode* sortList(ListNode* head) {
		if (head == NULL || head->next == NULL)
			return head;
		ListNode* pre = head;
		ListNode* slow = head;
		ListNode* fast = head;
		while (fast != NULL && fast->next != NULL) {//快慢指针寻找中点
			pre = slow;//跳出循环后保存slow前一个点
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = NULL;
		//将链表切到最小单元，反过来进行合并
		return mergeTwoList(sortList(head), sortList(slow));
	}
};
int main()
{
    ListNode a3(2), a2(1), a1(4);
    a1.next = &a2; a2.next = &a3;
    ListNode b3(2), b2(1), b1(4);
    b1.next = &b2; b2.next = &b3;
    for (ListNode* head : {Solution().sortList(&a1), Solution1().sortList(&b1)}) {
        for (ListNode* node = head; node != nullptr; node = node->next)
            cout << node->val << ' ';
        cout << endl;
    }
    return 0;
}
