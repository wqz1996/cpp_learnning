#include <cstddef> // 使用处：第 13 行的 NULL
using namespace std;
//面试题68 - II. 二叉树的最近公共祖先
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
//最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽
//可能大（一个节点也可以是它自己的祖先）。”
//例如，给定如下二叉树 : root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL)
			return NULL;
		if (root == p || root == q)//找到p或q则将root其返回
			return root;
		TreeNode* left = lowestCommonAncestor(root->left, p, q);//左子树找p和q
		TreeNode* right= lowestCommonAncestor(root->right, p, q);//右子树找p和q
		if (left != NULL && right != NULL)//左右子树分别找到了p和q则返回根节点
			return root;
		return left != NULL ? left : right;//若左子树返回NULL则说明p，q都在右子树，若左子树返回不为空说明都在左子树上
	}
};
int main()
{

	return 0;
}

