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
/************暴力递归（自己写的）******************/
class Solution {
private:
	int minval = INT_MAX;
	int sum;
	bool isArea(const vector<vector<int>>& triangle, int row, int col) {
		return col >= 0 && col < triangle[row].size();
	}
	void findpath(vector<vector<int>>& triangle, int row, int col) {
		if (row == triangle.size() - 1) {
			sum += triangle[row][col];
			minval = min(minval, sum);
			sum -= triangle[row][col];
			return;
		}
		sum += triangle[row][col];
		if (isArea(triangle, row + 1, col))
			findpath(triangle, row + 1, col);
		if (isArea(triangle, row + 1, col + 1))
			findpath(triangle, row + 1, col + 1);
		sum -= triangle[row][col];
		return;

	}
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())
			return 0;
		sum = 0;
		findpath(triangle, 0, 0);
		return minval;
	}
};
/************简单版******************/
class Solution1 {
private:
	int findpath(vector<vector<int>>& triangle, int i, int j) {
		if (i == triangle.size() - 1)//到最后一行返回当前值
			return triangle[i][j];
		int a = findpath(triangle, i + 1, j);//记录向下走结果
		int b = findpath(triangle, i + 1, j + 1);//记录向相邻位置走的结果
		return min(a, b) + triangle[i][j];//返回两个结果较小的值加上当前位置
	}
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())
			return 0;
		return findpath(triangle, 0, 0);
	}
};
/************记忆化搜索******************/
class Solution2 {
private:
	vector<vector<int>> mem;
	int findpath(vector<vector<int>>& triangle, int i, int j) {
		if (i == triangle.size() - 1)
			return triangle[i][j];
		if (mem[i][j] == -1) {
			int a = findpath(triangle, i + 1, j);
			int b = findpath(triangle, i + 1, j + 1);
			mem[i][j] = min(a, b) + triangle[i][j];
		}
		return mem[i][j];

	}
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())
			return 0;
		mem = vector<vector<int>>(triangle.size(), vector<int>(triangle.size(), -1));
		return findpath(triangle, 0, 0);
	}
};
/************动态规划******************/
class Solution3 {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())
			return 0;
		vector<vector<int>> dp(triangle.size(), vector<int>(triangle.size(), 0));
		int n = triangle.size();
		dp[0][0] = triangle[0][0];
		for (int i = 1; i < triangle.size(); i++) {
			dp[i][0] = dp[i - 1][0] + triangle[i][0];
			for (int j = 1; j < i; j++) {
				dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - 1]) + triangle[i][j];
			}
			dp[i][i] = dp[i - 1][i - 1] + triangle[i][i];
		}
		return *min_element(dp[n - 1].begin(), dp[n - 1].end());
	}
};
/************动态规划（空间优化）******************/
class Solution4 {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		if (triangle.empty())
			return 0;
		int n = triangle.size();
		vector<int> dp(n, 0);
		dp[0] = triangle[0][0];
		for (int i = 1; i < n; i++) {
			dp[i] = dp[i - 1] + triangle[i][i];
			for (int j = i - 1; j > 0; j--)
				dp[j] = min(dp[j - 1], dp[j]) + triangle[i][j];
			dp[0] += triangle[i][0];
		}
		return *min_element(dp.begin(), dp.end());
	}
};
/*动态规划最优解*/
class Solution5 {
public:
	int minnumTotal(vector<vector<int>> triangle) {
		if (triangle.empty())
			return 0;
		int n = triangle.size();
		vector<int> dp(n, 0);
		for (int i = 0; i < n; i++)//最下面一层为初始值
			dp[i] = triangle[n - 1][i];
		for (int i = n - 2; i >= 0; i--) {//从倒数第二层开始计算
			for (int j = 0; j < triangle[i].size(); j++) {//列数从0到
				dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
			}
		}
		return dp[0];
	}
};
int main()
{
	vector<vector<int>> num{
				   {2},
				  {3,4},
				 {6,5,7},
				{4,1,8,3}
	};
	int min = Solution5().minnumTotal(num);
	return 0;
}

