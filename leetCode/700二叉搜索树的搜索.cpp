#include <cstddef> // 使用处：第 11 行的 NULL
using namespace std;
// 700. 二叉搜索树中的搜索
// 给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
// 你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 null 。
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
	TreeNode *searchBST(TreeNode *root, int val)
	{
		if (root == nullptr)
			return nullptr;

		if (root->val > val)
			return searchBST(root->left, val);
		if (root->val < val)
			return searchBST(root->right, val);
		return root;
	}
};
int main()
{

	return 0;
}
