#include <cstddef> // 使用处：第 14 行的 NULL
#include <iostream> // 使用处：第 56 行的 cout
#include <string> // 使用处：第 68 行的 string
#include <stack> // 使用处：第 51 行的 stack
#include <assert.h> // 使用处：第 19 行的 assert(
using namespace std;
/*************235二叉搜索树的最近公共祖先******************/
//给定二叉搜索树，找到指定两个节点的最近公共祖先
//注意：二叉搜索树：左子树<根节点<右子树
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		assert(p != NULL && q != NULL);

		if (root == NULL)
			return NULL;

		if (p->val < root->val && q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);//公共祖先在左子树中
		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);//公共祖先在右子树中

		return root;//若p，q分别在左右子树，或者其中一个就是当前root节点，则公共祖先为当前节点root
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