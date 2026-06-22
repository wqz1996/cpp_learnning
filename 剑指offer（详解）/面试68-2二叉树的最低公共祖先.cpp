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
//面试题68 - II. 二叉树的最近公共祖先
// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
//百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
//最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽
//可能大（一个节点也可以是它自己的祖先）。”
//例如，给定如下二叉树 : root = [3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == NULL)
			return NULL;
		if (root == p || root == q)//找到p或q则将root其返回
			return root;
		TreeNode* left = lowestCommonAncestor(root->left, p, q);//左子树找p和q
		TreeNode* right= lowestCommonAncestor(root->right, p, q);//右子树找p和q
		if (left != NULL && right != NULL)//左右子树分别找到了p和q则返回根节点
			return root;
		return left != NULL ? left : right;//若左子树返回NULL则说明p，q都在右子树，若左子树返回不为空说明都在左子树上
	}
};
int main()
{

	return 0;
}

