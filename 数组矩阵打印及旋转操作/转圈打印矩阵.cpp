#include <iostream> // 使用处：第 10 行的 cout
#include <vector> // 使用处：第 7 行的 vector
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
