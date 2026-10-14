#include <iostream> // 使用处：第 109 行的 cout
#include <string> // 使用处：第 16 行的 string
#include <stack> // 使用处：第 26 行的 stack
#include <vector> // 使用处：第 22 行的 vector
#include <cassert> // 使用处：第 35 行的 assert(
#include <cstddef> // 使用处：第 13 行的 NULL
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
int main()
{
    TreeNode left(1), root(2), right(3);
    root.left = &left;
    root.right = &right;
    Solution solution;
    for (const auto& result : {solution.preorderTraversal(&root),
                               solution.inorderTraversal(&root),
                               solution.postorderTraversal(&root)}) {
        for (int value : result) cout << value << ' ';
        cout << endl;
    }
    return 0;
}
