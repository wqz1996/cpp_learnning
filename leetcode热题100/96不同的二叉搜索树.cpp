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

