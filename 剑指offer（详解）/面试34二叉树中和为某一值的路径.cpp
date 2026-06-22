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
//面试题34. 二叉树中和为某一值的路径
// 题目：输入一棵二叉树和一个整数，打印出二叉树中节点值的和
//为输入整数的所有路径。从树的根节点开始往下一直到叶节点所
//经过的节点形成一条路径。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*******************************************************/
class Solution {
private:
	vector<vector<int>> res;
	vector<int> temp;
	void caculatesum(TreeNode* root, int sum) {
		temp.push_back(root->val);//将当前节点加入到路径中
		if (sum==root->val && root->left == NULL && root->right == NULL) {
			res.push_back(temp);//当前和等于当前节点的值，并且是叶子节点，则记录一整个路径
		}
		if (root->left != NULL)//先序遍历
			caculatesum(root->left, sum-root->val);
		if (root->right != NULL)
			caculatesum(root->right, sum-root->val);
		//运行到最后自带return
		temp.pop_back();//叶子节点并且剩余和不等于当前节点值，返回上一层
	}
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		if (root == NULL)
			return res;
		 caculatesum(root, sum);
		 return res;
	}
};
/***********************更易理解********************************/
class Solution {
private:
	vector<vector<int>> res;
	vector<int> temp;
	void isSum(TreeNode* root, int sum) {
		//递归终止条件，当前节点等于sum剩余值。并且当前节点是叶子节点
		if (sum == root->val && root->left == NULL && root->right == NULL) {
			temp.push_back(root->val);//将当前节点放入路径中
			res.push_back(temp);//记录路径结果
			temp.pop_back();//回溯
			return;
		}
		temp.push_back(root->val);//将当前节点放入路径

		if (root->left != NULL)
			isSum(root->left, sum - root->val);//递归寻找左子树
		if (root->right != NULL)
			isSum(root->right, sum - root->val);//递归寻找右子树

		temp.pop_back();

	}
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		if (root == NULL)
			return res;
		isSum(root, sum);
		return res;
	}
};
int main()
{
	vector<int> data = { 1,3,2,6,5 };

	return 0;
}

