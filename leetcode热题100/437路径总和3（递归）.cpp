#include <iostream> // cout：第 67 行首次使用
#include <string> // string：第 80 行首次使用
#include <stack> // stack：第 62 行首次使用
#include <cstddef> // NULL：第 15 行首次使用
using namespace std;
/*************437路径总和3******************/
//给定二叉树，每个节点存放一个整数
//找出路径等于给定值的路径总数
//注意：路径不用以根节点开始到叶子节点结束，
//但要求从上到下
struct TreeNode {
     int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
private:
	//寻找以node为根节点的二叉树中，寻找包含node的路径，和为sum
	//与之前简单的路径和的求法一致，不同点是不要求以叶子节点结束
	int findpath(TreeNode* node, int sum) {
		if (node == NULL)
			return 0;
		int res = 0;
		if (node->val == sum)
			res += 1;
		res += findpath(node->left, sum - node->val);
		res += findpath(node->right, sum - node->val);
		return res;
	}
public:
		int pathSum(TreeNode* root, int sum) {
			if (root == NULL)
				return 0;
			int res = findpath(root,sum);//包含当前node
			res += pathSum(root->left, sum);//排除当前node，直接找左右子树
			res += pathSum(root->right, sum);

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
int main()
{
    string encoded = "1_2_#_5_#_#_3_#_#_";
    char* text = &encoded[0];
    Solution solution;
    TreeNode* root = solution.creatTree(text);
    solution.preOrderUnResur(root);
    cout << endl << "路径和为 3 的数量: " << solution.pathSum(root, 3) << endl;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}
