#include <cstddef> // 使用处：第 11 行的 NULL
using namespace std;
// 面试题8：二叉树的下一个结点
// 题目：给定一棵二叉树和其中的一个结点，如何找出中序遍历顺序的下一个结点？
// 树中的结点除了有两个分别指向左右子结点的指针以外，还有一个指向父结点的指针。
struct TreeLinkNode {
	int val;
	struct TreeLinkNode* left;
	struct TreeLinkNode* right;
	struct TreeLinkNode* next;//指向父节点的指针
	TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {}
};
class Solution {
public:
	TreeLinkNode* GetNext(TreeLinkNode* pNode)
	{
		if (pNode == NULL)
			return pNode;//当前节点为NULL则返回NULL

		TreeLinkNode* head = pNode;
		if (head->right != NULL) {//右孩子不为NULL则后继节点为右孩子最左的节点
			head = head->right;//从右孩子的根节点开始找
			while (head->left != NULL)//找到最左的节点
				head = head->left;
			return head;
		}
		else {//右孩子为NULL，则向上找父节点，直到当前节点是父节点的左孩子，则返回父节点
			TreeLinkNode* parent = head->next;//父节点
			while (parent != NULL && parent->left != head) {//父节点为NULL则说明当前节点是整棵树的根节点
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

