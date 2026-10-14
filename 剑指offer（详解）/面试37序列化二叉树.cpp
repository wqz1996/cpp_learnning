#include <cstddef> // 使用处：第 12 行的 NULL
#include <iostream> // 使用处：第 158 行的 cout
#include <string> // 使用处：第 18 行的 string
#include <stack> // 使用处：第 104 行的 stack
using namespace std;
//面试题37. 序列化二叉树
// 题目：请实现两个函数，分别用来序列化和反序列化二叉树。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
private:
	int index;
	TreeNode* reconBypreString(string str) {
		if (str[index] == '#'){
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
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (root == NULL)
			return "#_";
		string res = to_string(root->val) + "_";//先序遍历转换
		res += serialize(root->left);
		res += serialize(root->right);
		return res;
	}
	
	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.empty()||data=="#_")
			return NULL;
		index = 0;
		return reconBypreString(data);
	}
};
/******************栈深度搜索(DFS)************************/
class Codec1 {
private:
	int index;
	string res;
	TreeNode* reconBypreString(string str) {
		if (str[index] == '#') {
			index++;//跳过'#'
			index++;//跳过'_'
			return NULL;
		}
		int value = 0;
		if (str[index] == '-') {
			index++;
			while (str[index] != '_') {
				value = 10 * value - (int)(str[index] - '0');
				index++;
			}
		}
		else {
			while (str[index] != '_') {
				value = 10 * value + (int)(str[index] - '0');
				index++;
			}
		}

		index++;//跳过'_'
		TreeNode* node = new TreeNode(value);
		node->left = reconBypreString(str);
		node->right = reconBypreString(str);
		return node;
	}
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (root == NULL)
			return res;
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty()) {
			root = s.top();
			s.pop();
			if (root == NULL) {
				res += "#_";
				continue;
			}			
			else
				res += to_string(root->val) + '_';
			s.push(root->right);
			s.push(root->left);

		}
		return res;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.empty() || data == "#_")
			return NULL;
		index = 0;
		return reconBypreString(data);
	}
};
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
void printTree(TreeNode* root) {
	if (root == NULL)
		return;
	cout << root->val << ' ';
	printTree(root->left);
	printTree(root->right);

}
int main()
{
	string s = "1_2_#_#_3_4_#_#_5_#_#_";
	char* str = (char*)s.c_str();
	TreeNode* root = reconBypreString(str);

	string s1=Codec1().serialize(root);
	TreeNode* head = Codec().deserialize(s1);
	printTree(head);
	
	return 0;
}

