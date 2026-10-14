#include <cstddef> // 使用处：第 10 行的 NULL
#include <string> // 使用处：第 13 行的 string
#include <queue> // 使用处：第 52 行的 queue
#include <vector> // 使用处：第 48 行的 vector
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};
int index;
TreeNode* reconBypreString(string str) {
	if (str[index] == '#') {
		index++;//跳过'#'
		index++;//跳过'_'
		return NULL;
	}
	int value = 0;
	if (str[index] == '-') {
		index++;//跳过'-'
		while (str[index] != '_') {//计算所有'_'之前组成的数字
			value = 10 * value - (int)(str[index] - '0');
			index++;
		}
	}
	else {//不是负数
		while (str[index] != '_') {
			value = 10 * value + (int)(str[index] - '0');
			index++;
		}
	}

	index++;//跳过'_'
	//先序遍历重构
	TreeNode* node = new TreeNode(value);//新建节点
	node->left = reconBypreString(str);//递归构建左子树
	node->right = reconBypreString(str);//构建右子树
	return node;
}
TreeNode* deserialize(string data) {
	if (data.empty() || data == "#_")
		return NULL;
	index = 0;
	return reconBypreString(data);
}
/******二维*****/
vector<vector<int>> cengxu(TreeNode* root) {
	vector<vector<int>> res;
	if (root == NULL)
		return vector<vector<int>>{};
	queue<TreeNode*> q;
	q.push(root);
	vector<int> temp;
	while (!q.empty()) {
		int sz = q.size();
		for (int i = 0; i < sz; i++) {
			TreeNode* node = q.front();
			q.pop();
			temp.push_back(node->val);
			if (node->left != NULL)
				q.push(node->left);
			if (node->right != NULL)
				q.push(node->right);
		}
	
		res.push_back(temp);
		temp.clear();
		
	}
	return res;
}
/******一维*****/
vector<int> cengxu1(TreeNode* root) {
	vector<int>  res;
	if (root == NULL)
		return vector<int>{};
	queue<TreeNode*> q;
	q.push(root);
	while (!q.empty()) {
		TreeNode* node = q.front();
		q.pop();
		res.push_back(node->val);
		if (node->left != NULL)
			q.push(node->left);
		if (node->right != NULL)
			q.push(node->right);
	}
	return res;
}
int main() {
	
	string s = "1_2_4_#_#_5_#_#_3_#_#_";
	TreeNode* root = deserialize(s);
	vector<vector<int>> res = cengxu(root);
	return 0;
}
