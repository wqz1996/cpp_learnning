#include <iostream> // cout、endl：main 输出两种解法
#include <vector> // vector：第 10 行首次使用
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
    cout << "递归: " << Solution().uniquePaths(3, 2) << endl;
    cout << "动态规划: " << Solution1().uniquePaths(3, 2) << endl;
    return 0;
}
