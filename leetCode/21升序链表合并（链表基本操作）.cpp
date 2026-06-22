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

