#include <cstddef> // 使用处：第 13 行的 NULL
#include <iostream> // 使用处：第 63 行的 cout
#include <string> // 使用处：第 17 行的 string
#include <stack> // 使用处：第 58 行的 stack
#include <vector> // 使用处：第 17 行的 vector
using namespace std;
/*************257二叉树的所有路径******************/
//给定二叉树返回所有从根节点到叶子节点的路径
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res;

		if (root == NULL)
			return res;

		if (root->left == NULL && root->right == NULL) {
			res.push_back(to_string(root->val));
			return res;
		}
		vector<string> lefts=binaryTreePaths(root->left);
		for (int i = 0; i < lefts.size(); i++)
			res.push_back(to_string(root->val) + "->" + lefts[i]);//将当前节点加上左子树所有路径
		
		vector<string> rights = binaryTreePaths(root->right);
		for (int i = 0; i < rights.size(); i++)
			res.push_back(to_string(root->val) + "->" + rights[i]);

		return res;

	}
	TreeNode* creatTree(char*& str) {
		if (*str == '#') {
			str++;
			str++;
			return NULL;
		}
		int value = 0;
		while (*str != '_') {
			value = 10 * value + (int)((*str) - '0');
			str++;
		}
		str++;
		TreeNode* node = new TreeNode(value);
		node->left = creatTree(str);
		node->right = creatTree(str);
		return node;

	}
	void preOrderUnResur(TreeNode* head) {
		if (head != NULL) {
			stack<TreeNode*> s;
			s.push(head);
			while (!s.empty()) {
				head = s.top();//弹出栈顶元素
				s.pop();
				cout << head->val << " ";
				if (head->right != NULL)//先压右子树
					s.push(head->right);
				if (head->left != NULL)//后压左子树
					s.push(head->left);
			}
		}

	}

};
int main() {
	string prestr{ "1_2_#_5_#_#_3_#_#_" };//"1_2_#_3_#_#_4_#_#_"
	TreeNode* head;
	char* s_char = (char*)prestr.c_str();//string to char*
	head = Solution().creatTree(s_char);
	Solution().preOrderUnResur(head);
	
	return 0;
} 