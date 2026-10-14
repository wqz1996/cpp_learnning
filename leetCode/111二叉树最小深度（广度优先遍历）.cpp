#include <cstddef> // 使用处：第 11 行的 NULL
#include <algorithm> // 使用处：第 25 行的 min(
#include <queue> // 使用处：第 35 行的 queue
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
