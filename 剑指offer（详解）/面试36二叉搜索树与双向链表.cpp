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
//面试题36. 二叉搜索树与双向链表
// 题目：输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。
//要求不能创建任何新的节点，只能调整树中节点指针的指向。

//注：我们希望将这个二叉搜索树转化为双向循环链表。
//链表中的每个节点都有一个前驱和后继指针。
//对于双向循环链表，第一个节点的前驱是最后一个节点，
//最后一个节点的后继是第一个节点。
class Node {
public:
	int val;
	Node* left;
	Node* right;

	Node() {}

	Node(int _val) {
		val = _val;
		left = NULL;
		right = NULL;
	}

	Node(int _val, Node* _left, Node* _right) {
		val = _val;
		left = _left;
		right = _right;
	}
};
class Solution {
private:
	Node* pre, * cur;//cur当前结点，pre上次访问的节点
	void TransTreeToList(Node* root) {//中序遍历得到搜索二叉树的排序序列
		if (root == NULL)
			return;
		TransTreeToList(root->left);
		cur = root;//cur为当前访问的节点
		pre->right = cur;//连接上次访问的节点和当前节点的左右指针，右指针指向后继，左指针指向前驱
		cur->left = pre;
		pre = cur;//更新访问的节点
		TransTreeToList(root->right);

	}
public:
	Node* treeToDoublyList(Node* root) {
		if (root == NULL)
			return NULL;
		Node* dummyhead = new Node();//虚拟头节点
		pre = dummyhead;
		TransTreeToList(root);//中序遍历连接每个节点
		//运行上个函数后，cur为最后一个节点
		dummyhead->right->left = cur;//dummyhead->right为真实开头的节点，头节点的前驱是尾节点
		cur->right = dummyhead->right;//尾节点的后继是链表头节点
		return dummyhead->right;
	}
};

class Solution {
private:
	void listTree(Node* root, Node*& head, Node*& tail) {
		if (root == NULL)
			return;
		Node* Lhead, * Ltail, * Rhead, * Rtail;
		Lhead = root;
		if (root->left != NULL) {
			listTree(root->left, Lhead, Ltail);
			root->left = Ltail;
			Ltail->right = root;
		}
		Rtail = root;
		if (root->right != NULL) {
			listTree(root->right, Rhead, Rtail);
			root->right = Rhead;
			Rhead->left = root;
		}
		head = Lhead;
		tail = Rtail;
	}
public:
	Node* treeToDoublyList(Node* root) {
		if (root == NULL)
			return NULL;
		Node* head;
		Node* tail;
		listTree(root, head, tail);
		head->left = tail;
		tail->right = head;
		return head;

	}
};
int main()
{
	vector<int> data = { 1,3,2,6,5 };

	return 0;
}

