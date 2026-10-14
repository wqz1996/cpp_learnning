#include <iostream> // 使用处：第 115 行的 cout
#include <vector> // 使用处：第 10 行的 vector
using namespace std;
/************77组合*****************/
// 给出两个整数n,k，求1...n这n个数字中选出k个数字的所有组合
//[1,2]与[2,1]认为是相同的
class Solution
{
private:
	vector<vector<int>> res;
	// 求解C(n,k)，从start开始搜索组合中新的元素
	void generateComb(int n, int k, int start, vector<int> &c)
	{
		if (c.size() == k)
		{
			res.push_back(c);
			return;
		}
		for (int i = start; i <= n; i++)
		{
			c.push_back(i);
			generateComb(n, k, i + 1, c);
			c.pop_back();
		}
		return;
	}

public:
	vector<vector<int>> Combinations(int n, int k)
	{
		res.clear();
		if (n <= 0 || k <= 0 || k > n)
		{ // n，k值输入不合法情况
			return res;
		}
		vector<int> p; // 初始化空的p
		generateComb(n, k, 1, p);
		return res;
	}
};
/************回溯法的剪枝优化**********/
class Solution1
{
private:
	vector<vector<int>> res;
	// 求解C(n,k)，从start开始搜索组合中新的元素
	void generateComb(int n, int k, int start, vector<int> &c)
	{
		if (c.size() == k)
		{
			res.push_back(c);
			return;
		}
		// c中存放已有的k个元素，k-c.size()空位,[i...n]中至少有k-c.size()个元素
		// i最大为n-(k-c.size())+1
		for (int i = start; i <= n - (k - c.size()) + 1; i++)
		{
			c.push_back(i);
			generateComb(n, k, i + 1, c);
			c.pop_back();
		}
		return;
	}

public:
	vector<vector<int>> Combinations(int n, int k)
	{
		res.clear();
		if (n <= 0 || k <= 0 || k > n)
		{ // n，k值输入不合法情况
			return res;
		}
		vector<int> p; // 初始化空的p
		generateComb(n, k, 1, p);
		return res;
	}
};
// 最新版本 from labuladong
class Solution
{
private:
	vector<vector<int>> res;
	vector<int> temp;
	void backtrack(int n, int k, int idx)
	{
		if (temp.size() == k)
		{
			res.push_back(temp);
			return;
		}
		for (int i = idx; i <= n; i++)
		{
			temp.push_back(i);
			backtrack(n, k, i + 1);
			temp.pop_back();
		}
	}

public:
	vector<vector<int>> combine(int n, int k)
	{
		backtrack(n, k, 1);
		return res;
	}
};

int main()
{
	vector<vector<int>> res;
	res = Solution1().Combinations(4, 2);
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[0].size(); j++)
		{
			cout << res[i][j];
		}
		cout << endl;
	}
	return 0;
}
