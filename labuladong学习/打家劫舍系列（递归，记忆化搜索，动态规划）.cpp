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
/*************198打家劫舍******************/
//沿街偷窃所有房屋，每个房间有一定量现金
//不能同一晚偷相邻的房间
//计算一夜之内的最高金额
//例[3,4,1,2]->6
//函数定义[x...n-1]的房子
//状态转移方程
//f(0)=max{v(0)+f(1),v(1)+f(3),v(2)+f(4),.....,v(n-3)+f(n-1),v(n-2)+0,v(n-1)+0}
class Solution {
private:
	vector<int> mem;//抢劫nums[i...n]范围的房子获得的最大收益
	//nums[index...nums.size()]范围的房子
	int tryRob(vector<int>& nums,int index) {
		if (index >= nums.size())//递归终止条件
			return 0;
		int res=0;
		if (mem[index] != -1)//是否解决过index问题
			return mem[index];
		for (int i = index; i < nums.size(); i++) {
			res=max(res,nums[i] + tryRob(nums, i + 2));
		}
		mem[index] = res;
		return res;
	}
public:
	int rob(vector<int>& nums) {
		mem = vector<int>(nums.size(), -1);
		return tryRob(nums,0);
	}
};
class Solution {
public:
	int rob(vector<int>& nums) {
		int n = nums.size();
		vector<int> mem(n, -1);
		if (n == 0)//n-1要大于等于1，解决n=0的特殊情况
			return 0;
		mem[n - 1] = nums[n - 1];//总问题是mem[0],初始条件为mem[n-1]
		for (int i = n - 2; i >= 0; i--) {//从下向上分析
			for (int j = i; j < n; j++) {//[i...n-1]的房子
				mem[i] = max(mem[i], nums[j] + (j+2<n? mem[j + 2]:0)); //(j + 2 < n ? mem[j + 2] : 0)保证j+2不越界
			}
		}
		return mem[0];
	}
};
/******************213打家劫舍2，环形房屋**********************/
class Solution {
private:
	int findrob(vector<int> nums, int start, int end) {
		int dp_i_1 = 0, dp_i_2 = 0, dp_i = 0;
		for (int i = end; i >= start; i--) {
			dp_i = max(dp_i_1, nums[i] + dp_i_2);
			dp_i_2 = dp_i_1;
			dp_i_1 = dp_i;
		}
		return dp_i;
	}
public:
	int rob(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int n = nums.size();
		if (n == 1)
			return nums[0];
		return max(findrob(nums, 0, n - 2), findrob(nums, 1, n - 1));//因为头尾不能同时抢，将其分为两种情况，[0,n-2]和[1,n-1]
	}
};
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
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
		int notrobit = rob(root->left) + rob(root->right);
		int res = max(robit, notrobit);
		mem.emplace(root, res);
		return res;
	}
};
/******************337打家劫舍3，树形房屋**********************/
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
int main()
{
	
	return 0;

}

