#include <cstddef> // 使用处：第 13 行的 NULL
#include <stack> // 使用处：第 19 行的 stack
#include <vector> // 使用处：第 18 行的 vector
using namespace std;
// 面试题6：从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。

/************在线IDE*****************/

struct ListNode {
	int val;
	struct ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};

class Solution {
public:
	vector<int> printListFromTailToHead(ListNode* head) {
		stack<int> s;
		ListNode* node;
		vector<int> array;
		node = head;
		while (node != NULL) {
			s.push(node->val);
			node = node->next;
		}
		while (!s.empty()) {
			array.push_back(s.top());
			s.pop();
		}
		return array;
	}
};
int main()
{
	
	return 0;

}



