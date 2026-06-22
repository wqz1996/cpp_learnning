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
