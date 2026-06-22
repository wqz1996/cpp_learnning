#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
//面试题68 - I. 二叉搜索树的最近公共祖先
// 给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
//最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度
//尽可能大（一个节点也可以是它自己的祖先）。”
//例如，给定如下二叉搜索树 : root = [6, 2, 8, 0, 4, 7, 9, null, null, 3, 5]
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL||(root->left==NULL&&root->right==NULL))
			return NULL;
		TreeNode* cur = root;
		while (cur != NULL) {
			if (cur->val < p->val && cur->val < q->val)//当前节点小于两个节点则向右子树搜索
				cur = cur->right;
			else if (cur->val > p->val&& cur->val > q->val)//当前节点大于两个节点则向左子树搜索
				cur = cur->left;
			else
				break;
		}		
		return cur;
	}
};
int main()
{

	return 0;
}

