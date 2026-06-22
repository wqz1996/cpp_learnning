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
int main() {
	string prestr{ "1_2_#_5_#_#_3_#_#_" };//"1_2_#_3_#_#_4_#_#_"
	TreeNode* head;
	char* s_char = (char*)prestr.c_str();//string to char*
	head = Solution().creatTree(s_char);
	Solution().preOrderUnResur(head);
	
	return 0;
} 