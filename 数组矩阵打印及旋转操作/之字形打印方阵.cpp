#include <iostream> // 使用处：第 11 行的 cout
using namespace std;
/*******************之字形打印矩阵*******************************************/

void printlevel(int m[][3], int tR, int tC, int dR, int dC, bool f)
{
	if (f)//用于切换对角线打印方向
	{
		while (tR != dR + 1)
		{
			cout << m[tR++][tC--] << ' ';//打印(tr,tc)和(dr,dr)组成的对角线，向左下方移动
		}
	}
	else
	{
		while (dR != tR - 1)
		{
			cout << m[dR--][dC++] << ' ';//打印(tr,tc)和(dr,dr)组成的对角线，向右上方移动
		}
	}

}
void printMatrixZigZag(int matrix[][3], int R, int C)
{
	int aR = 0, aC = 0, bR = 0, bC = 0;//定义两个点(aR,aC)向右移动，到最右短后向下运动，(bR,bC)向下移动，到最下端后向右移动
	bool fromup = false;
	int endR = R - 1;
	int endC = C - 1;
	while (aR != endR + 1)
	{
		printlevel(matrix, aR, aC, bR, bC, fromup);
		aR = aC == endC ? aR + 1 : aR;//a点是否到最后一列，是则行数向下走，否则不变（和下边语句不可对换）
		aC = aC == endC ? aC : aC + 1;//a点是否到最后一列,是则列数保持不变，否则ac++
		bC = bR == endR ? bC + 1 : bC;//b点是否到最后一行，是则列数向右走，否则不变(和下边语句顺序不可对换)
		bR = bR == endR ? bR : bR + 1;//b点是否到最后一行，是则行数保持不变，否则br++

		fromup = !fromup;//切换从上到下或从下到上的打印顺序

	}
}


int main()
{
	//int** m;
	int matrix[3][3] = { 1,2,3,4,5,6,7,8,9 };
	//m = (int**)matrix; //void func(int** m,r,c){ *(m+c*i+j)->m[i][j] }
	//func(m,r,c);
	//int** m= (int**)matrix;//强制将数组转换为指针，才可以作为int**类型的形参传入
	//r.rotateEasy(matrix,3,3);
	printMatrixZigZag(matrix, 3, 3);
	cout << endl;
	return 0;


}

