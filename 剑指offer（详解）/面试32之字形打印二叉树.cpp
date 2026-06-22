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
//面试题32 - III. 从上到下打印二叉树 III
// 题目：请实现一个函数按照之字形顺序打印二叉树，
//即第一行按照从左到右的顺序打印，第二层按照从右到左的顺序打印，
//第三行再按照从左到右的顺序打印，其他行以此类推。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*******************************************************/
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		stack<TreeNode*> q1;//保存当前层的节点
		stack<TreeNode*> q2;//保存下一层的节点
		vector<int> temp;//保存当前层的节点数值
		int curnum = 1;//当前剩余未访问节点
		int nextnum = 0;//下一层节点
		bool flag = true;//压入节点顺序切换
		if (root == NULL)
			return res;
		q1.push(root);
		while (!q1.empty() || !q2.empty()) {//任意一个不为空则还有节点未访问
			TreeNode* node = q1.top();
			q1.pop();
			if (curnum != 0) {
				temp.push_back(node->val);
				curnum--;
			}
			if (flag) {//奇数层进入

				if (node->left != NULL) {//先压入左孩子
					q2.push(node->left);
					nextnum++;
				}
				if (node->right != NULL) {
					q2.push(node->right);
					nextnum++;
				}

			}
			else {//偶数层进入

				if (node->right != NULL) {//先压入右孩子
					q2.push(node->right);
					nextnum++;
				}
				if (node->left != NULL) {
					q2.push(node->left);
					nextnum++;
				}

			}

			if (curnum == 0) {//当前层节点访问完毕
				swap(q1, q2);//交换两个栈
				flag = !flag;//切换压入方式
				res.push_back(temp);//保存当前层节点结果
				temp.clear();//清除当前层节点缓存
				curnum = nextnum;
				nextnum = 0;
			}

		}
		return res;
	}
};
/*****************自写*********************/
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == NULL)
			return res;
		bool flag = true;//切换保存顺序标志位
		stack<TreeNode*> cur;//保存当前层
		stack<TreeNode*> next;//保存下一层
		cur.push(root);
		while (!cur.empty()) {
			vector<int> temp;
			int sz = cur.size();
			for (int i = 0; i < sz; i++) {
				TreeNode* node = cur.top();
				cur.pop();
				temp.push_back(node->val);
				if (flag) {//访问奇数层，下一层先压左子树，再压右子树
					if (node->left != NULL)
						next.push(node->left);
					if (node->right != NULL)
						next.push(node->right);
				}
				else {//访问偶数层，先压右子树，再压左子树
					if (node->right != NULL)
						next.push(node->right);
					if (node->left != NULL)
						next.push(node->left);
				}
			}
			res.push_back(temp);
			swap(cur, next);//交换当前层和下一层的缓存序列，此时cur为空，next为下一层需要访问的所有节点
			flag = !flag;//切换保存顺序
		}
		return res;
	}
};
/***********************二叉树反序列化及先序遍历********************************/
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
int main()
{
	string s = "3_9_8_#_#_6_#_#_20_15_#_#_7_#_#_";
	char* str = (char*)s.c_str();
	TreeNode* root = reconBypreString(str);
	Solution().levelOrder(root);
	preOrderUnResur(root);
	return 0;
}

