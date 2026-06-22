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
//面试题32 - I. 从上到下打印二叉树
// 题目：从上到下打印出二叉树的每个节点，
//同一层的节点按照从左到右的顺序打印。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
//	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
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
	TreeNode* head = new TreeNode;
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
void preOrderUnResur(TreeNode* head) {//先序遍历
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


class Solution {
private:
	vector<vector<int>> res;
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (root == NULL)
			return res;
		vector<int> tmp;//缓存每一层的元素
		queue<TreeNode*> q;
		int curnums = 1;//当前层剩余的节点
		int nextnums = 0;//下一层的节点
		q.push(root);
		while (!q.empty()) {
			TreeNode* node = q.front();
			q.pop();
			if (curnums != 0) {//当前层节点未保存完
				tmp.push_back(node->val);
				curnums--;
			}

			if (node->left != NULL) {
				q.push(node->left);
				nextnums++;
			}
			if (node->right != NULL) {
				q.push(node->right);
				nextnums++;
			}

			if (curnums == 0) {
				res.push_back(tmp);//当前层保存完毕
				tmp.clear();//清空层缓存
				curnums = nextnums;//记录下一层的节点数
				nextnums = 0;
			}
		}
		return res;

	}
};
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;//保存结果
		if (root == NULL)
			return res;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			vector<int> temp;//缓存当前层序列
			int sz = q.size();//记录当前队列中元素个数即为当前层节点个数
			for (int i = 0; i < sz; i++) {
				TreeNode* node = q.front();
				q.pop();
				temp.push_back(node->val);
				if (node->left != NULL)
					q.push(node->left);
				if (node->right != NULL)
					q.push(node->right);
			}
			res.push_back(temp);
		}
		return res;

	}
};
int main()
{
	string s = "3_9_8_#_#_6_#_#_20_15_#_#_7_#_#_";
	char* str = (char *)s.c_str();
	TreeNode* root = reconBypreString(str);
	Solution().levelOrder(root);
	preOrderUnResur(root);
	return 0;
}

