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
/**********************532二叉树直径*************************/
//给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意
//两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};

class Solution {
private:
	int res;
	int depth(TreeNode* root) {
		if (root == NULL)
			return 0;
		int left = depth(root->left);//左树最大深度
		int right = depth(root->right);//右树最大深度
		res = max(res, left + right + 1);
		return max(left, right) + 1;
	}
public:
	int diameterOfBinaryTree(TreeNode* root) {
		res = 1;
		depth(root);
		return res-1;
	}
};
int main()
{

	return 0;
}

