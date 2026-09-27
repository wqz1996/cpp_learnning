#include <cstddef> // NULL：第 9 行首次使用
using namespace std;
/****************101对称二叉树***********************************/

  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  };

class Solution {
private:
	bool isSymTree(TreeNode* left,TreeNode* right) {
		if (left == NULL && right == NULL)//左右指针同时到达叶子结点，则是对称二叉树
			return true;
		if (left == NULL || right == NULL)//除去两个指针都为NULL以外，其中一个先到叶子结点，则不是对称二叉树
			return false;
		//左右两个指针的值相同，并且左指针向左则右指针向右，左指针向右，右指针向左。
		return left->val == right->val && isSymTree(left->left, right->right) && isSymTree(left->right, right->left);
	}
public:
	bool isSymmetric(TreeNode* root) {
		if (root == NULL)
			return true;

		return isSymTree(root,root);
	}
};
int main()
{
	

	return 0;
}

