#include<algorithm>//包含堆操作
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<stack>//栈
#include<queue>//队列
using namespace std;
#define row 3
#define col 4
/****************最短路径问题***********************************/
int process(int matrix[][col], const int rowlen, const int collen, int i, int j) {

	if (i == rowlen - 1 && j == collen - 1) {//到最右下角了，返回当前值即为路径和
		return matrix[i][j];
	}
	if (i == rowlen - 1) {//到最下面一行了，只能向右运动，即当前值加右侧值为最小路径和，j++
		return matrix[i][j] + process(matrix, rowlen, collen, i, j + 1);
	}
	if (j == collen - 1) {//到最右面一列了，只能向下运动，即当前值加下侧值为最小路径和，i++
		return matrix[i][j] + process(matrix, rowlen, collen, i + 1, j);
	}
	int right = process(matrix, rowlen, collen, i, j + 1);//除去上述特殊情况，当前点右边位置到最右下角的最短路径和
	int down = process(matrix, rowlen, collen, i + 1, j);//当前点下边位置到最右下角的最短路径和
	return matrix[i][j] + min(right, down);//当前值加最小的值即为最小路径

}
/*------------------------------------------------------------------------------------------*/
int main()
{
	int matrix[row][col] = { 3,2,1,0,
							7,5,0,1,
							3,7,6,2,

	};
	int rowlen = sizeof(matrix) / sizeof(matrix[0]);
	int collen = sizeof(matrix[0]) / sizeof(matrix[0][0]);
	int res = process(matrix, rowlen, collen, 0, 0);
	cout << res << endl;
	return 0;
}

