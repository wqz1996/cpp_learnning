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
// 面试题18：删除链表的节点
// 题目：给定单向链表的头指针和一个要删除的节点的值，
//定义一个函数删除该节点。
//返回删除后的链表的头节点。

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
}; 
class Solution {
public:
	ListNode* deleteNode(ListNode* head, int val) {
		if (head == NULL)
			return head;
		if (head->val == val) {//头节点的值就是待删除的值
			head = head->next;//头节点指向下一个节点即可
			return head;
		}
		ListNode* cur = head;
		ListNode* pre = head;
		while (cur->val != val) {
			if (cur == NULL)
				return head;
			pre = cur;//保存待删除节点的前一个节点
			cur = cur->next;
		}
		pre->next = cur->next;
		return head;

	}
};
/**************书中的方法，与本题有些不同*********************/
class Solution {
public:
	ListNode* deleteNode(ListNode* head, int val) {
		if (head == NULL)
			return head;
		if (head->val == val) {//头节点的值就是待删除的值
			head = head->next;//头节点指向下一个节点即可
			return head;
		}
		ListNode* cur = head;
		while (cur->val != val) {
			if (cur == NULL)
				return head;
			cur = cur->next;
		}
		if (cur->next != NULL) {//待删除节点不是最后一个节点
			//cur指向待删除的节点
			cur->val = cur->next->val;//将待删除的节点下一个节点的值复制到待删除节点
			cur->next = cur->next->next;
		}
		else {//待删除节点是最后一个节点
			ListNode* precur = head;
			while (precur->next != cur) {//从头节点遍历找到待删除节点的前一个节点
				precur = precur->next;
			}
			precur->next = cur->next;//待删除节点前一个指向待删除节点的下一个
		}
		
		return head;
	}
};

int main()
{

	return 0;
}

