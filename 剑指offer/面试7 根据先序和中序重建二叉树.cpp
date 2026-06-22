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
using namespace std;
// 面试题7：重建二叉树
// 题目：输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输
// 入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,
// 2, 4, 7, 3, 5, 6, 8}和中序遍历序列{4, 7, 2, 1, 5, 3, 8, 6}，则重建出
// 图2.6所示的二叉树并输出它的头结点。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/************在线IDE*****************/
class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin) {
		if (pre.empty() || vin.empty()) {//base case
			return NULL;
		}
		int prelen = pre.size();
		int vinlen = vin.size();
		int root = 0;
		vector<int> left_pre, left_vin, right_pre, right_vin;
		TreeNode* head = new TreeNode(pre[0]);
		for (int i = 0; i < vinlen; i++) {
			if (vin[i] == pre[0]) {
				root = i;//记录中序遍历中根节点编号
				break;
			}
		}
		for (int i = 0; i < root; i++) {//记录先序和后序中左子树的数组
			left_vin.push_back(vin[i]);
			left_pre.push_back(pre[i + 1]);
		}
		for (int i = root + 1; i < vinlen; i++) {//记录先序和后序中右子树的数组
			right_vin.push_back(vin[i]);
			right_pre.push_back(pre[i]);
		}
		head->left = reConstructBinaryTree(left_pre, left_vin);
		head->right = reConstructBinaryTree(right_pre, right_vin);
		return head;


	}

};




int main()
{

	return 0;

}



