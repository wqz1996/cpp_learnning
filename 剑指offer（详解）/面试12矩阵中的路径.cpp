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
// 面试题12：矩阵中的路径
// 题目：请设计一个函数，用来判断在一个矩阵中是否
//存在一条包含某字符串所有字符的路径。路径可以从矩
//阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。
//如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
class Solution {
private:
	int m, n;
	vector<vector<bool>> visited;//标记对应坐标位置是否访问过
	bool isArea(int x, int y) {
		return x >= 0 && x < m && y >= 0 && y < n;
	}
	bool findword(vector<vector<char>>& board, string& word,int index, int row,int col) {//board和word传入用&，减少拷贝次数加快运行速度
		if (index == word.size()-1)//查询到最后一个字母，判断最后一个字母与当前坐标元素是否相等
			return board[row][col]==word[index];

		if (word[index] == board[row][col]) {
			visited[row][col] = true;//当前坐标标记为已访问
			if (isArea(row - 1, col) && !visited[row - 1][col]) {//判断能否向上走
				if (findword(board, word, index + 1, row - 1, col))
					return true;
			}
			if (isArea(row, col + 1) && !visited[row][col + 1]) {//判断能否向右走
				if (findword(board, word, index + 1, row, col + 1))
					return true;
			}
			if (isArea(row + 1, col) && !visited[row + 1][col]) {//判断能否向下走
				if (findword(board, word, index + 1, row + 1, col))
					return true;
			}
			if (isArea(row, col-1) && !visited[row][col-1]) {//判断能否向左走
				if (findword(board, word, index + 1, row, col-1))
					return true;
			}
			visited[row][col] = false;//回溯

		}
		//遇到字母不等或者越界了都返回false
			return false;

	}
public:
	bool exist(vector<vector<char>>& board, string word) {
		m = board.size();
		n = board[0].size();
		visited = vector<vector<bool>>(m, vector<bool>(n, false));
		for (int i = 0; i < m; i++) {//从(i,j)坐标开始搜索
			for (int j = 0; j < n; j++) {
				if (findword(board, word, 0, i, j))
					return true;
			}
		}
		return false;

	}
};
int main()
{
	
	return 0;
}

