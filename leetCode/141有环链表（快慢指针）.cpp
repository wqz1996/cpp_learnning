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
/*************141环形链表*****************************/
//判断有环无环
//使用快慢指针
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};
class Solution {
public:
	bool hasCycle(ListNode* head) {
		if (head==NULL||head->next == NULL)
			return false;
		ListNode* slow =head;//给定快慢指针的初始点不同
		ListNode* fast = head->next;
		while (slow != fast) {//快慢指针不相遇则继续
			if (fast == NULL || fast->next == NULL)//快指针遇到NULL则说明无环
				return false;
			slow = slow->next;
			fast = fast->next->next;
		}
		return true;//跳出循环，快慢指针相遇则有环
	}
};
/********************哈希表*********************/
class Solution {
public:
	bool hasCycle(ListNode* head) {
		unordered_set<ListNode*> nodeset;//用于存储当前节点
		while (head != NULL) {//没遇到NULL则循环
			if (nodeset.find(head) != nodeset.end())//找到了相同的节点则有环
				return true;
			else//未找到将当前节点放入哈希表中
				nodeset.insert(head);
			head = head->next;//判断下一个节点
		}
		return false;//遇到NULL则无环
	}
};

int main()
{

	return 0;
}

