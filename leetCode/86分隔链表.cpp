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
/*************86分隔链表*****************************/
// 给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，
//使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
//你应当 保留 两个分区中每个节点的初始相对位置。
// 思路：
// 类似合并链表，这个就是拆成两个链表再将两个链表连到一起
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
	
};
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode* dummy1 = new ListNode(-1);
        ListNode* dummy2 = new ListNode(-1);
        ListNode* p1 = dummy1;
        ListNode* p2 = dummy2;
        ListNode* p = head;
        while (p != nullptr) {
            if (p->val < x) {
                p1->next = p;
                p1 = p1->next;
            } else {
                p2->next = p;
                p2 = p2->next;
            }
			//需要先将原链表断开在让p指针前进，避免出现环
            ListNode* temp = p->next;
            p->next = nullptr;
            p = temp;
        }
        p1->next = dummy2->next;
        return dummy1->next;
    }
};
int main()
{

	return 0;
}

