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
using namespace std;
/********************************************************************/
/***************岛问题********************/
//矩阵中只有0，1两个值，每个位置可以和上下左右四个位置相连
//如果有一片1连在一起。则这部分叫做岛。求一个矩阵中岛的数量
//解：1）可以用深度搜索
//	  2)当矩阵特别大时，需要将矩阵划分成多块并行计算，需要用到并查集
void infect(int* m, int i, int j, int N, int M) {
	if (i < 0 || i >= N || j < 0 || j >= M || m[M * i + j] != 1) {//越界或当前不为1则返回
		return;
	}
	m[M * i + j] = 2;//将当前位置改为2
	infect(m, i + 1, j, N, M);//感染下
	infect(m, i, j + 1, N, M);//感染右
	infect(m, i - 1, j, N, M);//感染上
	infect(m, i, j - 1, N, M);//感染左
}
int countislands(int* m, int r, int c) {
	if (m == NULL)
		return 0;
	int N = r;
	int M = c;
	int res = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (m[c * i + j] == 1) {//当前为1则岛数加一，并将包括该位置所有连成一片的1全部改为2
				res++;
				infect(m, i, j, N, M);
			}
		}
	}
	return res;
}
//用并查集求解，将岛划分，并行完成，收集各任务的结果，设计边界合并方法（并查集）
//记录感染中心，将同一个感染中心感染的元素放在一个集合中，合并时将边界上的两个集合进行合并，
//合并以后两个集合为一个集合，再次判断时可以避免重复。
int main()
{
	
	int m[][7] = { 
	{1,1,1,1,0,0,0},
	{1,0,0,0,1,1,0},
	{1,1,0,0,0,0,1} 
	};//岛问题验证，答案：3
	cout << countislands((int*)m, 3, 7)<<endl;
	return 0;

}

