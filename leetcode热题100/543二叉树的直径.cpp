#include <algorithm> // 使用处：第 23 行的 max(
#include <cstddef> // 使用处：第 11 行的 NULL
using namespace std;
/**********************532二叉树直径*************************/
//给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意
//两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

class Solution {
private:
	int res;
	int depth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int left = depth(root->left);//左树最大深度
		int right = depth(root->right);//右树最大深度
		res = max(res, left + right + 1);
		return max(left, right) + 1;
	}
public:
	int diameterOfBinaryTree(TreeNode* root) {
		res = 1;
		depth(root);
		return res-1;
	}
};
int main()
{

	return 0;
}

