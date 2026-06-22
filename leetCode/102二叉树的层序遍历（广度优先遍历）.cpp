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
/************102二叉树层序遍历*******************/
 struct TreeNode {
     int val;
     TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 class Solution {
 public:
	 vector<vector<int>> levelOrder(TreeNode* root) {
		 vector<vector<int>> res;
		 if (root == NULL)
			 return res;
		 queue<pair<TreeNode*, int>> q;
		 q.push(make_pair(root, 0));
		 while (!q.empty()) {
			 TreeNode* node = q.front().first;
			 int level = q.front().second;
			 q.pop();
			 if (level == res.size()) {
				 res.push_back(vector<int>());//创建一个新的vector
			 }
			 res[level].push_back(node->val);//第level层的节点数值
			 if (node->left != NULL)
				 q.push(make_pair(node->left, level + 1));
			 if (node->right != NULL)
				 q.push(make_pair(node->right, level + 1));

		 }
		 return res;


	 }
 };
int main() {

	return 0;
} 