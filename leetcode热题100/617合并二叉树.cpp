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
/**********************617合并二叉树*************************/
// 合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，
// 否则不为NULL的节点将直接作为新二叉树的节点。
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*************递归********************/
class Solution
{
public:
	TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
	{
		if (t1 == NULL) // t1空返回t2
			return t2;
		if (t2 == NULL)								  // t2空返回t1
			return t1;								  // 这里都为空返回t2
		t1->val += t2->val;							  // 将节点值相加放到t1中
		t1->left = mergeTrees(t1->left, t2->left);	  // 左子树合并
		t1->right = mergeTrees(t1->right, t2->right); // 右子树合并
		return t1;
	}
};
/*************迭代********************/
class Solution
{
public:
	TreeNode *mergeTrees(TreeNode *t1, TreeNode *t2)
	{
		if (t1 == NULL)
			return t2;
		stack<pair<TreeNode *, TreeNode *>> nodestack;
		nodestack.push(make_pair(t1, t2)); // 将根节点压入栈
		while (!nodestack.empty())
		{													  // 栈不为空则未合并完成
			pair<TreeNode *, TreeNode *> t = nodestack.top(); // 获得栈顶元素
			nodestack.pop();
			if (t.first == NULL || t.second == NULL) // 其中有一个为空了则进行下一次循环
				continue;
			t.first->val += t.second->val; // 将值合并
			if (t.first->left == NULL)	   // t1左孩子为空则将t2的左孩子给t1
				t.first->left = t.second->left;
			else // 不为空则压入进行节点值合并运算
				nodestack.push(make_pair(t.first->left, t.second->left));
			if (t.first->right == NULL)
				t.first->right = t.second->right;
			else
				nodestack.push(make_pair(t.first->right, t.second->right));
		}
		return t1;
	}
};
int main()
{
	Solution().mergeTrees();
	std::cout << "qize" << std::endl;
	return 0;
}
