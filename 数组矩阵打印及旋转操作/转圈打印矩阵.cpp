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
/*******************转圈打印矩阵*******************************************/
class PrintMatrixSpiralOrder {
public:
	void printEdge(vector<vector<int>> matrix, int tr, int tc, int dr, int dc) {//打印函数
		if (tr == dr) {//只剩一行
			for (int i = tc; i <= dc; i++) {
				cout << matrix[tr][i] << ' ';
			}
		}
		else if (tc == dc) {//只剩一列
			for (int i = tr; i <= dr; i++) {
				cout << matrix[i][tc] << ' ';
			}
		}
		else {
			int curR = tr;
			int curC = tc;


			/*上侧边为tr,左侧边为tc，下侧边为dr，右侧边为dc*/
			while (curC != dc) {//打印上侧边从左到右
				cout << matrix[tr][curC] << ' ';//
				curC++;
			}
			while (curR != dr) {//打印右侧边从上到下
				cout << matrix[curR][dc] << ' ';
				curR++;
			}
			while (curC != tc) {//打印下侧边从右到左
				cout << matrix[dr][curC] << ' ';
				curC--;
			}
			while (curR != tr) {//打印左侧边从下到上
				cout << matrix[curR][tc] << ' ';
				curR--;
			}


		}

	}
	void spiralOrderPrint(vector<vector<int>> matrix) {
		int tr = 0;//左上角点的坐标
		int tc = 0;
		int dr = matrix.size() - 1;//右下角点的坐标
		int dc = matrix[0].size() - 1;
		while (tr <= dr && tc <= dc) {//当坐标点不重合则进入循环
			printEdge(matrix, tr++, tc++, dr--, dc--);//左上角点向右下角移动一个，右下角点向左上角移动一个
		}
		cout << endl;
	}

};
int main()
{
	PrintMatrixSpiralOrder p;
	//int** m;
	vector<vector<int>> matrix = { {1,2,3},{8,9,4},{7,6,5} };
	//m = (int**)matrix; //void func(int** m,r,c){ *(m+c*i+j)->m[i][j] }
	//func(m,r,c);
	p.spiralOrderPrint(matrix);

	return 0;


}
