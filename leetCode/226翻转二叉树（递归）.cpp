#include <cstddef> // 使用处：第 10 行的 NULL
#include <algorithm> // 使用处：第 19 行的 swap(
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