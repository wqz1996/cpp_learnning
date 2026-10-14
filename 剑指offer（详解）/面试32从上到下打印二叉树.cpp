#include <cstddef> // 使用处：第 12 行的 NULL
#include <queue> // 使用处：第 21 行的 queue
#include <vector> // 使用处：第 17 行的 vector
using namespace std;
//面试题32 - I. 从上到下打印二叉树
// 题目：从上到下打印出二叉树的每个节点，
//同一层的节点按照从左到右的顺序打印。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<int> levelOrder(TreeNode* root) {//层序遍历
		vector<int> res;
		if (root == NULL)
			return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();
			res.push_back(node->val);
			if(node->left!=NULL)//空节点不进入队列
			q.push(node->left);//先进左孩子，再进右孩子
			if (node->right != NULL)
			q.push(node->right);
		}
		return res;

	}
};
int main()
{

	return 0;
}

