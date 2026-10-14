#include <cstddef> // 使用处：第 11 行的 NULL
#include <queue> // 使用处：第 39 行的 queue
using namespace std;
//面试题28. 对称的二叉树
// 题目：请实现一个函数，用来判断一棵二叉树是不是对称的。
//如果一棵二叉树和它的镜像一样，那么它是对称的。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/********************递归*********************/
class Solution {
private:
	bool isSymTree(TreeNode* left, TreeNode* right) {
		if (left == NULL && right == NULL)//递归终止条件，左右子树同时为空
			return true;
		if (left == NULL || right == NULL)//根据上一条语句，则只有一个为空
			return false;
		if (left->val != right->val)
			return false;
		//两个节点的左子树等于另一个的右子树，右子树等于另一个的左子树
		return isSymTree(left->left, right->right) && isSymTree(left->right, right->left);
	}
public:
	bool isSymmetric(TreeNode* root) {
		if (root == NULL)//定义空树是对称二叉树
			return true;
		return isSymTree(root, root);
	}
};
/********************队列模拟广度优先遍历*********************/
class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		if (root == NULL)//定义空树是对称二叉树
			return true;
		queue<TreeNode*> q;
		q.push(root->left);//分别压入左右孩子
		q.push(root->right);
		while (!q.empty()) {
			TreeNode* left = q.front();//取出队首两个节点进行判断
			q.pop();
			TreeNode* right = q.front();
			q.pop();
			if (left == NULL && right == NULL)//都为空进行下一次循环
				continue;
			if (left == NULL || right == NULL)
				return false;
			if (left->val != right->val)
				return false;

			q.push(left->right);//将左子树的右孩子，右子树的左孩子放入队列
			q.push(right->left);
			//上下两对可以交换顺序
			q.push(left->left);//将左子树的左孩子， 右子树的右孩子放入队列
			q.push(right->right);
		}
		return true;
	}
};
int main()
{

	return 0;
}

