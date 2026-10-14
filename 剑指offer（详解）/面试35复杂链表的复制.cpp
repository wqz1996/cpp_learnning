#include <cstddef> // 使用处：第 17 行的 NULL
#include <vector> // 使用处：第 46 行的 vector
#include <unordered_map> // 使用处：第 27 行的 unordered_map
using namespace std;
//面试题35. 复杂链表的复制
// 题目：请实现 copyRandomList 函数，复制一个复杂链表。
//在复杂链表中，每个节点除了有一个 next 指针指向下一
//个节点，还有一个 random 指针指向链表中的任意节点或者 null。
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (head == NULL)
			return NULL;
		unordered_map<Node*, Node*> nodemap;
		Node* cur = head;
		while (cur != NULL) {//将所有节点拷贝到value中
			nodemap[cur] = new Node(cur->val);//map的value为拷贝节点
			cur = cur->next;
		}
		cur = head;//从头开始遍历
		while (cur != NULL) {
			//拷贝节点的next节点是key->next节点对应的拷贝节点
			nodemap[cur]->next = nodemap[cur->next];
			//同理连接random指针
			nodemap[cur]->random= nodemap[cur->random];
			cur = cur->next;
		}
		return nodemap[head];//返回拷贝的头节点
	}
};
int main()
{
	vector<int> data = { 1,3,2,6,5 };

	return 0;
}

