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
/************二叉树前序,中序，后序遍历*******************/
 struct TreeNode {
     int val;
     TreeNode *left;
      TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 struct Command {
	 string s;
	 TreeNode* node;
	 Command(string s, TreeNode* node) :s(s), node(node) {}
 };
class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> res;
		if (root == NULL)
			return res;
		stack<Command> stack;
		stack.push(Command("go", root));
		while (!stack.empty()) {
			Command command = stack.top();
			stack.pop();
			if (command.s == "print") {
				res.push_back(command.node->val);
			}
			else {
				assert(command.s == "go");
				if (command.node->right)
					stack.push(Command("go", command.node->right));
				if (command.node->left)
					stack.push(Command("go", command.node->left));
				stack.push(Command("print", command.node));
			}
		}
		return res;


	}

	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (root == NULL)
			return res;
		stack<Command> stack;
		stack.push(Command("go", root));
		while (!stack.empty()) {
			Command command = stack.top();
			stack.pop();
			if (command.s == "print") {
				res.push_back(command.node->val);
			}
			else {
				assert(command.s == "go");
				if (command.node->right)
					stack.push(Command("go", command.node->right));
				stack.push(Command("print", command.node));
				if (command.node->left)
					stack.push(Command("go", command.node->left));
				
			}
		}
		return res;

	}

	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> res;
		if (root == NULL)
			return res;
		stack<Command> stack;
		stack.push(Command("go", root));
		while (!stack.empty()) {
			Command command = stack.top();
			stack.pop();
			if (command.s == "print") {
				res.push_back(command.node->val);
			}
			else {
				assert(command.s == "go");
				stack.push(Command("print", command.node));
				if (command.node->right)
					stack.push(Command("go", command.node->right));
				if (command.node->left)
					stack.push(Command("go", command.node->left));

			}
		}
		return res;
	}
		
};
int main() {

	return 0;
} 