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
//面试题23.链表中环的入口节点
// 题目：给一个链表，若其中包含环，
//请找出该链表的环的入口结点，否则，输出null。

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};
/********************更易理解********************/
class Solution {
public:
	ListNode* EntryNodeOfLoop(ListNode* pHead) {
		ListNode* slow = pHead;//slow和fast同时从头节点出发
		ListNode* fast = pHead;
		while (fast != NULL && fast->next != NULL) {//保证fast和fast->next不为空
			slow = slow->next;
			fast = fast->next->next;
			if (slow == fast)
				break;
		}
		if (fast == NULL || fast->next == NULL)//判断跳出原因，因为初始化slow和fast相等，因此slow==fast不一定是while中实现的，不能用slow!=fast判断！！！
			return NULL;
		fast = pHead;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return fast;
	}
};
class Solution {
public:
	ListNode* EntryNodeOfLoop(ListNode* pHead) {
		if (pHead == NULL||pHead->next==NULL||pHead->next->next==NULL)
			return NULL;
		ListNode* slow = pHead->next;//slow指向第二个节点
		ListNode* fast = pHead->next->next;//fast指向第三个节点
		while (slow!=fast) {//快慢指针相遇
			if (fast->next == NULL || fast->next->next == NULL)
				return NULL;
			slow = slow->next;
			fast = fast->next->next;
		}
		fast = pHead;//快指针回到头节点
		while (fast != slow) {//两个指针一次只走一步，相遇的点即为入口节点
			fast = fast->next;
			slow = slow->next;
		}
		return fast;

	}
};
int main()
{

	return 0;
}

