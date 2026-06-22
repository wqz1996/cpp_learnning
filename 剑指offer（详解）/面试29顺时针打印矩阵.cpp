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
//面试题29. 顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。
class Solution {
private:
	vector<int> res;
	void rotateSaveMatrix(vector<vector<int>>& matrix, int tr, int tc, int dr, int dc) {//旋转存储一圈的数组
		if (tr == dr) {//只有一行
			for (int i = tc; i <= dc; i++)//从左到右存储一行
				res.push_back(matrix[tr][i]);
		}else if (tc == dc) {//只有一列
			for (int i = tr; i <= dr; i++)//从上到下存储一列
				res.push_back(matrix[i][tc]);
		}
		else {//不是一行或者一列
			int curR = tr;//tr，tc，dr，dc表示边界，不改变边界
			int curC = tc;
			while (curC != dc) //curR==tr
				res.push_back(matrix[curR][curC++]);//从左到右存储一行			
			while (curR != dr) //curC==dc
				res.push_back(matrix[curR++][curC]);//从上到下存储一列			
			while (curC != tc) //curR=dr
				res.push_back(matrix[curR][curC--]);//从右到左存储一行			
			while (curR != tr) //curC=tc
				res.push_back(matrix[curR--][curC]);//从下到上存储一列		

		}
	}
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.empty())
			return res;
		int tr = 0;//记录左上角的坐标
		int tc = 0;
		int dr = matrix.size()-1;//记录右下角的坐标
		int dc = matrix[0].size() - 1;
		while (tr <= dr && tc <= dc) {
			rotateSaveMatrix(matrix, tr++, tc++, dr--, dc--);//向内缩一圈
		}
		return res;
		
	}
};
//自写
class Solution {
private:
	vector<int> res;
	void spiralprint(vector<vector<int>>& m, int tr, int tc, int dr, int dc) {
		if (tr == dr) {
			while (tc <= dc)
				res.push_back(m[tr][tc++]);
		}
		else if (tc == dc) {
			while (tr <= dr)
				res.push_back(m[tr++][tc]);
		}
		else {
			int curR = tr;
			int curC = tc;
			while (curC < dc)
				res.push_back(m[curR][curC++]);
			while (curR < dr)
				res.push_back(m[curR++][curC]);
			while (curC > tc)
				res.push_back(m[curR][curC--]);
			while (curR > tr)
				res.push_back(m[curR--][curC]);
		}
	}
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.empty())
			return res;
		int tr = 0;
		int tc = 0;
		int dr = matrix.size() - 1;
		int dc = matrix[0].size() - 1;
		while (tr <= dr && tc <= dc) {
			spiralprint(matrix, tr++, tc++, dr--, dc--);
		}
		return res;
	}
};
int main()
{
	vector<vector<int>> m2 = { {1, 2, 3},{4, 5, 6},{7, 8, 9} };
	vector<int> ans;
	ans =Solution().spiralOrder(m2);
	return 0;
}

