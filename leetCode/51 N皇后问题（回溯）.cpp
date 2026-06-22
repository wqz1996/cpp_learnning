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
/*************n皇后问题*****************/
//将n个皇后放在n*n的方格中，保证每行和列还有对角线只有一个皇后
//使用剪枝方法
//使用col[i]数组，代表第i行被占用
//dia1[i]对角线dia2[i]对角线
//对角线表示法,右上到左下方向每个位置的横纵坐标相加等于1...2*n-2
//左上到右下方向，横纵坐标相减-（2n-2）/2到（2n-2）/2
//4皇后问题，每个方向的对角线有2*n-1个
class Solution {
private:
	vector<vector<string>> res;
	vector <bool> col,dia1,dia2;
	vector<string> generateBoard(int n,vector<int>& row) {//将row生成Q矩阵
		assert(row.size() == n);
		vector<string> board(n, string(n, '.'));//n个string，每个string有n个‘.’
		for (int i = 0; i < n; i++) {
			board[i][row[i]] = 'Q';
			
		}
		return board;

	}
	//递归解决n皇后问题，摆放在index行的皇后位置
	void putQueen(int n, int index, vector<int>& row) {//index第几个皇后，第index行皇后在第i列数
		if (index == n) {//摆放到最后一行则说明一种情况结束
			res.push_back(generateBoard(n, row));
			return;
		}
		for (int i = 0; i < n; i++) {//分别尝试将index行的皇后摆放在i列
			if (!col[i] && !dia1[index+i] && !dia2[index-i+n-1]) {
				row.push_back(i);//index行的皇后摆放在第i列
				col[i] = true;
				dia1[index + i] = true;
				dia2[index - i + n - 1] = true;
				putQueen(n, index + 1, row);//在下一行摆放皇后
				col[i] = false;//回溯
				dia1[index + i] = false;
				dia2[index - i + n - 1] = false;
				row.pop_back(); 
			}
		}
		return;
			
	}
public:
	vector<vector<string>> solveNQueens(int n) {
		col = vector<bool>(n, false);//记录每一列被占用的情况
		dia1 = vector<bool>(2*n-1, false);//记录对角线1被占用的情况
		dia2 = vector<bool>(2*n-1, false);//记录对角线2被占用的情况
		vector<int> row;
		putQueen(n, 0, row);
		return res;
	}

};
int main()
{
	int n = 4;

	vector<vector<string>> res = Solution().solveNQueens(n);
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res[0].size(); j++) {
			cout << res[i][j]<<endl;
		}
		cout << endl;
	}

	return 0;
}