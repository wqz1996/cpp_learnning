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
//面试题32 - I. 从上到下打印二叉树
// 题目：从上到下打印出二叉树的每个节点，
//同一层的节点按照从左到右的顺序打印。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	vector<int> levelOrder(TreeNode* root) {//层序遍历
		vector<int> res;
		if (root == NULL)
			return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();
			res.push_back(node->val);
			if(node->left!=NULL)//空节点不进入队列
			q.push(node->left);//先进左孩子，再进右孩子
			if (node->right != NULL)
			q.push(node->right);
		}
		return res;

	}
};
int main()
{

	return 0;
}

