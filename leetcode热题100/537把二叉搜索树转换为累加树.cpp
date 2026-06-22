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
// 538. 把二叉搜索树转换为累加树
// 给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树
// （Greater Tree)，使得每个节点的值是原来的节点值加上所有大于
// 它的节点值之和。
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/****************递归解决*******************/
class Solution
{
private:
	int sum = 0;

public:
	TreeNode *convertBST(TreeNode *root)
	{ // 反序中序遍历（右中左）
		if (root != NULL)
		{
			convertBST(root->right); // 先遍历右子树
			sum += root->val;		 // 降序遍历，将当前节点的值累加起来
			root->val = sum;		 // 把累加和给当前节点
			convertBST(root->left);	 // 遍历左子树
		}
		return root;
	}
};
/****************递归解决*******************/
class Solution1
{
public:
	TreeNode *convertBST(TreeNode *root)
	{ // 反序中序遍历（右中左）
		int sum = 0;
		TreeNode *node = root;
		stack<TreeNode *> s;
		while (!s.empty() || node != NULL)
		{
			while (node != NULL)
			{ // 将右子树全部压入
				s.push(node);
				node = node->right;
			}

			node = s.top();
			s.pop();

			sum += node->val; // 累加和
			node->val = sum;  // 将累加和放入当前节点

			node = node->left; // 访问左子树
		}
		return root;
	}
};
TreeNode *reconPreOrder(char *&str)
{ // char*& 影响函数外指针的值，相当于操作外部指针
	if (*str == '#')
	{
		str++; // 跳过'#'
		str++; // 跳过'_'
		return NULL;
	}
	int value = 0;
	while (*str != '_')
	{ // 遇到'_'之前的字符，将char转换为int值
		value = 10 * value + (int)((*str) - '0');
		str++;
	}
	str++; // 跳过'_'
	TreeNode *head = new TreeNode(-1);
	head->val = value;
	head->left = reconPreOrder(str);
	head->right = reconPreOrder(str);
	return head;
}
TreeNode *reconBypreString(char *str)
{ // 反序列化主函数
	if (str == NULL || *str == '#')
		return NULL;
	return reconPreOrder(str);
}
int main()
{
	string s = "5_2_#_#_13_#_#_";
	char *str = (char *)s.c_str();
	TreeNode *root = reconBypreString(str);
	Solution1().convertBST(root);

	return 0;
}
