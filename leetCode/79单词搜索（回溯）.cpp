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

class Solution1 {
private:
	int row, col;
	vector<vector<bool>> visit;
	bool isArea(int x, int y) {
		return x >= 0 && x < row && y >= 0 && y < col;
	}
	bool findpath(vector<vector<char>>& board, string word, int index, int x, int y) {
		if (index == word.size() - 1)
			return word[index] == board[x][y];
		if (word[index] == board[x][y]) {
			visit[x][y] = true;
			if (isArea(x + 1, y) && !visit[x + 1][y]) {
				if (findpath(board, word, index + 1, x + 1, y))
					return true;
			}
			if (isArea(x - 1, y) && !visit[x - 1][y]) {
				if (findpath(board, word, index + 1, x - 1, y))
					return true;
			}
			if (isArea(x, y+1) && !visit[x][y+1]) {
				if (findpath(board, word, index + 1, x, y+1))
					return true;
			}
			if (isArea(x, y-1) && !visit[x][y-1]) {
				if (findpath(board, word, index + 1, x, y-1))
					return true;
			}
			visit[x][y] = false;
		}
		return false;
	}
public:
	bool exist(vector<vector<char>>& board, string word) {//在board矩阵中查找word
		if (board.empty())
			return false;
		row = board.size();
		col = board[0].size();
		visit = vector<vector<bool>>(row, vector<bool>(col, false));
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (findpath(board, word, 0, i, j))
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