#include<algorithm>//包含堆操作
#include<iostream>
#include<sstream>//istringstream 可以将string以空格为分隔符分割
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
#include<assert.h>
#include<set>
#include<map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	int rob(TreeNode* root) {
		if (root == NULL)
			return 0;
		map<TreeNode*, int> mem;
		if (mem.find(root) != mem.end())//记录重叠子问题
			return mem[root];
		int robit = root->val + (root->left == NULL ? 0 : rob(root->left->left) + rob(root->left->right)) + (root->right == NULL ? 0 : rob(root->right->right) + rob(root->right->left));
		int notrobit = rob(root->left) +  rob(root->right);
		int res = max(robit, notrobit);
		mem.emplace(root,res);
		return res;
	}
};
class Solution {
private:
	//返回arr[0]表示不抢当前得到的最大钱数
	//arr[1]表示抢当前得到的最大钱数
	vector<int> findrob(TreeNode* root) {
		if (root == NULL)
			return vector<int>{0, 0};//空的时候返回{0,0}
		vector<int> left = findrob(root->left);//后序遍历左右子树，自底向上，因此左右遍历完再遍历根节点
		vector<int> right = findrob(root->right);
		int robit = root->val + left[0] + right[0];//抢当前家，下家不能抢（左右孩子都不能抢）
		int notrob = max(left[0], left[1]) + max(right[0], right[1]);//不抢当前家，可以抢或不抢左右孩子，找最大值
		return vector<int>{notrob, robit};
	}
public:
	int rob(TreeNode* root) {
		vector<int> res = findrob(root);
		return max(res[0], res[1]);
	}
};
int main() {

	
	return 0;
}