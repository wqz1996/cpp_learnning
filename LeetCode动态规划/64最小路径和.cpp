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
//64. 最小路径和
//给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，
//使得路径上的数字总和为最小。
/************暴力递归*****************/
class Solution {
private:
	int findpath(vector<vector<int>>& grid, int x, int y) {
		if (x == grid.size() || y == grid[0].size())
			return INT_MAX;
		if (x == grid.size() - 1 && y == grid[0].size() - 1)
			return grid[x][y];
		return grid[x][y] + min(findpath(grid, x + 1, y), findpath(grid, x, y + 1));

	}
public:
	int minPathSum(vector<vector<int>>& grid) {
		return findpath(grid, 0, 0);
	}
};
/************记忆化搜索*****************/
class Solution {
private:
	vector<vector<int>> mem;
	int findpath(vector<vector<int>>& grid, int x, int y) {
		if (x == grid.size() || y == grid[0].size())
			return INT_MAX;
		if (x == grid.size() - 1 && y == grid[0].size() - 1)
			return grid[x][y];
		if (mem[x][y] == -1) {//未计算过则进入递归
			mem[x][y] = grid[x][y] + min(findpath(grid, x + 1, y), findpath(grid, x, y + 1));
		}
		return mem[x][y];//计算过直接返回值

	}
public:
	int minPathSum(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		mem = vector<vector<int>>(m, vector<int>(n, -1));
		return findpath(grid, 0, 0);
	}
};
/****************经典动态规划*******************/
class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == 0 && j == 0)
					dp[i][j] = grid[i][j];
				else if (i == 0)
					dp[i][j] = dp[i][j - 1] + grid[i][j];
				else if (j == 0)
					dp[i][j] = dp[i-1][j] + grid[i][j];
				else {
					dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
				}
				
				
			}
		}
		return dp[row - 1][col - 1];
	}
};
/****************使用一维数组(?)*******************/
class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		vector<int> dp(2,0);

		
	}
};
/****************直接在原数组上修改*******************/
class Solution1 {
public:
	int minPathSum(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == 0&&j!=0)
					grid[i][j] += grid[i][j - 1];
				else if (j == 0&& i!=0)
					grid[i][j] += grid[i-1][j];
				else if (i == 0 && j == 0) {
					continue;
				}
				else {
					grid[i][j] += min(grid[i - 1][j], grid[i][j - 1]);
				}

			}
		}
		return grid[row - 1][col - 1];
	}
};
int main()
{
	vector<vector<int>> grid{ {1,3,1} ,
							  {1,5,1},
							  {4,2,1}
								      };
	Solution1().minPathSum(grid);
	return 0;
}

