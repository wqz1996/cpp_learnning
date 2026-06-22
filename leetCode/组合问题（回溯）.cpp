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
using namespace std;
/************77组合*****************/
//给出两个整数n,k，求1...n这n个数字中选出k个数字的所有组合
//[1,2]与[2,1]认为是相同的
class Solution {
private:
	vector<vector<int>> res;
	//求解C(n,k)，从start开始搜索组合中新的元素
	void generateComb(int n, int k, int start, vector<int>& c) {
		if (c.size() == k) {
			res.push_back(c);
			return;
		}
		for (int i = start; i <= n; i++) {
			c.push_back(i);
			generateComb(n, k, i + 1, c);
			c.pop_back();
		}
		return;
	}
public:
	vector<vector<int>> combine(int n, int k) {
		res.clear();
		if (n <= 0 || k <= 0 || k > n) {//n，k值输入不合法情况
			return res;
		}
		vector<int> p;//初始化空的p
		generateComb(n, k, 1, p);
		return res;
	}
};
/************回溯法的剪枝优化**********/
class Solution1 {
private:
	vector<vector<int>> res;
	//求解C(n,k)，从start开始搜索组合中新的元素
	void generateComb(int n, int k, int start, vector<int>& c) {
		if (c.size() == k) {
			res.push_back(c);
			return;
		}
		//c中存放已有的k个元素，k-c.size()空位,[i...n]中至少有k-c.size()个元素
		//i最大为n-(k-c.size())+1
		for (int i = start; i <= n - (k - c.size()) + 1; i++) {
			c.push_back(i);
			generateComb(n, k, i + 1, c);
			c.pop_back();
		}
		return;
	}
public:
	vector<vector<int>> combine(int n, int k) {
		res.clear();
		if (n <= 0 || k <= 0 || k > n) {//n，k值输入不合法情况
			return res;
		}
		vector<int> p;//初始化空的p
		generateComb(n, k, 1, p);
		return res;
	}
};
int main()
{
	vector<vector<int>> res;
	res = Solution1().Combinations(4, 2);
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[0].size(); j++) {
			cout << res[i][j];
		}
		cout << endl;
	}
	return 0;
}

