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
//56. 合并区间
//给出一个区间的集合，请合并所有重叠的区间。
/****************递归（超时）**********************/
class Solution {
private:
	int res;
	vector<vector<bool>> visited;
	int row, col;
	bool isArea(int x, int y) {
		return x <= row - 1 && y <= col - 1;
	}
	void findpath(int x, int y) {
		if (x == row - 1 && y == col - 1) {
			res++;
			return;
		}
		visited[x][y] = true;
		if (isArea(x + 1, y) && !visited[x + 1][y]) {
			findpath(x + 1, y);
			visited[x][y] = false;
		}
			
		if (isArea(x, y + 1) && !visited[x][y + 1]) {
			findpath(x , y + 1);
			visited[x][y] = false;
		}
			
	}
public:
	int uniquePaths(int m, int n) {
		res = 0;
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		row = m;
		col = n;
		findpath(0, 0);
		return res;
	}
};
/******************动态规划************************/
class Solution1 {
public:
	int uniquePaths(int m, int n) {
		vector<vector<int>> dp(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++)
			dp[i][0] = 1;
		for (int i = 1; i < n; i++)
			dp[0][i] = 1;
		for (int i = 1; i < m; i++) {
			for (int j = 1; j < n; j++) {
				dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
			}
		}
		return dp[m - 1][n - 1];

	}
};
int main()
{
	Solution1().uniquePaths(3, 2);
	return 0;
}

