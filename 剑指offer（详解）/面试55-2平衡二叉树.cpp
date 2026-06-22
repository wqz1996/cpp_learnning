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
/***************简单解法**************************/
class Solution {
private:
	int getheight(TreeNode* root) {
		if (root == NULL)
			return 0;
		queue<TreeNode*> q;
		q.push(root);
		int height = 0;
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
			height++;
		}
		return height;
	}
public:
	bool isBalanced(TreeNode* root) {
		if (root == NULL)
			return true;
		int leftheight = getheight(root->left);//获取左树高度
		int rightheight = getheight(root->right);//右树高度
		int diff = leftheight - rightheight;//高度差
		if (abs(diff) > 1)
			return false;
		return isBalanced(root->left) && isBalanced(root->right);//左右子树均是平衡二叉树则为真
	}
};
/***************后序遍历**************************/
//在遍历根节点之前已经遍历左右子树
class Solution {
private:
	bool judgebalancetree(TreeNode* root, int& depth) {//加&改变变量值
		if (root == NULL) {//终止条件
			depth = 0;
			return true;
		}
		int left = 0, right = 0;
		if (judgebalancetree(root->left, left) && judgebalancetree(root->right, right)) {//左右子树都是平衡二叉树继续计算
			int diff = left - right;
			if (abs(diff) <= 1) {
				depth = 1 + (left > right ? left : right);//取较大的高度+1
				return true;
			}
		}
		return false;//其中一个不是平衡二叉树直接返回false
			
	}
public:
	bool isBalanced(TreeNode* root) {
		if (root == NULL)
			return true;
		int depth = 0;
		return judgebalancetree(root, depth);
	}
};
/*********************/
class Solution {
private:
	int depth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int leftdepth = depth(root->left);
		int rightdepth = depth(root->right);
		if ((leftdepth == -1) || rightdepth == -1)
			return -1;
		return abs(leftdepth - rightdepth) > 1 ? -1 : max(leftdepth, rightdepth) + 1;
	}
public:
	bool isBalanced(TreeNode* root) {
		return depth(root) != -1;
	}
};
int main()
{
	return 0;
}

