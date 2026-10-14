#include <iostream> // 使用处：第 29 行的 cout
using namespace std;
/*******************在排列好的矩阵中查找数*******************************************/
bool hasAimNum(int m[][4],int num,int r,int c) {
	int indexR = 0;
	int indexC = c - 1;
	while (indexR!=r&&indexC!=-1) {
		if (m[indexR][indexC] > num) {
			indexC--;
		}
		else if (m[indexR][indexC] < num) {
			indexR++;
		}
		else {
			return true;
		}

	}
	return false;
}
int main()
{	
	//int** m;
	int matrix[3][4] = { 1,3,5,6,
		2,5,7,9,
		4,6,8,10
	};
	for(int i=0;i<15;i++)
	cout<< hasAimNum(matrix, i, 3, 4)<<endl;
	return 0;

	
}

