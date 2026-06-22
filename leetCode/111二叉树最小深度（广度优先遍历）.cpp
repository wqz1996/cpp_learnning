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

 
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 //递归
 class Solution {
 public:
	 int minDepth(TreeNode* root) {
		 if (root == NULL)
			 return 0;
		 if (root->left == NULL)
			 return 1 + minDepth(root->right);
		 if (root->right == NULL)
			return  1 + minDepth(root->left);
		 int left = 1 + minDepth(root->left);
		 int right = 1 + minDepth(root->right);
		 return min(left, right);
		 
	 }
 };
 //非递归
 class Solution {
 public:
	 int minDepth(TreeNode* root) {
		 if (root == NULL)
			 return 0;
		 queue<TreeNode*> q;
		 q.push(root);
		 int depth = 1;
		 while (!q.empty()) {
			 int size = q.size();
			 for (int i = 0; i < size; i++) {
				 TreeNode* node = q.front();
				 q.pop();
				 if (node->left == NULL && node->right == NULL)
					 return depth;
				 if (node->left != NULL)
					 q.push(node->left);
				 if (node->right != NULL)
					 q.push(node->right);
			 }
			 depth++;
		 }
		 return depth;

	 }
 };
int main() {

	return 0;
}
