#include <cstddef> // 使用处：第 11 行的 NULL
#include <stack> // 使用处：第 37 行的 stack
#include <vector> // 使用处：第 16 行的 vector
using namespace std;
//面试题54. 二叉搜索树的第k大节点
// 题目：给定一棵二叉搜索树，请找出其中第k大的节点。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/************递归***********************/
class Solution {
private:
	vector<int> res;
	void findkthnode(TreeNode* root) {
		if (root == NULL)
			return;
		findkthnode(root->right);
		res.push_back(root->val);
		findkthnode(root->left);

	}

public:
	int kthLargest(TreeNode* root, int k) {
		findkthnode(root);
		return res[k-1];

	}
};
/*****************栈*****************/
class Solution {
public:
	int kthLargest(TreeNode* root, int k) {
		stack<TreeNode*> s;
		TreeNode* cur = root;
		while (cur != NULL || !s.empty()) {//右中左顺序进行遍历
			while (cur != NULL) {//将右子树全部压入
				s.push(cur);
				cur = cur->right;
			}
			cur = s.top();
			s.pop();
			if (--k == 0)
				return cur->val;
			cur = cur->left;
		}
		return root->val;

	}
};
/*********反序中序遍历，右中左*******************/
class Solution {
public:
	int kthLargest(TreeNode* root, int k) {
		if (root == NULL)
			return NULL;
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty() || root != NULL) {
			if (root != NULL) {
				s.push(root);
				root = root->right;
			}
			else {
				root = s.top();
				s.pop();
				if (--k == 0)
					return root->val;
				root = root->left;
			}

		}
		return root->val;
	}
};
int main()
{
	return 0;
}

