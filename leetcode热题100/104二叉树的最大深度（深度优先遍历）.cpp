#include <algorithm> // 使用处：第 21 行的 max(
#include <cstddef> // 使用处：第 10 行的 NULL
using namespace std;
/*************104二叉树的最大深度******************/

struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL)
			return 0;

		int leftdepth = maxDepth(root->left);
		int rightdepth = maxDepth(root->right);

		return max(leftdepth, rightdepth)+1;

	}
};
int main() {
	
	return 0;
} 