#include <cstddef> // 使用处：第 13 行的 NULL
using namespace std;
//面试题68 - I. 二叉搜索树的最近公共祖先
// 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
//最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度
//尽可能大（一个节点也可以是它自己的祖先）。”
//例如，给定如下二叉搜索树 : root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5]
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL||(root->left==NULL&&root->right==NULL))
			return NULL;
		TreeNode* cur = root;
		while (cur != NULL) {
			if (cur->val < p->val && cur->val < q->val)//当前节点小于两个节点则向右子树搜索
				cur = cur->right;
			else if (cur->val > p->val&& cur->val > q->val)//当前节点大于两个节点则向左子树搜索
				cur = cur->left;
			else
				break;
		}		
		return cur;
	}
};
int main()
{

	return 0;
}

