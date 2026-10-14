#include <cstddef> // 使用处：第 10 行的 NULL
#include <string> // 使用处：第 13 行的 string
#include <stack> // 使用处：第 53 行的 stack
#include <vector> // 使用处：第 49 行的 vector
using namespace std;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/***********************二叉树反序列化及遍历********************************/
string serialByPre(TreeNode* root) {//先序序列化

	if (root == NULL)
		return "#_";//记录NULL
	string res = to_string(root->val) + "_";
	res += serialByPre(root->left);//记录左树
	res += serialByPre(root->right);//记录右树
	return res;

}
/**************反序列化**************/
TreeNode* reconPreOrder(char*& str) {//char*& 影响函数外指针的值，相当于操作外部指针
	if (*str == '#') {
		str++;//跳过'#'
		str++;//跳过'_'
		return NULL;
	}
	int value = 0;
	while (*str != '_') {//遇到'_'之前的字符，将char转换为int值
		value = 10 * value + (int)((*str) - '0');
		str++;
	}
	str++;//跳过'_'
	TreeNode* head = new TreeNode(-1);
	head->val = value;
	head->left = reconPreOrder(str);
	head->right = reconPreOrder(str);
	return head;

}
TreeNode* reconBypreString(char* str) {//反序列化主函数
	if (str == NULL || *str == '#')
		return NULL;
	return reconPreOrder(str);
}
/***************************************************/
vector<int> preOrderUnResur(TreeNode* root) {//先序遍历
			vector<int> res;
			if (root == NULL)
				return res;
			stack<TreeNode*> s;
			s.push(root);
			while (!s.empty()) {
				root = s.top();//弹出栈顶元素
				s.pop();
				res.push_back(root->val);
				if (root->right != NULL)//先压右子树
					s.push(root->right);
				if (root->left != NULL)//后压左子树
					s.push(root->left);
			}	
			return res;

}
vector<int> inOrderUnResur(TreeNode* root) {//中序遍历
	vector<int> res;
	if (root == NULL)
		return res;
	stack<TreeNode*> s;
	
	while (!s.empty()||root!=NULL) {
		if (root != NULL) {
			s.push(root);
			root = root->left;
		}
		else {
			root = s.top();
			s.pop();
			res.push_back(root->val);
			root = root->right;
		}
	}	

	return res;
}
vector<int> postOrderUnResur(TreeNode* root) {//后序遍历
	vector<int> res;
	if (root == NULL)
		return res;
	stack<TreeNode*> help;
	stack<TreeNode*> s;
	s.push(root);
	while (!s.empty()) {
		TreeNode* node = s.top();
		s.pop();
		help.push(node);
		if (node->left != NULL)
			s.push(node->left);
		if (node->right != NULL)
			s.push(node->right);
	}
	while (!help.empty()) {
		res.push_back(help.top()->val);
		help.pop();
	}
	
	return res;
}
int main()
{
	string s = "3_9_8_#_#_6_#_#_20_15_#_#_7_#_#_";
	char* str = (char *)s.c_str();
	TreeNode* root = reconBypreString(str);
	vector<int> ans= preOrderUnResur(root);

	return 0;
}

