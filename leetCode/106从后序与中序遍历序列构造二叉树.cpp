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
// 106 从后序与中序遍历序列构造二叉树
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
	unordered_map<int, int> m;
	TreeNode *build(vector<int> &inorder, int in_start, int in_end,
					vector<int> &postorder, int post_start, int post_end)
	{
		if (in_start > in_end || post_start > post_end)
			return nullptr;
		int root_val = postorder[post_end];
		TreeNode *root = new TreeNode(root_val);
		int root_idx = m[root_val];
		int left_size = root_idx - in_start;
		root->left = build(inorder, in_start, root_idx - 1, postorder,
						   post_start, post_start + left_size - 1);
		root->right = build(inorder, root_idx + 1, in_end, postorder,
							post_start + left_size, post_end - 1);
		return root;
	}

public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
	{
		for (int i = 0; i < inorder.size(); i++)
		{
			m[inorder[i]] = i;
		}

		return build(inorder, 0, inorder.size() - 1, postorder, 0,
					 postorder.size() - 1);
	}
};
int main()
{

	return 0;
}
