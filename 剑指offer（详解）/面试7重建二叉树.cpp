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
//面试7 重建二叉树
//输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
//假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty())
			return NULL;

		vector<int> left_pre, left_in, right_pre, right_in;
		int inlen = inorder.size();//先序和中序长度一样，只需记录一个
		int root = 0;//记录根节点索引位置
		TreeNode* head = new TreeNode(preorder[0]);//先序遍历第一个为根节点

		//由于不存在数值相同的节点，因此可以这样搜索
		while (inorder[root] != preorder[0]) //记录中序遍历中的根节点位置		
			root++;

		//中序遍历根节点左侧为左子树的中序遍历，右侧为右子树的中序遍历
		//先序遍历根节点后分别为左子树和右子树的先序遍历
		for (int i = 0; i < root; i++) {//记录左子树的先序遍历和中序遍历
			left_pre.push_back(preorder[i + 1]);//先序遍历的左子树索引和中序遍历差一个根节点
			left_in.push_back(inorder[i]);
		}
		for (int i = root + 1; i < inlen; i++) {//记录右子树的先序遍历和中序遍历
			right_pre.push_back(preorder[i]);
			right_in.push_back(inorder[i]);
		}
		head->left = buildTree(left_pre, left_in);//递归完成左子树和右子树的建立
		head->right = buildTree(right_pre, right_in);
		return head;
	}
};
/***********分冶递归**********************/
class Solution {
private:
	//使用迭代器
	TreeNode* recursionBuild(vector<int>::iterator preBegin, vector<int>::iterator preEnd, vector<int>::iterator inBegin, vector<int>::iterator inEnd) {
		if (inEnd == inBegin)//递归终止条件
			return NULL;
		TreeNode* head = new TreeNode(*preBegin);//建立当前根节点
		auto root = find(inBegin, inEnd, *preBegin);//找到中序遍历根节点位置
		//preBegin + 1 + (root - inBegin)指向的是root的下一位表示preorder.end()
		head->left = recursionBuild(preBegin + 1, preBegin + 1 + (root - inBegin), inBegin, root);//必须用对应的迭代器表示
		head->right = recursionBuild(preBegin + 1 + (root - inBegin), preEnd, root + 1, inEnd);
		return head;
	}
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty())
			return NULL;
		return recursionBuild(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
	}
};
//自写，不使用空间缓存序列，只需要进行递归即可，最优解
class Solution {
private:
	TreeNode* rebuildTree(vector<int>& preorder, vector<int>& inorder, int pre_begin, int pre_end, int in_begin, int in_end) {
		if (pre_begin > pre_end)//终止条件范围为空区间
			return NULL;
		int root = 0;
		for (int i = in_begin; i <= in_end; i++) {//在中序区间中找到根节点位置
			if (inorder[i] == preorder[pre_begin]) {
				root = i;
				break;
			}

		}
		TreeNode* node = new TreeNode(preorder[pre_begin]);
		//pre_begin + 1为跳过第一个根节点作为先序的起始位置，pre_begin + root - in_begin是根据中序遍历根节点到开始节点的距离作为递增步长
		//pre_begin + 1, pre_begin + root - in_begin和pre_begin + root - in_begin + 1, pre_end将先序序列分为两个部分
		//in_begin, root - 1,root + 1, in_end将中序序列以根节点为划分，分成左右子树的序列
		node->left = rebuildTree(preorder, inorder, pre_begin + 1, pre_begin + root - in_begin, in_begin, root - 1);
		node->right = rebuildTree(preorder, inorder, pre_begin + root - in_begin + 1, pre_end, root + 1, in_end);
		return node;
	}
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.empty() || inorder.empty())
			return NULL;
		return rebuildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
	}
};
int main()
{

	return 0;
}

