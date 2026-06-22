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
/*************328奇偶链表*****************************/
//将奇数节点排在一起，偶数节点放在所有奇数节点后
//注：按照索引分奇偶，不按照节点的值
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
	
};
class Solution {
public:
	ListNode* oddEvenList(ListNode* head) {
		if (head == NULL||head->next == NULL)
			return head;

		ListNode* odd = head;
		ListNode* even = head->next;
		ListNode* evenhead = even;//保存第一个偶数节点，用于最后的连接
		while (even != NULL && even->next != NULL) {
			odd->next = even->next;//奇数节点链接偶数节点的下一个节点
			odd = odd->next;//更新奇数节点指针指向下一个奇数节点
			even->next = odd->next;//偶数节点链接奇数节点的下一个节点
			even = even->next;//更新偶数节点指针

		}
		odd->next = evenhead;//链接奇数节点与偶数节点
		return head;

	}
};

int main()
{

	return 0;
}

