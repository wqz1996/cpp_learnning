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