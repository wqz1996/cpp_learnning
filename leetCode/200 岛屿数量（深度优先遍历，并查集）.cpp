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
		if (isArea(grid, i, j))
			return;
		grid[i][j] = '2';
		infect(grid, i + 1, j);//下
		infect(grid, i, j + 1);//右
		infect(grid, i - 1, j);//上
		infect(grid, i, j - 1);//左

	}
	bool isArea(vector<vector<char>>& grid, int i, int j) {
		return (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != '1');
	}
public:

	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty())
			return 0;
		n = grid.size();//行
		m = grid[0].size();//列
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
//并查集
class Solution {//字符格式
public:
	int count;//统计集合个数
	int row;
	int col;
	vector<int> parent;//代表节点
	vector<int> rank;//每个集合节点个数
	void creatUnion(vector<vector<char>> grid) {
		count = 0;
		parent = vector<int>(row * col, -1);//初始化为一维数组方便操作
		rank = vector<int>(row * col, 1);//初始化所有集合中元素个数为1
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == '1') {//统计'S'的数量
					parent[i * col + j] = i * col + j;//'S'的代表节点就是本身
					count++;
				}
			}
		}
	}
	int find(int i) {//查找代表节点并压缩路径
		int root = i;
		while (root != parent[root])//找到老大
			root = parent[root];
		while (i != parent[i]) {//压缩路径，将所有直接指向真正老大
			int temp = parent[i];
			parent[i] = root;
			i = temp;
		}
		return root;
	}
	void unionset(int x, int y) {//合并两个集合
		int rootx = find(x);//找到x的代表节点
		int rooty = find(y);//找到y的代表节点
		if (rootx != rooty) {//两个代表节点不同则进行合并
			if (rank[rootx] > rank[rooty])//将小的集合合并到大集合中
				parent[rooty] = rootx;//rooty的老大是rootx
			else if (rank[rootx] < rank[rooty])
				parent[rootx] = rooty;
			else {//两个集合数量相等则我们制定合并到其中一个即可，
				parent[rooty] = rootx;
				rank[rootx] += rank[rooty];//rootx的集合数量加上rooty的集合数量
			}
			count--;//每次合并集合数量减一
		}

	}
	bool isArea(int x, int y) {
		return x >= 0 && x < row && y >= 0 && y < col;
	}
	int numIslands(vector<vector<char>>& grid) {
		if (grid.empty())
			return 0;
		row = grid.size();
		col = grid[0].size();
		creatUnion(grid);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (grid[i][j] == '0')
					continue;
				if (isArea(i + 1, j) && grid[i + 1][j] == '1')
					unionset(i * col + j, (i + 1) * col + j);
				if (isArea(i - 1, j) && grid[i - 1][j] == '1')
					unionset(i * col + j, (i - 1) * col + j);
				if (isArea(i, j + 1) && grid[i][j + 1] == '1')
					unionset(i * col + j, i * col + (j + 1));
				if (isArea(i, j - 1) && grid[i][j - 1] == '1')
					unionset(i * col + j, i * col + (j - 1));
			}
		}
		return count;
	}
};
int main()
{
	vector<vector<int>> board = {
		{1,1,1,1,0},
		{1,1,0,0,0},
		{1,1,0,1,0},
	};

	cout << Solution().NumofIsland(board) << endl;

	return 0;
}