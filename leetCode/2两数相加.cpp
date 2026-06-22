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
/*************2两数相加*****************************/
//链表处理
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
	
};
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* dummyhead = new ListNode(0);//创建虚拟头节点
		ListNode* p = l1, * q = l2, * cur = dummyhead;
		int carry = 0;//进位 0/1
		while (p != NULL || q != NULL) {//
			int x = (p != NULL) ? p->val : 0;//若为空了以后创建数值为0的节点
			int y = (q != NULL) ? q->val : 0;
			int sum = carry + x + y;
			carry = sum / 10;
			cur->next = new ListNode(sum % 10);
			cur = cur->next;
			p = (p != NULL) ? p->next : p;
			q = (q != NULL) ? q->next : q;

		}
		if (carry > 0)//若到长链表结束后仍存在进位，则需创建一位
			cur->next = new ListNode(carry);
		return dummyhead->next;
	}
};
int main()
{

	return 0;
}

