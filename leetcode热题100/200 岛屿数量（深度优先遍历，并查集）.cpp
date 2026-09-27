#include <iostream> // cout, endl：第 84 行首次使用
#include <vector> // vector：第 10 行首次使用
using namespace std;
/*************深度优先遍历*****************/
//岛的数量问题(floodfill算法)
class Solution {//整形数组格式
private:
	int nums;
	int m, n;
	void infect(vector<vector<int>>& board, int i, int j) {//将连在一起的1变为2
		if (isArea(board, i, j))
			return;
		board[i][j] = 2;
		infect(board, i + 1, j);//下
		infect(board, i, j + 1);//右
		infect(board, i - 1, j);//上
		infect(board, i, j - 1);//左

	}
	bool isArea(vector<vector<int>>& board, int i, int j) {
		return (i < 0 || i >= n || j < 0 || j >= m || board[i][j] != 1);
	}
public:
	int NumofIsland(vector<vector<int>>& board) {
		if (board.empty())
			return 0;
		n = board.size();//行
		m = board[0].size();//列
		for (int i = 0; i < n; i++) {//遍历所有位置
			for (int j = 0; j < m; j++) {
				if (board[i][j] == 1) {//若未感染则岛数+1
					nums++;
					infect(board, i, j);//感染所有连在一个起的1
				}

			}
		}
		return nums;
	}

};
class Solution1 {//字符格式
private:
	int nums;
	int m, n;
	void infect(vector<vector<char>>& grid, int i, int j) {//将连在一起的1变为2
		if (!isArea(i, j)||grid[i][j] != '1')
			return;
		grid[i][j] = '2';
		infect(grid, i + 1, j);//下
		infect(grid, i, j + 1);//右
		infect(grid, i - 1, j);//上
		infect(grid, i, j - 1);//左

	}
	bool isArea(int i, int j) {
		return (i >= 0 && i < n && j >= 0 && j < m );
	}
public:

	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty())
			return 0;
		n = grid.size();//行
		m = grid[0].size();//列
		nums = 0;
		for (int i = 0; i < n; i++) {//遍历所有位置
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == '1') {//若未感染则岛数+1
					nums++;
					infect(grid, i, j);//感染所有连在一个起的1
				}

			}
		}
		return nums;
	}
};

int main()
{
    vector<vector<int>> intGrid{{1, 1, 0}, {0, 1, 0}, {0, 0, 1}};
    vector<vector<char>> charGrid{{'1', '1', '0'}, {'0', '1', '0'}, {'0', '0', '1'}};
    cout << "整数网格: " << Solution().NumofIsland(intGrid) << endl;
    cout << "字符网格: " << Solution1().numIslands(charGrid) << endl;
    return 0;
}
