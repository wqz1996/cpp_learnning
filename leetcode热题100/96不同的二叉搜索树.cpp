#include <vector> // vector：第 8 行首次使用
using namespace std;
//96. 不同的二叉搜索树
//给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
class Solution {
public:
	int numTrees(int n) {
		vector<int> treenum(n + 1);
		treenum[0] = 1;
		treenum[1] = 1;
		for (int i = 2; i <= n; i++) {//分别以i为根
			for (int j = 1; j <= i; j++) {//
				treenum[i] += treenum[j - 1] * treenum[i - j];
			}
		}
		return treenum[n];
	}
};
int main()
{

	return 0;
}

