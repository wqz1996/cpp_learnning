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
/**********************234回文链表*************************/
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };
 ListNode* creat_node(int data) {
	 ListNode* node = (ListNode*)malloc(sizeof(ListNode));//分配内存空间
	 node->val = data;
	 node->next = NULL;
	 return node;
 }
 ListNode* reverseList(ListNode* head) {//链表逆序
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
 void Printlist(ListNode* node) {
	 ListNode* head = node;
	 if (head == NULL)
		 cout << "NULL" << endl;
	 while (head->next != NULL) {
		 cout << head->val << "->";
		 head = head->next;
	 }
	 cout << head->val <<"->NULL" <<endl;
 }
/****************空间复杂度O(1)****************************/
class Solution {
private:
	//反转链表
	ListNode* reserveList(ListNode* head) {
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
public:
	bool isPalindrome(ListNode* head) {
		if (head == NULL)//空链表认为是回文
			return true;
		ListNode* slow = head;
		ListNode* fast = head;
		//区别于另一种快慢指针找中点，该方法可以直接将slow指向靠前的中点
		while (fast->next != NULL && fast->next->next != NULL) {//找到中点
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode* firstend = slow;//奇数个节点时，中间节点归为第一段链表
		ListNode* secondbegin = reserveList(firstend->next);

		ListNode* p1 = head;
		ListNode* p2 = secondbegin;
		bool res = true;//保证返回之前将链表结构恢复
		while (p2 != NULL&&res) {//比较两段链表的值
			if (p1->val != p2->val)
				res = false;
			p1 = p1->next;
			p2 = p2->next;

		}
		firstend->next = reserveList(secondbegin);//将第一段与第二段的反转链表相连，恢复结构
		return true;//跳出循环则证明两段链表所有元素相同，是回文链表
	}
};
/*****************数组使用额外空间O(N)***********************/
class Solution1 {
public:
	bool isPalindrome(ListNode* head) {
		vector<int> arr;
		ListNode* cur = head;
		while (cur != NULL) {//将链表记录到数组中
			arr.push_back(cur->val);
			cur = cur->next;
		}
		int len = arr.size();
		int left = 0;
		int right = len - 1;
		while (left < right) {//双指针进行元素比较
			if (arr[left] != arr[right])
				return false;
			left++;
			right--;
		}
		return true;
	}
};
int main()
{
	vector<int> arr{ 1,2,2,1};
	ListNode* head = new ListNode(0);
	ListNode* cur = head;
	for (auto i : arr) {	
		cur->next=creat_node(i);
		cur = cur->next;
	}
	Printlist(head->next);
	cout<<Solution1().isPalindrome(head->next)<<endl;
	cout<<Solution().isPalindrome(head->next)<<endl;

	return 0;
}

