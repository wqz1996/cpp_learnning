#include <vector> // vector：第 15 行首次使用
#include <cstddef> // NULL：第 10 行首次使用
using namespace std;
// 105 从前序与中序遍历序列构造二叉树
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution
{
public:
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
	{
		if (preorder.empty() || inorder.empty())
			return NULL;
		vector<int> left_pre, left_in, right_pre, right_in;
		int len = inorder.size();					// 记录树的总节点数
		int root = 0;								// 记录根节点索引位置
		TreeNode *head = new TreeNode(preorder[0]); // 先序遍历第一个元素为根节点
		while (inorder[root] != preorder[0])		// 找到中序遍历根节点位置
			root++;

		for (int i = 0; i < root; i++)
		{ // 记录左子树先序遍历和中序遍历的元素
			left_pre.push_back(preorder[i + 1]);
			left_in.push_back(inorder[i]);
		}
		for (int i = root + 1; i < len; i++)
		{ // 记录右子树先序遍历和中序遍历的元素
			right_pre.push_back(preorder[i]);
			right_in.push_back(inorder[i]);
		}
		// 先序遍历建立整棵树
		head->left = buildTree(left_pre, left_in);	  // 递归建立左子树
		head->right = buildTree(right_pre, right_in); // 建立右子树
		return head;
	}
};
int main()
{

	return 0;
}
