#include <cstddef> // 使用处：第 11 行的 NULL
using namespace std;
//面试题26. 树的子结构
// 题目：输入两棵二叉树A和B，判断B是不是A的子结构。
//(约定空树不是任意一个树的子结构)
//B是A的子结构， 即 A中有出现和B相同的结构和节点值。
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};
class Solution {
private:
	bool DoesTree1HaveTree2(TreeNode* T1, TreeNode* T2) {
		if (T2 == NULL)//T2为空了，代表T2所有节点已经都匹配完毕
			return true;
		if (T1 == NULL)//T1为空了，（暗含）T2不为空，则T1不能包含T2
			return false;
		if (T1->val != T2->val)//若T1当前节点和T2当前节点的值不等直接返回false
			return false;
		//T1左子树和T2左子树相等并且T1右子树和T2右子树相等
		return DoesTree1HaveTree2(T1->left, T2->left) && DoesTree1HaveTree2(T1->right, T2->right);
	}
public:
	bool isSubStructure(TreeNode* A, TreeNode* B) {
		if (A == NULL || B == NULL)//任何一个树为空直接返回false
			return false;
		//判断以当前节点是否可以找到T1包含T2//递归找A的左子树            //递归找A的右子树
		return DoesTree1HaveTree2(A, B) || isSubStructure(A->left, B) || isSubStructure(A->right, B);
	}
};

int main()
{

	return 0;
}

