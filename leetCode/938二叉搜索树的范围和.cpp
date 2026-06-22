#include <algorithm> //包含堆操作
#include <iostream>
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
/****************938二叉搜索树的范围和***********************************/
// 给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
	int rangeSumBST(TreeNode *root, int low, int high)
	{
		if (root == nullptr)
			return 0;

		if (root->val > high)
			return rangeSumBST(root->left, low, high);
		if (root->val < low)
			return rangeSumBST(root->right, low, high);

		return root->val + rangeSumBST(root->left, low, high) +
			   rangeSumBST(root->right, low, high);
	}
};
int main()
{

	return 0;
}
