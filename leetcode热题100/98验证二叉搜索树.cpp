#include <algorithm> //包含堆操作
#include <iostream>
#include <sstream> //istringstream 可以将string以空格为分隔符分割
#include <string>
#include <cmath>
#include <stack>  //栈
#include <queue>  //队列
#include <vector> //不注重插入和删除效率
#include <list>	  //类似双向链表，随即存取效率差，不支持[]符号，但是插入和删除效率高
#include <deque>  //双端队列，兼顾随即存取，和两端数据的插入删除
#include <ctime>
#include < unordered_map>
#include < unordered_set>
#include <hash_map>
#include <hash_set>
#include <assert.h>
#include <set>
#include <map>
using namespace std;
// 98. 验证二叉搜索树
// 给定一个二叉树，判断其是否是一个有效的二叉搜索树。
// 假设一个二叉搜索树具有如下特征：
// 节点的左子树只包含小于当前节点的数。
// 节点的右子树只包含大于当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
private:
	bool help(TreeNode *root, long long lower, long long upper)
	{
		if (root == NULL)
			return true;
		if (root->val <= lower || root->val >= upper)
			return false;
		return help(root->left, lower, root->val) && help(root->right, root->val, upper);
	}

public:
	bool isValidBST(TreeNode *root)
	{
		return help(root, LLONG_MIN, LLONG_MAX);
	}
};
/**********中序遍历*********************/
class Solution
{
	long pre = LONG_MIN;

public:
	bool isValidBST(TreeNode *root)
	{
		if (root == NULL)
			return true;
		if (!isValidBST(root->left)) // 先递归遍历左子树
			return false;
		if (root->val <= pre) // 当前值与前一个值比较判断升序
			return false;
		pre = root->val;				// 记录当前节点为下次比较准备
		return isValidBST(root->right); // 遍历右子树
	}
};
// newest method
class Solution
{
private:
	bool checkValidBST(TreeNode *root, TreeNode *minNode, TreeNode *maxNode)
	{
		if (root == nullptr)
			return true;
		if (minNode != nullptr && root->val <= minNode->val)
			return false;
		if (maxNode != nullptr && root->val >= maxNode->val)
			return false;
		return checkValidBST(root->left, minNode, root) &&
			   checkValidBST(root->right, root, maxNode);
	}

public:
	bool isValidBST(TreeNode *root)
	{
		return checkValidBST(root, nullptr, nullptr);
	}
};
int main()
{

	return 0;
}
