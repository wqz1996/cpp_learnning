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
//在4x4的棋盘上摆满了黑白棋子，黑白两色的位置和数目随机其中左上角坐标
//为(1,1),右下角坐标为(4,4),现在依次有一些翻转操作，要对一些给定支点坐
//标为中心的上下左右四个棋子的颜色进行翻转，请计算出翻转后的棋盘颜色。
//给定两个数组A和f, 分别为初始棋盘和翻转位置。其中翻转位置共有3个。
//请返回翻转后的棋盘。
class Flip {
private:
	void change(vector<vector<int>>& A, int x, int y) {
		int row = A.size();
		int col = A[0].size();
		if (x == 0 && y == 0) {
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//下
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右

		}
		else if (x == row - 1 && y == 0) {
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//上
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右			
		}
		else if (x == row - 1 && y == col - 1) {
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//上
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
		}
		else if (x == 0 && y == col - 1) {
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//下
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
		}
		else if (x == 0 && y > 0 && y < col - 1) {
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//下
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右
		}
		else if (x == row - 1 && y > 0 && y < col - 1) {
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//上
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右
		}
		else if (y == col - 1 && x > 0 && x < row - 1) {
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//上
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//下
		}
		else if (y == 0 && x > 0 && x < row - 1) {
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//上
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//下
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右
		}
		else {
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;//上
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;//下
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;//右
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;//左
		}
	}
public:
	vector<vector<int>> flipChess(vector<vector<int> > A, vector<vector<int> > f) {
		for (int i = 0; i < f.size(); i++) {
			int x = f[i][0];
			int y = f[i][1];
			change(A, x - 1, y - 1);
		}
		return A;


	}
};

class Flip {
private:
	void change(vector<vector<int>>& A, int x, int y) {
		if (x > 0)
			A[x - 1][y] = A[x - 1][y] == 0 ? 1 : 0;
		if (y > 0)
			A[x][y - 1] = A[x][y - 1] == 0 ? 1 : 0;
		if (x < A.size() - 1)
			A[x + 1][y] = A[x + 1][y] == 0 ? 1 : 0;
		if (y < A[0].size() - 1)
			A[x][y + 1] = A[x][y + 1] == 0 ? 1 : 0;
	}
public:
	vector<vector<int>> flipChess(vector<vector<int> > A, vector<vector<int> > f) {
		for (int i = 0; i < f.size(); i++) {
			int x = f[i][0];
			int y = f[i][1];
			change(A, x - 1, y - 1);
		}
		return A;


	}
};
int main() {

	return 0;
}

