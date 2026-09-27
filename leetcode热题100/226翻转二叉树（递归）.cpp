#include <utility> // swap：Solution::invertTree 交换左右子树
#include <cstddef> // NULL：第 10 行首次使用
using namespace std;
/*************226翻转二叉树******************/

struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == NULL)
			return NULL;
		invertTree(root->left);
		invertTree(root->right);
		swap(root->left, root->right);
		return root;
	}
};
int main() {
	
	return 0;
} 