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

