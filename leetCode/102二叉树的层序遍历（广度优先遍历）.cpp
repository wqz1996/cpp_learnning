#include <cstddef> // 使用处：第 11 行的 NULL
#include <utility> // 使用处：第 19 行的 pair
#include <queue> // 使用处：第 19 行的 queue
#include <vector> // 使用处：第 15 行的 vector
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