#include <cstddef> // 使用处：第 11 行的 NULL
#include <algorithm> // 使用处：第 23 行的 max(
#include <vector> // 使用处：第 32 行的 vector
#include <map> // 使用处：第 18 行的 map<
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