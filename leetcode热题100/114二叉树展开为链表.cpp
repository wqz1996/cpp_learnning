#include <cstddef> // NULL：第 16 行首次使用
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	void flatten(TreeNode* root) {
		while (root != NULL) {//
			if (root->left != NULL) {//root不是叶子节点则继续
				TreeNode* node = root->left;
				while (node->right != NULL)//找到左子树最右节点
					node = node->right;
				node->right = root->right;//左子树最右节点的右指针指向root的右孩子
				root->right = root->left;//释放root右指针
				root->left = NULL;

			}
			root = root->right;//root左指针被右指针代替，因此用右指针遍历
		}
	}
};
int main()
{


	return 0;
}

