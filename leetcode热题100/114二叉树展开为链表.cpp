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
#include<hash_map>
#include<hash_set>
#include<assert.h>
#include<set>
#include<map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
	void flatten(TreeNode* root) {
		while (root != NULL) {//
			if (root->left != NULL) {//root不是叶子节点则继续
				TreeNode* node = root->left;
				while (node->right != NULL)//找到左子树最右节点
					node = node->right;
				node->right = root->right;//左子树最右节点的右指针指向root的右孩子
				root->right = root->left;//释放root右指针
				root->left = NULL;

			}
			root = root->right;//root左指针被右指针代替，因此用右指针遍历
		}
	}
};
int main()
{


	return 0;
}

