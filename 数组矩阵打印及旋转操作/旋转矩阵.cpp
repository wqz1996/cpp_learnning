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
/*******************旋转矩阵*******************************************/
class rotatematix {
public:
	void rotate(int** matrix, int r, int c) {
		int tr = 0;
		int tc = 0;
		int dr = r - 1;
		int dc = c - 1;
		while (tr < dr) {
			rotateEdge(matrix, r, c, tr++, tc++, dr--, dc--);
		}
	}
	void rotateEdge(int** m, int r, int c, int tr, int tc, int dr, int dc) {
		int times = dc - tc;
		int* tmp;
		for (int i = 0; i != times; i++) {
			tmp = (*(m + c * tr + (tc + i)));//m[tr][tc+i]
			*(m + c * tr + (tc + i)) = *(m + c * (dr - i) + tc);//m[tr][tc+i]=m[dr-i][tc]
			*(m + c * (dr - i) + tc) = *(m + c * dr + (dc - i));//m[dr-i][tc]=m[dr][dc-i]
			*(m + c * dr + (dc - i)) = *(m + c * (tr + i) + dc);//m[dr][dc-i]=m[tr+i][dc]
			*(m + c * (tr + i) + dc) = tmp;
		}
	}
	void rotateEasy(int matrix[][3], int r, int c) {
		int tr = 0;
		int tc = 0;
		int dr = r - 1;
		int dc = c - 1;
		while (tr < dr) {
			rotateEdgeEasy(matrix, tr++, tc++, dr--, dc--);//从外圈开始逐渐向内圈收缩
		}
	}
	void rotateEdgeEasy(int m[][3], int tr, int tc, int dr, int dc) {
		int times = dc - tc;
		int tmp = 0;
		for (int i = 0; i != times; i++) {
			tmp = m[tr][tc + i];//将上边移动到右边，从左往右遍历因此tc+i,在上边因此是tr
			m[tr][tc + i] = m[dr - i][tc];//左边元素移动到上边，从下往上遍历因因此dr-i,在左边因此tc
			m[dc - i][tc] = m[dr][dc - i];//下边元素移动到左边，从右往左遍历因因此dc-i,在下边因此dr
			m[dr][dc - i] = m[tr + i][dc];//右边元素移动到下边，从上往下遍历因因此tr+i,在右边因此dc
			m[tr + i][dc] = tmp;
		}
	}
	/*******vector数组实现********/
	void rotateEasy1(vector<vector<int>>& matrix) {
		int tr = 0;
		int tc = 0;
		int dr = matrix.size() - 1;
		int dc = matrix[0].size() - 1;
		while (tr < dr) {
			rotateEdgeEasy1(matrix, tr++, tc++, dr--, dc--);//从外圈开始逐渐向内圈收缩
		}
	}
	void rotateEdgeEasy1(vector<vector<int>>& m, int tr, int tc, int dr, int dc) {
		int times = dc - tc;
		int tmp = 0;
		for (int i = 0; i != times; i++) {
			tmp = m[tr][tc + i];//将上边移动到右边，从左往右遍历因此tc+i,在上边因此是tr
			m[tr][tc + i] = m[dr - i][tc];//左边元素移动到上边，从下往上遍历因因此dr-i,在左边因此tc
			m[dc - i][tc] = m[dr][dc - i];//下边元素移动到左边，从右往左遍历因因此dc-i,在下边因此dr
			m[dr][dc - i] = m[tr + i][dc];//右边元素移动到下边，从上往下遍历因因此tr+i,在右边因此dc
			m[tr + i][dc] = tmp;
		}
	}
};
int main()
{
	rotatematix r;

	//int** m;
	int matrix[3][3] = { 1,2,3,8,9,4,7,6,5 };
	//m = (int**)matrix; //void func(int** m,r,c){ *(m+c*i+j)->m[i][j] }
	//func(m,r,c);
	int** m = (int**)matrix;//强制将数组转换为指针，才可以作为int**类型的形参传入
	//r.rotateEasy(matrix,3,3);
	r.rotate(m, 3, 3);
	cout << endl;
	return 0;


}

