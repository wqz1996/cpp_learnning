#include <iostream> // cout, endl：第 63 行首次使用
#include <string> // string：第 17 行首次使用
#include <vector> // vector：第 12 行首次使用
#include <cassert> // assert：第 42 行首次使用
using namespace std;
/*************单词搜索*****************/
//给定二维字符数组，上下左右相连即为找到给定单词
class Solution {
private:
	int d[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };//向四个方向移动坐标
	int m, n;
	vector<vector<bool>> visited;
	bool inArea(int x, int y) {
		return x >= 0 && x < m && y >= 0 && y < n;
	}
	//从board[startx][starty]开始，寻找word[index...word.size()]是否存在
	bool searchWord(const vector<vector<char>>& board, const string& word, int index, int startx, int starty) {
		if (index == word.size() - 1)
			return board[startx][starty] == word[index];
		if (board[startx][starty] == word[index]) {//从(x,y)出发，向四个方向寻找
			visited[startx][starty] = true;//已经经过的设置为true
			for (int i = 0; i < 4; i++) {//四个方向,左上右下的顺序
				int newx = startx + d[i][0];
				int newy = starty + d[i][1];
				if (inArea(newx, newy) && !visited[newx][newy]) {//边界判断
					if (searchWord(board, word, index + 1, newx, newy))//找到了字符串
						return true;

				}
				
			}
			visited[startx][starty] = false;//无果后放弃该位置

		}
		return false;
	}
public:

	bool exist(vector<vector<char>> & board, string word) {//在board矩阵中查找word
		m = board.size();
		n = board[0].size();
		assert(m > 0);
		visited = vector<vector<bool>>(m, vector<bool>(n, false));//初始化为m*n的false矩阵
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[i].size(); j++) {
				if (searchWord(board, word, 0, i, j))
					return true;
			}

		}
		return false;
	}
};

int main()
{
	vector<vector<char>> board={
		{'a','b','f','g'},
		{'c','f','c','s'},
		{'j','d','e','h'}
	};
	string word{ "bfch" };
	cout << Solution().exist(board, word)<<endl;
	return 0;
}