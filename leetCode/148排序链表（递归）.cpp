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

	return 0;
}

