#include <iostream> // cout、endl：main 输出前序、中序和后序遍历
#include <string> // string：第 16 行首次使用
#include <stack> // stack：第 26 行首次使用
#include <vector> // vector：第 22 行首次使用
#include <cassert> // assert：第 35 行首次使用
#include <cstddef> // NULL：第 13 行首次使用
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
