#include <cstddef> // 使用处：第 13 行的 NULL
#include <iostream> // 使用处：第 55 行的 cout
#include <string> // 使用处：第 67 行的 string
#include <stack> // 使用处：第 50 行的 stack
using namespace std;
/*************112路径总和******************/
//给定二叉树和目标和，判断书中是否存在根节点到叶子节点
//的路径，使得路径上节点值相加等于目标和
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	bool hasPathSum(TreeNode* root, int sum) {
		if (root == NULL)
			return false;
		if (root->left == NULL && root->right == NULL)
			return root->val==sum;

		if (hasPathSum(root->left, sum - root->val))
		return true;
		if (hasPathSum(root->right, sum - root->val))
		return true;

		return false;
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
	string prestr{ "1_#_2_#_#_" };//"1_2_#_3_#_#_4_#_#_"
	TreeNode* head;
	char* s_char = (char*)prestr.c_str();//string to char*
	head = Solution().creatTree(s_char);
	Solution().preOrderUnResur(head);
	cout << Solution().hasPathSum(head,0);
	return 0;
} 