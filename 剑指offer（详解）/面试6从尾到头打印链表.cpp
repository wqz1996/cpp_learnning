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
//面试6 从尾到头打印链表
//输入一个链表的头节点，从尾到头反过来返回每个节点的值（用数组返回）。
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	vector<int> reversePrint(ListNode* head) {
		vector<int> res;
		if (head == NULL)
			return res;
		stack<int> s;
		while (head != NULL) {//按顺序访问节点压栈
			s.push(head->val);
			head = head->next;
		}
		while (!s.empty()) {//弹出顺序与压入顺序反向
			res.push_back(s.top());
			s.pop();
		}
		return res;
	}
};
//递归写法
class Solution {
private:
	vector<int> res;
	void print(ListNode* head) {
		if (head->next == NULL) {//终止条件，head下一个为空
			res.push_back(head->val);
			return;
		}
		print(head->next);//访问到最后一个节点后返回保存
		res.push_back(head->val);
	}
public:
	vector<int> reversePrint(ListNode* head) {
		if (head == NULL)
			return res;
		print(head);
		return res;
	}
};
int main()
{

	return 0;
}

