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
// 105 从前序与中序遍历序列构造二叉树
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
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
	{
		if (preorder.empty() || inorder.empty())
			return NULL;
		vector<int> left_pre, left_in, right_pre, right_in;
		int len = inorder.size();					// 记录树的总节点数
		int root = 0;								// 记录根节点索引位置
		TreeNode *head = new TreeNode(preorder[0]); // 先序遍历第一个元素为根节点
		while (inorder[root] != preorder[0])		// 找到中序遍历根节点位置
			root++;

		for (int i = 0; i < root; i++)
		{ // 记录左子树先序遍历和中序遍历的元素
			left_pre.push_back(preorder[i + 1]);
			left_in.push_back(inorder[i]);
		}
		for (int i = root + 1; i < len; i++)
		{ // 记录右子树先序遍历和中序遍历的元素
			right_pre.push_back(preorder[i]);
			right_in.push_back(inorder[i]);
		}
		// 先序遍历建立整棵树
		head->left = buildTree(left_pre, left_in);	  // 递归建立左子树
		head->right = buildTree(right_pre, right_in); // 建立右子树
		return head;
	}
};
int main()
{

	return 0;
}
