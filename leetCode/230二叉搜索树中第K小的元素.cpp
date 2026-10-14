#include <cstddef> // 使用处：第 10 行的 NULL
#include <stack> // 使用处：第 50 行的 stack
using namespace std;
// 230. 二叉搜索树中第K小的元素
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/************递归***********************/
class Solution
{
private:
	int rank = 0;
	int res;
	void traverse(TreeNode *root, int k)
	{
		if (root == nullptr)
			return;

		traverse(root->left, k);
		rank++;
		if (rank == k)
		{
			res = root->val;
			return;
		}

		traverse(root->right, k);
	}

public:
	int kthSmallest(TreeNode *root, int k)
	{
		traverse(root, k);
		return res;
	}
};
/**栈***/
class Solution
{
public:
	int kthSmallest(TreeNode *root, int k)
	{
		if (root == nullptr)
			return 0;
		int rank = 0;
		stack<TreeNode *> s;
		while (!s.empty() || root != nullptr)
		{
			while (root != nullptr)
			{
				s.push(root);
				root = root->left;
			}
			root = s.top();
			s.pop();

			rank++;
			if (rank == k)
				return root->val;

			root = root->right;
		}
		return root->val;
	}
};
int main()
{
	return 0;
}
