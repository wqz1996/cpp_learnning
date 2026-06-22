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
using namespace std;
// 面试题8：二叉树的下一个结点
// 题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
// 树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。
struct TreeLinkNode {
	int val;
	struct TreeLinkNode* left;
	struct TreeLinkNode* right;
	struct TreeLinkNode* next;//指向父节点的指针
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {

	}
};
class Solution {
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL) {
			return pNode;
		}
		TreeLinkNode* head = pNode;
		if (head->right != NULL) {//右子树不为空，则右子树最左的节点即为当前节点的后继
			head = head->right;
			while (head->left != NULL) {
				head = head->left;
			}
			return head;
		}
		else {//右子树为空，则以当前节点最为初始节点开始，向上找父节点，若当前节点是父节点的左孩子，则父节点是初始节点的后继
			TreeLinkNode* parent = head->next;
			while (parent != NULL && parent->left != head) {
				head = parent;
				parent = parent->next;

			}
			return parent;
		}

	}
};
int main()
{

	return 0;

}



