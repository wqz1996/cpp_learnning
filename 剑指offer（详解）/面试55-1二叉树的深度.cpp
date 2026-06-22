#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
#include<vector>//不注重插入和删除效率
#include<list>//类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include<deque>//双端队列，兼顾随即存取，和两端数据的插入删除
#include<ctime>
#include< unordered_map>
#include< unordered_set>
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
using namespace std;
//面试题55 - I. 二叉树的深度
// 题目：输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节
//点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/************递归*******************/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int leftheight = maxDepth(root->left);
		int rightheight= maxDepth(root->right);
		return leftheight > rightheight ? leftheight + 1 : rightheight + 1;
	}
};
/*************深度优先遍历**************/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int leftdepth = maxDepth(root->left);
		int rightdepth = maxDepth(root->right);
		return max(leftdepth, rightdepth) + 1;
	}
};
/************广度优先遍历（层序遍历）*******************/
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == NULL)
			return 0;
		queue<TreeNode*> q;
		q.push(root);
		int res = 0;
		while (!q.empty()) {
			int size = q.size();
			for (int i = 0; i < size; i++) {
				TreeNode* node = q.front();
				q.pop();
				if (node->left != NULL)
					q.push(node->left);
				if (node->right != NULL)
					q.push(node->right);
			}
			res++;//遍历完一层后加1
		}
		return res;
	}
};

int main()
{
	return 0;
}

