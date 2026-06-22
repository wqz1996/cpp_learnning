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
//面试4 二维数组中的查找
//在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，
//每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的
//一个二维数组和一个整数，判断数组中是否含有该整数。
/******************自写程序*********************/
class Solution {
public:
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
		//从右上角开始找
		if (matrix.size()==0||matrix[0].size()==0)
			return false;
		int row = 0;
		int col = matrix[0].size()-1;
		while (row != matrix.size()-1 || col != 0) {
			if (matrix[row][col] > target)
				if (matrix[0].size() == 1||col==0)
					return false;
				else
					col--;
			else if (matrix[row][col] < target)
				if (matrix.size() == 1||row==matrix.size()-1)
					return false;
				else
					row++;
			else {
				assert(matrix[row][col] == target);
				return true;
			}
		}
		if (matrix[row][col] == target)
			return true;
		return false;

	}
};
class Solution {
public:
	bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
		if (matrix.size() == 0 || matrix[0].size() == 0)
			return false;//空全都为false

		int row = 0;//从右上角开始找
		int col = matrix[0].size() - 1;
		while (row < matrix.size() && col >= 0) {//边界判断
			if (matrix[row][col] == target)
				return true;
			else if (matrix[row][col] > target)//大于目标值向左移动
				col--;
			else//小于目标值向下移动
				row++;
		}
		return false;

	}
};
int main()
{
	vector<vector<int>> matrix{ {-1,3} };
	cout<< Solution().findNumberIn2DArray(matrix,-1)<<endl;
	
	return 0;
}

