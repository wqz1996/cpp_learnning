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
//面试题47. 礼物的最大价值
// 题目：在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值
//（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者
//向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，
//请计算你最多能拿到多少价值的礼物？
/*****************传统动态规划******************/
class Solution {
public:
	int maxValue(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		vector<vector<int>> dp(row, vector<int>(col, 0));
		dp[0][0] = grid[0][0];
		for (int i = 1; i < col; i++)//填充第一行
			dp[0][i] = dp[0][i - 1] + grid[0][i];
		for (int i = 1; i < row; i++)//填充第一列
			dp[i][0] = dp[i - 1][0] + grid[i][0];
		for (int i = 1; i < row; i++) {
			for (int j = 1; j < col; j++) {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];//取上面一个和左边一个的最大值与grid[i][j]相加
			}
		}
		return dp[row - 1][col - 1];
	}
};
/**************优化空间************************/
class Solution {
public:
	int maxValue(vector<vector<int>>& grid) {
		int row = grid.size();
		int col = grid[0].size();
		vector<int> dp(col, 0);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == 0 && j == 0)//dp[0][0]==grid[0][0]
					dp[j] = grid[i][j];
				else if (i == 0)//j!=0，根据前一个值累加得当前值
					dp[j] = grid[i][j] + dp[j - 1];
				else if (j == 0)//i!=0，dp[j]相当于dp[i-1][j]，累加即可
					dp[j] = grid[i][j] + dp[j];
				else//i!=0&&j!=0，根据当前dp[j]和前一个值dp[j-1]相当于dp[i-1][j]和dp[i][j-1]
					dp[j] = max(dp[j], dp[j - 1]) + grid[i][j];

			}
		}
		return dp[col - 1];
	}
};
int main()
{
	vector<vector<int>> grid{ {1,3,1} };
	Solution().maxValue(grid);

	return 0;
}

