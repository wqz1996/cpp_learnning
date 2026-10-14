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



