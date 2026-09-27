#include <iostream> // cout、endl：main 输出递归和迭代解法
#include <string> // string：第 93 行首次使用
#include <stack> // stack：第 44 行首次使用
#include <cstddef> // NULL：第 15 行首次使用
using namespace std;
// 538. 把二叉搜索树转换为累加树
// 给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树
// （Greater Tree)，使得每个节点的值是原来的节点值加上所有大于
// 它的节点值之和。
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/****************递归解决*******************/
class Solution
{
private:
	int sum = 0;

public:
	TreeNode *convertBST(TreeNode *root)
	{ // 反序中序遍历（右中左）
		if (root != NULL)
		{
			convertBST(root->right); // 先遍历右子树
			sum += root->val;		 // 降序遍历，将当前节点的值累加起来
			root->val = sum;		 // 把累加和给当前节点
			convertBST(root->left);	 // 遍历左子树
		}
		return root;
	}
};
/****************递归解决*******************/
class Solution1
{
public:
	TreeNode *convertBST(TreeNode *root)
	{ // 反序中序遍历（右中左）
		int sum = 0;
		TreeNode *node = root;
		stack<TreeNode *> s;
		while (!s.empty() || node != NULL)
		{
			while (node != NULL)
			{ // 将右子树全部压入
				s.push(node);
				node = node->right;
			}

			node = s.top();
			s.pop();

			sum += node->val; // 累加和
			node->val = sum;  // 将累加和放入当前节点

			node = node->left; // 访问左子树
		}
		return root;
	}
};
TreeNode *reconPreOrder(char *&str)
{ // char*& 影响函数外指针的值，相当于操作外部指针
	if (*str == '#')
	{
		str++; // 跳过'#'
		str++; // 跳过'_'
		return NULL;
	}
	int value = 0;
	while (*str != '_')
	{ // 遇到'_'之前的字符，将char转换为int值
		value = 10 * value + (int)((*str) - '0');
		str++;
	}
	str++; // 跳过'_'
	TreeNode *head = new TreeNode(-1);
	head->val = value;
	head->left = reconPreOrder(str);
	head->right = reconPreOrder(str);
	return head;
}
TreeNode *reconBypreString(char *str)
{ // 反序列化主函数
	if (str == NULL || *str == '#')
		return NULL;
	return reconPreOrder(str);
}
int main()
{
    string encoded = "5_2_#_#_13_#_#_";
    char* firstText = &encoded[0];
    char* secondText = &encoded[0];
    TreeNode* first = reconBypreString(firstText);
    TreeNode* second = reconBypreString(secondText);
    Solution().convertBST(first);
    Solution1().convertBST(second);
    cout << "递归: " << first->left->val << ' ' << first->val << ' ' << first->right->val << endl;
    cout << "迭代: " << second->left->val << ' ' << second->val << ' ' << second->right->val << endl;
    delete first->left; delete first->right; delete first;
    delete second->left; delete second->right; delete second;
    return 0;
}
