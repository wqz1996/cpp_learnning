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
/*************23合并K个排序链表*****************************/
//给定数组nums，找出三个元素和为0，输出不重复的所有结果
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {//两个有序链表连接
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
	/********************递归过程***********************/
	ListNode* merge(vector<ListNode*>& lists, int L, int R) {
		if (L == R)//终止条件左右指针碰撞
			return lists[L];
		if (L > R)//防止边界溢出
			return NULL;
		int mid = L - (L - R) / 2;//防止加运算溢出
		return mergeTwoLists(merge(lists, L, mid), merge(lists, mid + 1, R));//左侧和右侧分别合并
	}
public:
	/****************顺序合并****************/
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* ans=NULL;
		int n = lists.size();
		for (int i = 0; i < n; i++) {
			ans = mergeTwoLists(ans, lists[i]);
		}
		return ans;
	}
	/****************递归合并****************/
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		return merge(lists, 0, lists.size() - 1);
	}
	/****************优先队列****************///????
	struct Status {
		int val;
		ListNode* ptr;
		bool operator < (const Status& rhs) const {
			return val > rhs.val;
		}
	};

	priority_queue <Status> q;

	ListNode* mergeKLists(vector<ListNode*> & lists) {
		for (auto node : lists) {
			if (node) q.push({ node->val, node });
		}
		ListNode* head;
		ListNode* tail = head;
		while (!q.empty()) {
			auto f = q.top(); q.pop();
			tail->next = f.ptr;
			tail = tail->next;
			if (f.ptr->next) q.push({ f.ptr->next->val, f.ptr->next });
		}
		return head->next;
	}

};
/*************************最优方法***********************************/
class Solution {
private:
	/***************两个有序链表合并********************/
	ListNode* mergeTwoList(ListNode* L1, ListNode* L2) {
		if (L1 == NULL)//L1空了返回L2剩余的部分
			return L2;
		if (L2 == NULL)//L2空了返回L1剩余部分
			return L1;
		if (L1->val <= L2->val) {
			L1->next = mergeTwoList(L1->next, L2);//L1的下一个节点是L1->next和L2的合并结果
			return L1;//返回较小的L1
		}
		else {
			L2->next = mergeTwoList(L2->next, L1);//L2的下一个节点是L2->next和L1的合并结果
			return L2;//返回较小的L1
		}
	}
	ListNode* merge(vector<ListNode*>& lists, int L, int R) {
		if (L == R)
			return lists[L];//递归终止，返回最后一个合并后的链表lists[L]或者lists[R]
		if (L > R)//防止越界
			return NULL;
		int mid = L - (L - R) / 2;//二分法
		return mergeTwoList(merge(lists, L, mid), merge(lists, mid + 1, R));//将左侧链表与右侧链表排序
	}
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0)
			return NULL;
		return merge(lists, 0, lists.size() - 1);
	}
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty())
            return nullptr;
        ListNode* dummy = new ListNode(-1);
        ListNode* p = dummy;

        priority_queue<ListNode*, vector<ListNode*>,
                       function<bool(ListNode*, ListNode*)>>
            pq([](ListNode* a, ListNode* b) { return a->val > b->val; });
        for (ListNode* head : lists) {
            if (head != nullptr)
                pq.push(head);
        }
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            p->next = node;
            if (node->next != nullptr) {
                pq.push(node->next);
            }
            p = p->next;
        }
        return dummy->next;
    }
};

int main()
{

	return 0;
}

