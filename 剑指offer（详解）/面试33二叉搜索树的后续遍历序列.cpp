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
//面试题33. 二叉搜索树的后序遍历序列
// 题目：输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。
//如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
//二叉搜索树root->left->val<root->val<root->right->val
//二叉搜索树（二叉查找树、二叉排序树）：空树定义是二叉搜索树，左子树不为空，
//则左子树所有节点值小于根节点，右子树不为空则，右子树所有节点值大于根节点
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
/*******************************************************/
class Solution {
private:
	bool isPostOrder(vector<int>& postorder,int start,int end) {
		if (start > end)//递归终止条件
			return true;
		int root = postorder[end];//最后一个为根节点
		int i = start;
		while (i < end && postorder[i] < root) //不包括root
			i++;//从左到右第一个大于root的节点是右子树的开始位置

		//在二叉搜索书中右子树的所有结点大于根结点
		for (int j = i; j < end; j++)
		{
			if (postorder[j] < root)//如果右子树中出现小于root的节点则返回false
				return false;
		}

		bool left = true;//没有左右子树默认为真
		bool right = true;
		if (i > start)//判断左子树是否满足条件，i>start说明存在左子树
			left = isPostOrder(postorder, start, i - 1);//从开始到第一个大于根节点的前一个节点
		if(i<end-1)//判断右子树是否满足条件，i<end-1说明存在右子树
			right= isPostOrder(postorder, i, end - 1);//从找到的第一个大于根节点到根节点前一个位置
		return left && right;
	}
public:
	bool verifyPostorder(vector<int>& postorder) {
		if (postorder.empty())
			return true;//定义空是二叉搜索树
		return isPostOrder(postorder, 0, postorder.size() - 1);//从0到size-1递归

	}
};
/**********自写程序 空间复杂度O(N)***************/
class Solution {
	bool judge(vector<int>& postorder) {
		if (postorder.size() <= 2)//序列小于2一定为真
			return true;
		int root = postorder.back();//根节点为序列末尾元素
		int big = postorder.size() - 1;//当big==postorder.size()-1说明不存在右子树
		vector<int> left;
		vector<int> right;
		for (int i = big; i >= 0; i--) {//找到左侧第一个大于root的元素下标
			if (postorder[i] > root) {
				big = i;
			}
		}
		for (int i = 0; i < big; i++) {//缓存左子树序列,当big==postorder.size()-1时左子树为去掉末尾元素的所有元素
			if (postorder[i] >= root)
				return false;
			left.push_back(postorder[i]);
		}
		
		for (int i = big; i < postorder.size() - 1; i++) {//缓存右子树序列，当big==postorder.size()-1时右子树为空
			if (postorder[i] <= root)
				return false;
			right.push_back(postorder[i]);
		}
		if (judge(left) && judge(right))//递归判断左右子树
			return true;
		return false;
	}
public:
	bool verifyPostorder(vector<int>& postorder) {
		if (postorder.empty())
			return true;
		return judge(postorder);
	}
};
/******自写空间复杂度O(1)********/
class Solution {
	bool judge(vector<int>& postorder, int start, int end) {
		if (end - start <= 2)//元素个数小于等于2一定成立
			return true;
		int root = postorder[end];
		int i = start;
		while (i < end && postorder[i] < root)//从左到右找到第一个大于root的元素下标
			i++;
		for (int j = i; j < end; j++) {//判断右子树中是否存在小于root的值
			if (postorder[j] < root)
				return false;
		}
		for (int j = start; j < i; j++) {//判断左子树中是否存在小于root的值
			if (postorder[j] > root)
				return false;
		}
		bool left = true;
		bool right = true;
		if (i > start)//若i==start则左子树只有一个元素或者左子树为空，left为默认值true
			left = judge(postorder, start, i - 1);
		if (i < end - 1)//若i==end没有右子树，i==end-1则右子树只有一个元素，right返回默认值true
			right = judge(postorder, i, end - 1);
		return left && right;
	}
public:
	bool verifyPostorder(vector<int>& postorder) {
		if (postorder.empty())
			return true;
		return judge(postorder, 0, postorder.size() - 1);
	}
};
int main()
{
	vector<int> data = { 1,3,2,6,5 };
	cout<<Solution().verifyPostorder(data);
	return 0;
}

