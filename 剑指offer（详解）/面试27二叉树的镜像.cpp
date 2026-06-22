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
//面试题27. 二叉树的镜像
// 题目：请完成一个函数，输入一个二叉树，该函数输出它的镜像。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {
		if (root == NULL)//当前节点为空返回NULL
			return NULL;
		if (root->left != NULL || root->right != NULL) {//其中一个不为空继续递归
			swap(root->left, root->right);//交换左右子树
			mirrorTree(root->left);//以左孩子为根递归交换
			mirrorTree(root->right);//以右孩子为根递归交换
		}
		return root;
	}
};
/*************简洁递归******************/
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {
		if (root == NULL)
			return NULL;
		mirrorTree(root->left);
		mirrorTree(root->right);
		swap(root->left, root->right);
		return root;
	}
};
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {//先序遍历交换节点
		if (root == NULL)
			return root;

		swap(root->left, root->right);
		if (root->left != NULL)
			mirrorTree(root->left);
		if (root->right != NULL)
			mirrorTree(root->right);

		return root;
	}
};
/***************栈模拟先序遍历（深度优先）***********************/
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty()) {
			TreeNode* node = s.top();//取栈顶节点
			s.pop();
			if (node == NULL)//为空直接进行下一次循环
				continue;
			swap(node->left, node->right);//交换栈顶节点的左右子树
			s.push(node->right);//弹出右子树后再弹出右子树的右子树，深度优先
			s.push(node->left);
		}
		return root;
	}
};
/***************队列模拟层序遍历（广度优先）***********************/
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();
			if (node == NULL)
				continue;
			swap(node->left, node->right);
			q.push(node->left);//按层弹出，先弹出第一层左子树，再弹出第一层右子树
			q.push(node->right);

		}
		return root;
	}
};
/******自写*********/
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {
		if (root == NULL)
			return NULL;
		swap(root->left, root->right);
		if (root->left != NULL)
			mirrorTree(root->left);
		if (root->right != NULL)
			mirrorTree(root->right);
		return root;
	}
};
int main()
{

	return 0;
}

