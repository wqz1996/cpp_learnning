#include <cstddef> // 使用处：第 10 行的 NULL
using namespace std;
/****************938二叉搜索树的范围和***********************************/
// 给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。
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
	int rangeSumBST(TreeNode *root, int low, int high)
	{
		if (root == nullptr)
			return 0;

		if (root->val > high)
			return rangeSumBST(root->left, low, high);
		if (root->val < low)
			return rangeSumBST(root->right, low, high);

		return root->val + rangeSumBST(root->left, low, high) +
			   rangeSumBST(root->right, low, high);
	}
};
int main()
{

	return 0;
}
